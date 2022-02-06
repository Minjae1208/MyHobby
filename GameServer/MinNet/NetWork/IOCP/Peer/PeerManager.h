#pragma once

#include "../../../MinNetCommon.h"

NAMESPACE_BEGINE(MinNet)

class CPeer;

class CPeerManager
{
private:
	CPeerManager();
	~CPeerManager();

	static CPeerManager* instance;

public:
	static CPeerManager* Get();
	static void Purge();
	
	CPeer* ConnectPeer(int InIndex);
	void DisConnectPeer(int InIndex);

private:
	CRITICAL_SECTION mPeerCS;
	std::unordered_map<int, CPeer*> mConnectPeer;
};


NAMESPACE_END