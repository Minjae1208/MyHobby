#include "pch.h"
#include "Starter.h"
#include "NetWork/NetWork.h"

CStarter::CStarter()
{
}

CStarter::~CStarter()
{
}

void CStarter::Start()
{
	CNetWork::Instance()->Start();
}
