
#include "PeerManager.h"
#include "Peer.h"


NAMESPACE_BEGINE(MinNet)

CPeerManager* CPeerManager::instance = nullptr;

CPeerManager::CPeerManager()
{
	InitializeCriticalSection(&mPeerCS);
}

CPeerManager::~CPeerManager()
{
	DeleteCriticalSection(&mPeerCS);
}

CPeerManager * CPeerManager::Get()
{
	if (nullptr == instance)
		instance = new CPeerManager();

	return instance;
}

void CPeerManager::Purge()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

/**
	@brief 
	@param InIndex
*/
CPeer * CPeerManager::ConnectPeer(int InIndex)
{
	CPeer* peer = new CPeer();
	
	EnterCriticalSection(&mPeerCS);
	mConnectPeer.insert({ InIndex, peer });
	LeaveCriticalSection(&mPeerCS);

	return peer;
}

/**
	@brief 소유권 포기
	@param InIndex 
*/
void CPeerManager::DisConnectPeer(int InIndex)
{
	EnterCriticalSection(&mPeerCS);
	mConnectPeer[InIndex]->DisConnect();
	mConnectPeer.erase(InIndex);
	LeaveCriticalSection(&mPeerCS);
}

NAMESPACE_END