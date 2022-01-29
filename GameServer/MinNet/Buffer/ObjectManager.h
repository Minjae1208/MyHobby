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
	
	static void InitObjectManager(size_t InSize, int InBufCount, int InNextBufCount)
	{
		mBuffer->Init(BUF_DEALLOC_TYPE::NON_CHECK, InSize, InBufCount, InNextBufCount);

		isAlloc = true;
	}

	static void* operator new(size_t InSize)
	{
		char* ptr = nullptr;

		if (true == isAlloc)
		{
			ptr = mBuffer.Pop();
		}

		return ptr;
	}

	static void operator delete(void* InObject)
	{
		if (true == isAlloc)
		{
			mBuffer.Push((char*)InObject);
		}
	}

private:
	static CFixedBuffer mBuffer;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CObjectManager<T>::mBuffer;
template<typename T> bool CObjectManager<T>::isAlloc = false;

MINNET_END