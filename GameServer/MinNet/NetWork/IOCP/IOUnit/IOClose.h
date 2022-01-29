#pragma once
#include "IOUnit.h"

MINNET_BEGINE

class CIOClose : public CIOUnit, public CObjectManager<CIOClose>
{
public:
	CIOClose() : CIOUnit(IO_TYPE::CLOSE)
	{

	}
	virtual ~CIOClose()
	{

	}
};

MINNET_END