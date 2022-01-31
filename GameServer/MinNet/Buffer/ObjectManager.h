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
		@brief Object Manager�� �ʱ�ȭ���ִ� �Լ�
		@param InBufCount : �ʱ�ȭ �� ����
		@param InNextBufCount : �߰� Alloc�� �Ҷ� ����
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
		@brief Object Manager ��� ����
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