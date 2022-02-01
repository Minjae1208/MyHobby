#pragma once

#include "../MinNetCommon.h"
#include "FixedBuffer.h"

MINNET_BEGINE

template <typename T>
class CBufferManager
{
public:
	CBufferManager() {}
	~CBufferManager() {}


	/**
		@brief Buffer Manager를 초기화해주는 함수
		@param InSize : Buffer를 쪼갤 사이즈
		@param InBufCount : 초기화 할 개수
		@param InNextBufCount : 추가 Alloc을 할때 개수
	*/
	static void InitBufferManager(ULONG InSize, int InBufCount, int InNextBufCount)
	{
		mBuffer.Init(BUF_DEALLOC_TYPE::NON_CHECK, InSize, InBufCount, InNextBufCount);

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

	static void ClearBufferManager()
	{

	}


private:
	static CFixedBuffer mBuffer;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CBufferManager<T>::mBuffer;
template<typename T> bool CBufferManager<T>::isAlloc = false;


MINNET_END

