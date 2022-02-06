
#include "LoginService.h"

#include "NetWork/IOCP/ServerManager.h"
#include "../Login_NetWork/LoginNetWork.h"

void CLoginService::Constructor()
{
	MinNet::CServerManager::Constructor();
	CLoginNetWork::Get()->InitLoginNetWork(9000, 1, 10);
}

void CLoginService::Distrucotr()
{
	CLoginNetWork::Get()->StopLoginNetWork();
	MinNet::CServerManager::Destructor();
}