#pragma once

#include "IOUnit.h"

MINNET_BEGINE

class CIOSend : public CIOUnit, public CObjectManager<CIOSend>
{
public:
	CIOSend(CSocket* InSock) : CIOUnit(IO_TYPE::SEND, InSock)
	{

	}
	virtual ~CIOSend()
	{

	}
};

MINNET_END