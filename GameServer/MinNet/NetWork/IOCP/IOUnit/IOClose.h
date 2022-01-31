#pragma once
#include "IOUnit.h"

MINNET_BEGINE

class CIOClose : public CIOUnit, public CObjectManager<CIOClose>
{
public:
	CIOClose(CSocket* InSock) : CIOUnit(IO_TYPE::CLOSE, InSock)
	{

	}
	virtual ~CIOClose()
	{

	}
};

MINNET_END