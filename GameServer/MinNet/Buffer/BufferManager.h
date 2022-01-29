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
		mBuffer->Init(BUF_DEALLOC_TYPE::NON_CHECK, InSize, InBufCount, InNextBufCount);

		isAlloc = true;
	}
	
	static ULONG GetBufferSize() 
	{ 
		ULONG size = 0;

		if (true == isAlloc)
		{
			size = mBuffer.GetFixedSize();
		}

		return size;
	}

	static void* PopMemory()
	{
		char* ptr = nullptr;
		if (true == isAlloc)
		{
			ptr = mBuffer.Pop();
		}

		return ptr;
	}

	static void PushMemory(char* InMem)
	{
		if (true == isAlloc)
		{
			mBuffer.Push(InMem);
		}
	}


private:
	static CFixedBuffer mBuffer;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CBufferManager<T>::mBuffer;
template<typename T> bool CBufferManager<T>::isAlloc = false;


MINNET_END

