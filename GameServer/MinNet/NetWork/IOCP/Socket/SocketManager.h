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

	void OnConnect(CSocket* InSock);
	void OnDisConnect(CSocket* InSock);

private:
	void _AllocSocket(int InCount);

private:
	CRITICAL_SECTION mCS;
	CRITICAL_SECTION mUsingCS;
	std::queue<CSocket*> mSocketQueue;
	
	int mSocketMaxCount;
	int mNextCount;

	std::atomic<int> mKey;
	std::map<int, CSocket*> mUsingSocket;
};

MINNET_END