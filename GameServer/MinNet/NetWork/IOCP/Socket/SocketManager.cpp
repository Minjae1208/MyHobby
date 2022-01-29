#include "SocketManager.h"
#include "Socket.h"

MINNET_BEGINE

CSocketManager* CSocketManager::instance = nullptr;

CSocketManager::CSocketManager()
{
	mNextCount = 0;
	mSocketMaxCount = 0;

	InitializeCriticalSection(&mCS);
}

CSocketManager::~CSocketManager()
{
	DeleteCriticalSection(&mCS);
}

CSocketManager * CSocketManager::Get()
{
	if (nullptr == instance)
		instance = new CSocketManager();

	return instance;
}

void CSocketManager::Purge()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void CSocketManager::InitSocket(int InCount, int InNextCount)
{
	mNextCount = InNextCount;

	_AllocSocket(InCount);
}

CSocket * CSocketManager::GetSocket()
{
	CSocket* sock = nullptr;

	EnterCriticalSection(&mCS);

	if (mSocketQueue.size() == 0)
	{
		_AllocSocket(mNextCount);
	}

	sock = mSocketQueue.front();
	mSocketQueue.pop();

	LeaveCriticalSection(&mCS);

	return sock;
}

void CSocketManager::ReturnSocket(CSocket* InSock)
{
	EnterCriticalSection(&mCS);
	mSocketQueue.push(InSock);
	LeaveCriticalSection(&mCS);
}

void CSocketManager::_AllocSocket(int InCount)
{
	for (int i = mSocketMaxCount; i < mSocketMaxCount + InCount; i++)
	{
		CSocket* sock = new CSocket(i);
		mSocketQueue.push(sock);
	}

	mSocketMaxCount += InCount;
}

MINNET_END