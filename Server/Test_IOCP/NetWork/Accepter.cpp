#include "pch.h"
#include "Accepter.h"
#include "NetWork.h"

CAccepter::CAccepter()
{
}

CAccepter::~CAccepter()
{
}

void CAccepter::StartAccepter()
{
	worker = std::thread(WorkerRun, this);
}

void CAccepter::WorkerRun(CAccepter* pThis)
{
	pThis->AccepterRun();
	printf_s("Accepter 종료");
}

void CAccepter::AccepterRun()
{
	while (true)
	{
		

		// permits an incoming connection attempt on a socket
		// Link : https://learn.microsoft.com/en-us/windows/win32/api/winsock2/nf-winsock2-accept
		SOCKET new_client = accept(CNetWork::Instance()->listen_socket, NULL, NULL);
		if (new_client == INVALID_SOCKET)
		{
			printf_s("연결 실패");
			return;
		}
		else
		{
			printf_s("연결 성공");
			return;
		}

		return;
	}
}
