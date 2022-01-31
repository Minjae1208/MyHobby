#include "iocpServer.h"
#include "Socket/SocketManager.h"

#include "IOUnit/IOAccept.h"
#include "IOUnit/IORecv.h"
#include "IOUnit/IOSend.h"
#include "IOUnit/IOClose.h"

MINNET_BEGINE

CiocpServer::CiocpServer()
{
}

CiocpServer::~CiocpServer()
{
	closesocket(mSock);
	CloseHandle(mIOCP);
	WSACleanup();
}

bool CiocpServer::InitNetWork(int InPort, int InWorkerCount, int InSocketCount)
{
	if (false == _WsaStart())
		return false;

	if (false == _Bind(InPort))
		return false;

	if (false == _Listen())
		return false;

	if (false == _Handle())
		return false;

	_CreateSocket(InSocketCount);

	return true;
}

void CiocpServer::_WorkerFunc()
{

}

bool CiocpServer::_WsaStart()
{
	WSADATA wsa;
	
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return false;
	
	mSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == mSock)
		return false;
	
	return true;
}

bool CiocpServer::_Bind(int InPort)
{
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr.s_addr);
	mAddr.sin_port = htons(InPort);

	if (SOCKET_ERROR == ::bind(mSock, (SOCKADDR*)&mAddr, sizeof(SOCKADDR_IN)))
		return false;

	return true;
}

bool CiocpServer::_Listen()
{
	// 이걸 설정 반드시 해야하나? 확인 필요
	if (SOCKET_ERROR == setsockopt(mSock, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&mAddr, sizeof(SOCKADDR_IN)))
		return false;

	if (SOCKET_ERROR == ::listen(mSock, SOMAXCONN))
		return false;

	return true;
}

bool CiocpServer::_Handle()
{
	mIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);
	if (INVALID_HANDLE_VALUE == mIOCP)
		return false;

	if (NULL == CreateIoCompletionPort((HANDLE)mSock, mIOCP, 0, 0))
		return false;

	return true;
}

void CiocpServer::_CreateSocket(int InCount)
{
	CSocketManager::Get()->InitSocket(InCount, InCount/2);

	for (int i = 0; i < InCount; i++)
	{
		_AcceptExSocket();
	}
}

void CiocpServer::_AcceptExSocket()
{
	CSocket* sock = CSocketManager::Get()->GetSocket();
	if (nullptr == sock)
		return ;

	CIOAccept* ioAccept = new CIOAccept(sock);
	CIOAcceptBuffer* mem = (CIOAcceptBuffer*)ioAccept->GetIOBuffer();

	if (::AcceptEx(mSock, sock->GetSocket(), mem->GetMemory(), NULL, sizeof(SOCKADDR_STORAGE) + 16, sizeof(SOCKADDR_STORAGE) + 16, NULL, ioAccept->GetOverlappedPtr()))
	{
		// Error
	}
}

MINNET_END

