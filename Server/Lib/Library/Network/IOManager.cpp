
#include "pch.h"
#include "IOManager.h"
#include "NetWork.h"
#include "Context.h"
#include "IOUnit.h"

// ===========================================================================================
//											IO Manager
// ===========================================================================================
CIOManager::CIOManager(CNetWork* net)
{
	network = net;
}

CIOManager::~CIOManager()
{
	WSACleanup();
	closesocket(listen_socket);
	CloseHandle(io_handle);
}

bool CIOManager::Init_Manager()
{
	accept_run = io_run = proc_run = true;

	// initiates use of the Winsock DLL by a process
	// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock/nf-winsock-wsastartup
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
	{
		// error
		return false;
	}

	// creates a socket that is bound to a specific transport-service provider
	// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-wsasocketw
	listen_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	sockaddr_in addr;
	addr.sin_port = htons(8990);
	addr.sin_family = AF_INET;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);

	// aassociates a local address with a socket
	// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-bind
	if (0 != bind(listen_socket, (sockaddr*)&addr, sizeof(sockaddr_in)))
	{
		//error
		return false;
	}

	// places a socket in a state in which it is listening for an incoming connection
	// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-listen
	if (0 != listen(listen_socket, SOMAXCONN))
	{
		// error
		return false;
	}

	// creates an I/O completion port
	// Link : https://learn.microsoft.com/en-us/windows/win32/fileio/createiocompletionport
	io_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == io_handle)
	{
		// error
		return false;
	}

	proc_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == proc_handle)
	{
		// error
		return false;
	}

	return true;
}

void CIOManager::Accepter_Run()
{
	while (accept_run)
	{
		// permits an incoming connection attempt on a socket
		// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
		SOCKET new_client = accept(listen_socket, NULL, NULL);
		if (new_client == INVALID_SOCKET)
		{
			continue;
		}
		else
		{
			// Success Connect
			network->io_manager->OnAccept(new_client);
		}
	}

	return;
}

void CIOManager::Process_Run()
{
	DWORD length = 0;
	CIOUnit* unit = nullptr;
	CIO_Context* context = nullptr;

	while (proc_run)
	{
		length = 0;
		unit = nullptr;
		context = nullptr;
		if (false == GetQueuedCompletionStatus(proc_handle, &length, (ULONG_PTR*)unit, &(OVERLAPPED*&)context, INFINITE))
		{
			continue;
		}

		if (unit == nullptr)
		{
			// error
			continue;
		}

		if (IO_Type::IO_PROC == context->GetType())
		{
			unit->ProcWork();
		}
		else
		{

		}
	}
}

// ===========================================================================================
//											RIO Manager
// ===========================================================================================
CRIOManager::CRIOManager(CNetWork* net) : CIOManager(net)
{
}

CRIOManager::~CRIOManager()
{
}

bool CRIOManager::Init_Manager()
{
	if (CIOManager::Init_Manager() == false)
	{
		// error
		return false;
	}

	proc_run = true;
	guid = WSAID_MULTIPLE_RIO;

	if (Init_RIO_Table() == false)
	{
		// error
		return false;
	}

	if (Init_RIO_CQ() == false)
	{
		// error
		return false;
	}

	// Init Unit

	// Accept Worker
	accept_worker = std::thread([this]() { this->Accepter_Run(); });

	// IO Worker
	for (int i = 0; i < 1; i++)
		io_workers.emplace_back(std::thread([this, index = i]() { this->IO_Run(index); }));

	// Process Worker
	for (int i = 0; i < 1; i++)
		process_workers.emplace_back(std::thread([this]() { this->Process_Run(); }));

	return true;
}

void CRIOManager::IO_Run(int index)
{
	RIORESULT results[256];

	while (io_run)
	{
		// 루프 당 초기화 한번 진행
		memset(results, 0, sizeof(results));

		ULONG cnt = table.RIODequeueCompletion(cqs[index], results, 256);

		if (RIO_CORRUPT_CQ == cnt)
		{
			// error
			break;
		}
		else if (0 == cnt)
		{
			Sleep(1);
			continue;
		}

		for (ULONG i = 0; i < cnt; i++)
		{
			// 실제 동작부
			CRIO_Context* rio = (CRIO_Context*)results[i].RequestContext;
			ULONG size = results[i].BytesTransferred;

			CIOUnit* unit = rio->GetUnit();

			if (IO_Type::IO_RECV == rio->GetType())
			{
				unit->IORecvWork(size);
			}
			else if (IO_Type::IO_SEND == rio->GetType())
			{
				unit->IOSendWork(size);
			}
			else
			{

			}
		}
	}

	return;
}

void CRIOManager::OnAccept(SOCKET socket)
{
	
}

CIOUnit* CRIOManager::AllocUnit(SOCKET socket)
{
	return nullptr;
}

bool CRIOManager::Init_RIO_Table()
{
	SOCKET socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	DWORD dw = 0;

	int err = WSAIoctl(socket, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(GUID), (void**)&table, sizeof(table), &dw, NULL, NULL);

	if (err != 0)
	{
		// error
		int last_err = WSAGetLastError();
		return false;
	}

	closesocket(socket);
	return true;
}

bool CRIOManager::Init_RIO_CQ()
{
	cqs.resize(1);
	for (int i = 0; i < 1; i++)
	{
		// 
		// 
		cqs[i] = table.RIOCreateCompletionQueue(2500, 0);
		if (cqs[i] == RIO_INVALID_CQ)
		{
			// error
			return false;
		}
	}

	return true;
}


// ===========================================================================================
//									IOCP Manager - Accept
// ===========================================================================================
CIOCPManager::CIOCPManager(CNetWork* net) : CIOManager(net)
{

}

CIOCPManager::~CIOCPManager()
{

}

bool CIOCPManager::Init_Manager()
{
	if (CIOManager::Init_Manager() == false)
	{
		// error
		return false;
	}

	return true;
}

void CIOCPManager::IO_Run(int index)
{
	while (io_run)
	{

	}

	return;
}

void CIOCPManager::OnAccept(SOCKET socket)
{
	CLock lock(unit_lock);

	CIOUnit* unit = AllocUnit(socket);
	if (unit == nullptr)
	{
		closesocket(socket);
		return;
	}


}

CIOUnit* CIOCPManager::AllocUnit(SOCKET socket)
{



	return nullptr;
}


// ===========================================================================================
//									IOCP Manager - AcceptEx
// ===========================================================================================
CIOCPManager_Ex::CIOCPManager_Ex(CNetWork* net) : CIOManager(net)
{
}

CIOCPManager_Ex::~CIOCPManager_Ex()
{
}

bool CIOCPManager_Ex::Init_Manager()
{
	if (CIOManager::Init_Manager() == false)
	{
		// error
		return false;
	}

	return true;
}

void CIOCPManager_Ex::IO_Run(int index)
{
	while (io_run)
	{

	}

	return;
}

void CIOCPManager_Ex::OnAccept(SOCKET socket)
{
}
