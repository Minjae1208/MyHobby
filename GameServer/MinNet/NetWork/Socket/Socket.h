#pragma once

#include "../../MinNetCommon.h"

MINNET_BEGINE

class CSocket
{
public:
	CSocket();
	~CSocket();

public:
	void OnCreateSocket();
	void OnCloseSocket();

private:
	SOCKET mSock;
};

MINNET_END