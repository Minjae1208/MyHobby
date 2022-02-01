#pragma once

#include "../../../MinNetCommon.h"

MINNET_BEGINE

class CSocket
{
public:
	CSocket(int InIndex);
	~CSocket();

	inline SOCKET GetSocket() { return mSock; }
	inline int GetIndex() { return mIndex; }

	void OnCreateSocket();
	bool IsConnect();
	void OnConnectSocket();
	void OnCloseSocket();
	

private:
	enum class SOCKET_STATE
	{
		CONNECT,
		DISCONNECT,
	};

private:
	SOCKET mSock;
	int mIndex;
	SOCKET_STATE mState;
};

MINNET_END