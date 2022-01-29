#pragma once
#include "IOUnit.h"

MINNET_BEGINE

class CIORecv : public CIOUnit, public CObjectManager<CIORecv>
{
public:
	CIORecv() : CIOUnit(IO_TYPE::RECV)
	{

	}
	virtual ~CIORecv()
	{

	}
};

MINNET_END