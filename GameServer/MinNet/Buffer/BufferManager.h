#pragma once

#include "../MinNetCommon.h"
#include "FixedBuffer.h"

MINNET_BEGINE

template <typename T>
class CBufferManager
{
public:
	CBufferManager();
	~CBufferManager();

	static void InitBufferManager(ULONG InSize, int InBufCount, int InNextBufCount)
	{
		mBuf->Init(BUF_DEALLOC_TYPE::NON_CHECK, InSize, InBufCount, InNextBufCount);

		isAlloc = true;
	}
	
	static void* PopMemory()
	{
		char* ptr = nullptr;
		if (true == isAlloc)
		{
			ptr = mBuf.Pop();
		}

		return ptr;
	}

	static void PushMemory(char* InMem)
	{
		if (true == isAlloc)
		{
			mBuf.Push(InMem);
		}
	}


private:
	static CFixedBuffer mBuf;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CBufferManager<T>::mBuf;
template<typename T> bool CBufferManager<T>::isAlloc = false;


MINNET_END

