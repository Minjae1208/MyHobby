#pragma once
#include "IOUnit.h"


MINNET_BEGINE

class CIOAccept : public CIOUnit, public CObjectManager<CIOAccept>
{
public:
	CIOAccept(CSocket* InSock) : CIOUnit(IO_TYPE::ACEEPT, InSock)
	{
		
	}
	virtual ~CIOAccept()
	{

	}

};

MINNET_END