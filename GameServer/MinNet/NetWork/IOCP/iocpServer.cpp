#include "iocpServer.h"
#include "Socket/SocketManager.h"

#include "Peer/PeerManager.h"
#include "Peer/Peer.h"

//#include "IOUnit/IOManager.h"
#include "IOUnit/IOAccept.h"
#include "IOUnit/IORecv.h"
#include "IOUnit/IOSend.h"
#include "IOUnit/IOClose.h"

NAMESPACE_BEGINE(MinNet)

CiocpServer::CiocpServer()
{
}

CiocpServer::~CiocpServer()
{
	closesocket(mSock);
	CloseHandle(mIOCP);
	WSACleanup();
}

/**
	@brief IOCP NetWork Initialize
*/
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

/**
	@brief GQCS Main Worker Function
*/
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

		result = GetQueuedCompletionStatus(mIOCP, &dw, &key, (LPOVERLAPPED*)&ioUnit, INFINITE);

		if (false == result)
		{
			OnClose(ioUnit);
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
				continue;
			}
		}
		else
		{
			if (IO_TYPE::RECV == ioUnit->GetIOType())
			{
				OnRecv(ioUnit, dw);
			}
			else if (IO_TYPE::SEND == ioUnit->GetIOType())
			{
				OnSend(ioUnit, dw);
			}
		}

		// SEND를 제외한 사용한 IO 반납
		// SEND의 경우 OnSend 함수에서 모든 전송을 끝내면 자동으로 반납함
		if (NULL != ioUnit && IO_TYPE::SEND != ioUnit->GetIOType())
		{
			_DeAllocIoUnit(ioUnit);
		}
	}
}


void CiocpServer::OnConnect(CIOUnit* InIO)
{
	CIOAccept* ioAccept = (CIOAccept*)InIO;
	CSocket* sock = ioAccept->GetSocket();

	CIORecv* ioRecv = new CIORecv(sock);
	CIORecvBuffer* ioBuffer = (CIORecvBuffer*)ioRecv->GetIOBuffer();
	
	CPeer* peer = CPeerManager::Get()->ConnectPeer(ioRecv->GetSocket()->GetIndex());
	ioRecv->SetPeer(peer);

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
		_DeAllocIoUnit(ioRecv);
	}
}

void CiocpServer::OnRecv(CIOUnit* InIO, DWORD InLen)
{
	// 데이터 처리
	//CIORecv* ioRecv = (CIORecv*)InIO;
	//CIORecvBuffer* ioBuffer = (CIORecvBuffer*)ioRecv->GetIOBuffer();

	
	CIORecv* ioRecv = new CIORecv(InIO->GetSocket());
	CIORecvBuffer* ioBuffer = (CIORecvBuffer*)ioRecv->GetIOBuffer();

	ioRecv->SetPeer(InIO->GetPeer());

	DWORD dwBytes, dwFlags = 0;
	int result = WSARecv(ioRecv->GetSocket()->GetSocket(), ioBuffer->GetWsaBufPtr(), 1, &dwBytes, &dwFlags, ioRecv->GetOverlappedPtr(), 0);
	if (0 == result)
	{
		// Success 
	}
	else if (SOCKET_ERROR == result && WSA_IO_PENDING == WSAGetLastError())
	{
		// Success 
	}
	else
	{
		// Fail
		_DeAllocIoUnit(ioRecv);
	}
}

void CiocpServer::OnSend(CIOUnit* InIO, DWORD InLen)
{
	// Peer가 끊긴 상태인지 확인 필요
	//if(InIO->GetPeer()->)

	CIOSend* ioSend = (CIOSend*)InIO;
	CIOSendBuffer* ioBuffer = (CIOSendBuffer*)ioSend->GetIOBuffer();

	if (InLen < ioBuffer->GetUseBufSize())
	{
		ioBuffer->Compress(InLen);

		DWORD dwBytes, dwFlags = 0;
		int result = WSASend(ioSend->GetSocket()->GetSocket(), ioBuffer->GetWsaBufPtr(), 1, &dwBytes, dwFlags, ioSend->GetOverlappedPtr(), 0);
		if (0 == result)
		{
			// Success
		}
		else if (SOCKET_ERROR == result && WSA_IO_PENDING == WSAGetLastError())
		{
			// Success
		}
		else
		{
			OnClose(ioSend);
		}
	}
	else
	{
		_DeAllocIoUnit(ioSend);
	}
}


void CiocpServer::OnClose(CIOUnit* InIO)
{
	CSocket* sock = InIO->GetSocket();
	CSocketManager::Get()->OnDisConnect(sock);
	
	_DeAllocIoUnit(InIO);
}

void CiocpServer::StopNetWork()
{
	// StopWorker 원자식으로 변경필요함
	StopWorker();
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

void CiocpServer::_DeAllocIoUnit(CIOUnit * InIO)
{
	switch (InIO->GetIOType())
	{
	case IO_TYPE::ACEEPT:
		delete static_cast<CIOAcceptBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIOAccept*>(InIO);
		break;
	case IO_TYPE::RECV:
		InIO->GetPeer()->DeCrease();
		delete static_cast<CIORecvBuffer*>(InIO->GetIOBuffer());
		delete static_cast<CIORecv*>(InIO);
		break;
	case IO_TYPE::SEND:
		InIO->GetPeer()->DeCrease();
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

NAMESPACE_END