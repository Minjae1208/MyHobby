#pragma once

#include "../../../MinNetCommon.h"

NAMESPACE_BEGINE(MinNet)

class CSafeRefCount
{
protected:
	CSafeRefCount()
	{
		mRefCount = 0;
	}

	virtual ~CSafeRefCount()
	{

	}

	LONG64 GetRefCount() { return mRefCount; }

	void IncreaseRefCount()
	{
		InterlockedIncrement64(&mRefCount);
	}

	LONG64 DecreaseRefCount()
	{
		InterlockedDecrement64(&mRefCount);
		return mRefCount;
	}


private:
	LONG64 mRefCount;
};

NAMESPACE_END