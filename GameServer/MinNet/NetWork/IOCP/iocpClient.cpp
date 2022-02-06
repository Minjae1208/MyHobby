#include "iocpClient.h"

#include "Socket/Socket.h"
#include "Socket/SocketManager.h"

#include "IOUnit/IOAccept.h"
#include "IOUnit/IORecv.h"
#include "IOUnit/IOSend.h"
#include "IOUnit/IOClose.h"

NAMESPACE_BEGINE(MinNet)

CiocpClient::CiocpClient()
{

}

CiocpClient::~CiocpClient()
{

}

bool CiocpClient::InitNetWork(int InPort, int InWorkerCount)
{
	if (false == _StartUp())
		return false;

	if (false == _CreateSocket())
		return false;

	if (false == _Bind(InPort))
		return false;

	if (false == _Handle())
		return false;

	if (false == _WsaIoCtl(WSAID_CONNECTEX))
		return false;

	if (false == _ConnectEx())
		return false;

	InitWorker(InWorkerCount);

	return true;
}

void CiocpClient::_WorkerFunc()
{
	DWORD dw = 0;
	ULONGLONG key = 0;
	CIOUnit* ioUnit = NULL;
	bool result;

	while (GetState())
	{
		result = GetQueuedCompletionStatus(mIOCP, &dw, (PULONG_PTR)&key, (LPOVERLAPPED*)&ioUnit, INFINITE);

		if (false == result)
		{
			// DisConnect
			OnClose(ioUnit);
		}
		else if (true == result && 0 == dw)
		{
			if (IO_TYPE::ACEEPT == ioUnit->GetIOType())
			{
				// Connect
				OnConnect(ioUnit);
			}
			else
			{
				// DisConnect
				OnClose(ioUnit);
			}
		}
		else
		{
			if (IO_TYPE::RECV == ioUnit->GetIOType())
			{
				//RECV
			}
			else if (IO_TYPE::SEND == ioUnit->GetIOType())
			{
				//SEND
			}
		}

		if (nullptr != ioUnit && IO_TYPE::SEND != ioUnit->GetIOType())
		{
			_DeAllocIoUnit(ioUnit);
		}
	}
}

void CiocpClient::OnConnect(CIOUnit * InIO)
{

}

void CiocpClient::OnRecv(CIOUnit * InIO, DWORD InLen)
{

}

void CiocpClient::OnSend(CIOUnit * InIO, DWORD InLen)
{
}

void CiocpClient::OnClose(CIOUnit * InIO)
{
	CSocket* sock = InIO->GetSocket();

	_DeAllocIoUnit(InIO);
}

void CiocpClient::StopNetWork()
{
	StopWorker();
}

bool CiocpClient::_StartUp()
{
	WSADATA wsa;
	if(0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return false;

	return true;
}

bool CiocpClient::_CreateSocket()
{
	mSock = new CSocket();

	if (nullptr == mSock)
		return false;

	return true;
}

bool CiocpClient::_Bind(int InPort)
{
	inet_pton(AF_INET, "127.0.0.1", &mAddr.sin_addr);
	mAddr.sin_family = AF_INET;

	if (0 != ::bind(mSock->GetSocket(), (SOCKADDR*)&mAddr, sizeof(SOCKADDR_IN)))
		return false;

	mAddr.sin_port = InPort;

	return true;
}

bool CiocpClient::_Handle()
{
	mIOCP = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, NULL, 0);

	if (INVALID_HANDLE_VALUE == mIOCP)
		return false;

	mIOCP = CreateIoCompletionPort((HANDLE)mSock->GetSocket(), mIOCP, 0, 0);

	return true;
}

bool CiocpClient::_WsaIoCtl(GUID InGuid)
{
	DWORD dw = 0;
	int err = WSAIoctl(mSock->GetSocket(), SIO_GET_EXTENSION_FUNCTION_POINTER,
		&InGuid, sizeof(InGuid),
		&mConEx, sizeof(mConEx),
		&dw, NULL, NULL);

	if (0 != err)
		return false;

	return true;
}

bool CiocpClient::_ConnectEx()
{
	CIOAccept* ioAccept = new CIOAccept(mSock);
	if (nullptr == ioAccept)
		return false;

	if (FALSE == mConEx(mSock->GetSocket(), (SOCKADDR*)&mAddr, sizeof(SOCKADDR_IN), NULL, NULL, NULL, ioAccept->GetOverlappedPtr()))
		return false;

	return true;
}

void CiocpClient::_DeAllocIoUnit(CIOUnit * InIO)
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



NAMESPACE_END