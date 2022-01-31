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

	/**
		@brief Object Manager를 초기화해주는 함수
		@param InBufCount : 초기화 할 개수
		@param InNextBufCount : 추가 Alloc을 할때 개수
	*/
	static void InitObjectManager(int InBufCount, int InNextBufCount)
	{
		mBuffer.Init(BUF_DEALLOC_TYPE::NON_CHECK, sizeof(T), InBufCount, InNextBufCount);

		isAlloc = true;
	}


	/**
		@brief operator new
	*/
	static void* operator new(size_t InSize)
	{
		char* ptr = nullptr;

		if (true == isAlloc)
		{
			ptr = mBuffer.Pop();
		}

		return ptr;
	}

	/**
		@brief operator delete
	*/
	static void operator delete(void* InObject)
	{
		if (true == isAlloc)
		{
			mBuffer.Push((char*)InObject);
		}
	}

	/**
		@brief Object Manager 사용 종료
	*/
	static void ClearObjectManager()
	{

	}

private:
	static CFixedBuffer mBuffer;
	static bool isAlloc;
};

template<typename T> CFixedBuffer CObjectManager<T>::mBuffer;
template<typename T> bool CObjectManager<T>::isAlloc = false;

MINNET_END