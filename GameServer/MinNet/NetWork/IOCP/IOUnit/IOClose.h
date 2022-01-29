#pragma once
#include "IOUnit.h"

MINNET_BEGINE

class CIOClose : public CIOUnit, public CObjectManager<CIOClose>
{
public:
	CIOClose() : CIOUnit(IO_TYPE::CLOSE)
	{

	}
	~CIOClose();


private:
	CIOCloseBuffer* mBuf;
};

MINNET_END