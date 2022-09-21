#include "pch.h"
#include "NetWork.h"

CNetWork::CNetWork()
{
}

CNetWork::~CNetWork()
{
}

bool CNetWork::Start()
{
	// NetWork Init
	if (Init_NetWork())
		return false;

	// Set Accepter Thread



	// Set IO Thread







	return true;
}

void CNetWork::Stop()
{

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
	addr.sin_port = htons(1919);
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
	network_handle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == network_handle)
	{
		//error
		return false;
	}

	return true;
}
