﻿#pragma once

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

#include "../../MinNetCommon.h"
#include "Worker/iocpWorker_std.h"

MINNET_BEGINE

typedef CiocpWorker_std CiocpWorker;

class CIOUnit;

class CiocpServer : public CiocpWorker
{
public:
	CiocpServer();
	virtual ~CiocpServer();

	bool InitNetWork(int InPort, int InWorkerCount, int InSocketCount);
	
protected:
	virtual void _WorkerFunc();
	virtual void OnConnect(CIOUnit* InIO);
	virtual void OnRecv(CIOUnit* InIO);
	virtual void OnSend(CIOUnit* InIO);
	virtual void OnClose(CIOUnit* InIO);

private:
	bool _WsaStart();
	bool _Bind(int InPort);
	bool _Listen();
	bool _Handle();

	void DisConnectSocket(CIOUnit* InIO);
	void DeAllocIoUnit(CIOUnit* InIO);

	void _CreateSocket(int InCount);
	void _AcceptExSocket();
private:
	HANDLE mIOCP;
	// listen Socket
	SOCKET mSock;
	SOCKADDR_IN mAddr;
};

MINNET_END