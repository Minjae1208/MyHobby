#pragma once
#include "IOUnit.h"


MINNET_BEGINE

class CIOAccpet : public CIOUnit, public CObjectManager<CIOAccpet>
{
public:
	CIOAccpet() : CIOUnit(IO_TYPE::ACEEPT)
	{
		
	}
	~CIOAccpet();

};

MINNET_END