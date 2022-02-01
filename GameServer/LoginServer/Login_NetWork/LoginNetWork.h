#pragma once

#include "NetWork/IOCP/iocpServer.h"

class CLoginNetWork : public MinNet::CiocpServer
{
private:
	CLoginNetWork();
	virtual ~CLoginNetWork();

	static CLoginNetWork* instance;

public:
	static CLoginNetWork* Get();
	static void Purge();

	bool InitLoginNetWork(int InPort, int InThreadCount, int InSocketCount);
	void StopLoginNetWork();
};