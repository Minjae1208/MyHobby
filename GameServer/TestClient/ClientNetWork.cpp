#include "ClientNetWork.h"

CNetWorkCE* CNetWorkCE::instance = nullptr;

CNetWorkCE::CNetWorkCE()
{
}

CNetWorkCE::~CNetWorkCE()
{
}

CNetWorkCE * CNetWorkCE::Get()
{
	if (nullptr == instance)
		instance = new CNetWorkCE();

	return instance;
}

void CNetWorkCE::Purge()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool CNetWorkCE::InitClientNetWork(int InPort, int InWorkerCount)
{
	return InitNetWork(InPort, InWorkerCount);
}

void CNetWorkCE::StopClientNetWork()
{
	StopNetWork();
}
