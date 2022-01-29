#pragma once

#include "../../../MinNetCommon.h"

MINNET_BEGINE

class CSocket
{
public:
	CSocket(int InIndex);
	~CSocket();

public:
	void OnCreateSocket();
	void OnCloseSocket();

private:
	SOCKET mSock;
	int mIndex;
};

MINNET_END