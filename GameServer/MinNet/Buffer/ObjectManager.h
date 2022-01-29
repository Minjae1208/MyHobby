#pragma once
#include "../MinNetCommon.h"
#include "FixedBuffer.h"

MINNET_BEGINE

template <typename T>
class CObjectManager
{
public:
	CObjectManager()
	{
		
	}

	~CObjectManager()
	{

	}
	
	static void InitObjectBuf(size_t InSize, int InBufCount, int InNextBufCount)
	{
		mObjectBuf->Init(BUF_DEALLOC_TYPE::NON_CHECK, InSize, InBufCount, InNextBufCount);

		isAlloc = true;
	}

	static void* operator new(size_t InSize)
	{
		char* ptr = nullptr;

		if (true == isAlloc)
		{
			ptr = mObjectBuf.Pop();
		}

		return ptr;
	}

	static void operator delete(void* InObject)
	{
		if (true == isAlloc)
		{
			mObjectBuf.Push(InObject);
		}
	}

private:
	static CFixedBuffer mObjectBuf;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CObjectManager<T>::mObjectBuf;
template<typename T> bool CObjectManager<T>::isAlloc = false;

MINNET_END