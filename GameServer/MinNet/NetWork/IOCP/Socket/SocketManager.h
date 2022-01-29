#pragma once

#include "../../../MinNetCommon.h"

MINNET_BEGINE

class CSocket;

class CSocketManager
{
private:
	CSocketManager();
	~CSocketManager();

	static CSocketManager* instance;

public:
	static CSocketManager* Get();
	static void Purge();

	void InitSocket(int InCount, int InNextCount);
	
	CSocket* GetSocket(); 
	void ReturnSocket(CSocket* InSock);

private:
	void _AllocSocket(int InCount);

private:
	CRITICAL_SECTION mCS;
	std::queue<CSocket*> mSocketQueue;
	int mSocketMaxCount;
	int mNextCount;
};

MINNET_END