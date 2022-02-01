
#include "LoginNetWork.h"

CLoginNetWork* CLoginNetWork::instance = nullptr;

CLoginNetWork::CLoginNetWork()
{

}

CLoginNetWork::~CLoginNetWork()
{
}

CLoginNetWork * CLoginNetWork::Get()
{
	if (nullptr == instance)
		instance = new CLoginNetWork();

	return instance;
}

void CLoginNetWork::Purge()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

bool CLoginNetWork::InitLoginNetWork(int InPort, int InThreadCount, int InSocketCount)
{
	//return InitNetWork(InPort, InThreadCount, InSocketCount);
	return false;
}

void CLoginNetWork::StopLoginNetWork()
{
	StopNetWork();
}
