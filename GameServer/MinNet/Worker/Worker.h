#pragma once
#include "../MinNetCommon.h"

MINNET_BEGINE

class CWorker
{
public:
	CWorker();
	virtual ~CWorker();

	bool InitWorker();
	
private:
	HANDLE mEvent;

};

MINNET_END