#include "pch.h"

#include "NetWork.h"
#include "IOManager.h"

CNetWork::CNetWork()
{
	//accepter = std::make_unique<CAccepter>();
}

CNetWork::~CNetWork()
{

}

bool CNetWork::Start()
{
	// NetWork Init
	if (Init_NetWork() == false)
	{
		// error
		return false;
	}


	// Set IO Manager - 임시 RIO | IOCP(Accept) | IOCP(AcceptEx)로 나눠주기
	if (1)		io_manager = std::make_unique<CRIOManager>();
	else if (2)	io_manager = std::make_unique<CIOCPManager>();
	else if (3)	io_manager = std::make_unique<CIOCPManager_Ex>();
	//else		// error

	if (io_manager->is_fail)
	{
		// error
		return false;
	}
	else
	{
		// Set IO Worker
		for (int i = 0; i < 1; i++)
		{
			workers.emplace_back(std::thread([this, index = i]() { this->io_manager->IO_Run(index); }));
		}
	}

	// Set Accepter Thread
	accepter = std::thread([this]() { this->AccepterRun(); });

	return true;
}

void CNetWork::Stop()
{

}

void CNetWork::AccepterRun()
{
	while (true)
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
			io_manager->OnAccept(new_client);
		}
	}

	return;
}

bool CNetWork::Init_NetWork()
{
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
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(8990);
	addr.sin_family = AF_INET;

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

	return true;
}

