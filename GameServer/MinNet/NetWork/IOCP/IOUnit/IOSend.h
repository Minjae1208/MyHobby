#pragma once

#include "IOUnit.h"

MINNET_BEGINE

class CIOSend : public CIOUnit, public CObjectManager<CIOSend>
{
public:
	CIOSend() : CIOUnit(IO_TYPE::SEND)
	{

	}
	virtual ~CIOSend()
	{

	}
};

MINNET_END