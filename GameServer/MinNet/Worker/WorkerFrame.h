#pragma once
#include "../MinNetCommon.h"

MINNET_BEGINE

class CWorkerFrame
{
public:
	CWorkerFrame() {}
	virtual ~CWorkerFrame() {}

	virtual void proc() {}
};

MINNET_END