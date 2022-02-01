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
	DWORD dw = 0;
	ULONGLONG key = 0;
	bool result = false;
	CIOUnit* ioUnit = NULL;
	

	while (true == GetState())
	{
		dw = 0;
		key = 0;
		ioUnit = NULL;

		result = GetQueuedCompletionStatus(mIOCP, &dw, &key, (LPOVERLAPPED*)ioUnit->GetOverlappedPtr(), INFINITE);

		if (false == result)
		{
			OnClose(ioUnit);
			DisConnectSocket(ioUnit);
			continue;
		}
		else if (true == result && 0 == dw)
		{
			if (IO_TYPE::ACEEPT == ioUnit->GetIOType())
			{
				OnConnect(ioUnit);
			}
			else
			{
				OnClose(ioUnit);
				DisConnectSocket(ioUnit);
				continue;
			}
		}
		else
		{
			if (IO_TYPE::RECV == ioUnit->GetIOType())
			{
				OnRecv(ioUnit);
			}
			else if (IO_TYPE::SEND == ioUnit->GetIOType())
			{

			}
		}

		// SEND를 제외한 사용한 IO 반납
		// SEND의 경우 OnSend 함수에서 모든 전송을 끝내면 자동으로 반납함
		if (NULL != ioUnit && IO_TYPE::SEND != ioUnit->GetIOType())
		{
			DeAllocIoUnit(ioUnit);
		}
	}
}

void CiocpServer::OnConnect(CIOUnit* InIO)
{
	CIOAccept* ioAccept = (CIOAccept*)InIO;
	CSocket* sock = ioAccept->GetSocket();

	CIORecv* ioRecv = new CIORecv(sock);
	CIORecvBuffer* ioBuffer = (CIORecvBuffer*)ioRecv->GetIOBuffer();
	
	DWORD dwRecv, dwFlags = 0;
	int result = WSARecv(sock->GetSocket(), ioBuffer->GetWsaBufPtr(), 1, &dwRecv, &dwFlags, ioRecv->GetOverlappedPtr(), 0);
	if (0 == result)
	{
		// Success
	}
	else if (SOCKET_ERROR == result && WSAGetLastError() == WSA_IO_PENDING)
	{
		// Success
	}
	else
	{
		// fail
		DeAllocIoUnit(ioRecv);
	}
}

void CiocpServer::OnRecv(CIOUnit* InIO)
{
	CIORecv* ioRecv = (CIORecv*)InIO;
	CIORecvBuffer* ioBuffer = (CIORecvBuffer*)ioRecv->GetIOBuffer();

	
	//MinNet::CIORecv* 


}

void CiocpServer::OnSend(CIOUnit* InIO)
{

}

void CiocpServer::OnClose(CIOUnit* InIO)
{
	CSocket* sock = InIO->GetSocket();
	CSocketManager::Get()->OnDisConnect(sock);
	
	DeAllocIoUnit(InIO);
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

void CiocpServer::DisConnectSocket(CIOUnit * InIO)
{
	CSocket* sock = InIO->GetSocket();
	//CSocketManager::Get()->

	DeAllocIoUnit(InIO);
}

void CiocpServer::DeAllocIoUnit(CIOUnit * InIO)
{
	switch (InIO->GetIOType())
	{
	case IO_TYPE::ACEEPT:
		delete static_cast<CIOAcceptBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIOAccept*>(InIO);
		break;
	case IO_TYPE::RECV:
		delete static_cast<CIORecvBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIORecv*>(InIO);
		break;
	case IO_TYPE::SEND:
		delete static_cast<CIOSendBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIOSend*>(InIO);
		break;
	case IO_TYPE::CLOSE:
		delete static_cast<CIOCloseBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIOClose*>(InIO);
		break;
	}
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

