#pragma once

#include "../../MinNetCommon.h"
#include "Worker/iocpWorker_std.h"


MINNET_BEGINE

typedef CiocpWorker_std CiocpWorker;

class CiocpServer : public CiocpWorker
{
public:
	CiocpServer();
	virtual ~CiocpServer();

	bool InitNetWork(int InPort, int InWorkerCount, int InSocketCount);

protected:
	virtual void _WorkerFunc();

private:
	bool _Bind();
	bool _Listen();
	bool _Handle();
	


private:
	HANDLE mIOCP;
	// listen Socket
	SOCKET mSock;
	SOCKADDR_IN mAddr;
};

MINNET_END