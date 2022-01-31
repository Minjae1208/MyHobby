#pragma once
#include "IOUnit.h"

MINNET_BEGINE

class CIORecv : public CIOUnit, public CObjectManager<CIORecv>
{
public:
	CIORecv(CSocket* InSock) : CIOUnit(IO_TYPE::RECV, InSock)
	{

	}
	virtual ~CIORecv()
	{

	}
};

MINNET_END