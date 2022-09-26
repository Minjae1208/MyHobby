
#include "pch.h"
#include "IOManager.h"

// ===========================================================================================
//											IO Manager
// ===========================================================================================
CIOManager::CIOManager()
{
	// creates an I/O completion port
	// Link : https://learn.microsoft.com/en-us/windows/win32/fileio/createiocompletionport
	io_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == io_handle)
	{
		// error
		is_fail = true;
	}
}

CIOManager::~CIOManager()
{
	CloseHandle(io_handle);
}

// ===========================================================================================
//											RIO Manager
// ===========================================================================================
CRIOManager::CRIOManager()
{
	guid = WSAID_MULTIPLE_RIO;
	Init_RIO_Table();
}

CRIOManager::~CRIOManager()
{
}

void CRIOManager::IO_Run(int index)
{
	RIORESULT results[256];

	while (true)
	{
		memset(results, 0, sizeof(results));

		//
		//
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

		}
	}
}

void CRIOManager::OnAccept(SOCKET socket)
{
}

void CRIOManager::Init_RIO_Table()
{
	SOCKET socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	DWORD dw = 0;

	int err = WSAIoctl(socket, SIO_GET_MULTIPLE_EXTENSION_FUNCTION_POINTER,
		&guid, sizeof(GUID), (void**)&table, sizeof(table), &dw, NULL, NULL);

	if (err != 0)
	{
		// error
		int last_err = WSAGetLastError();
		is_fail = true;
	}

	closesocket(socket);
}

void CRIOManager::Init_RIO_CQ()
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
			is_fail = true;
			return;
		}
	}
}


// ===========================================================================================
//									IOCP Manager - Accept
// ===========================================================================================
CIOCPManager::CIOCPManager()
{

}

CIOCPManager::~CIOCPManager()
{

}

void CIOCPManager::IO_Run(int index)
{
}

void CIOCPManager::OnAccept(SOCKET socket)
{
}


// ===========================================================================================
//									IOCP Manager - AcceptEx
// ===========================================================================================
CIOCPManager_Ex::CIOCPManager_Ex()
{
}

CIOCPManager_Ex::~CIOCPManager_Ex()
{
}

void CIOCPManager_Ex::IO_Run(int index)
{
}

void CIOCPManager_Ex::OnAccept(SOCKET socket)
{
}
