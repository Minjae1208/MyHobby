#pragma once

#include "NetWork/IOCP/iocpClient.h"

class CNetWorkCE : public MinNet::CiocpClient
{
private:
	CNetWorkCE();
	virtual ~CNetWorkCE();

	static CNetWorkCE* instance;

public:
	static CNetWorkCE* Get();
	static void Purge();

	bool InitClientNetWork(int InPort, int InWorkerCount);
	void StopClientNetWork();
};
