#pragma once

#include "../../../Buffer/ObjectManager.h"
#include "../../../Buffer/BufferManager.h"

MINNET_BEGINE

class CIOBufferInterface : public CObjectManager<CIOBufferInterface>
{
public:
	CIOBufferInterface() {}
	virtual ~CIOBufferInterface() {}

protected:
	char* mBuf;
	WSABUF mWsaBuf;
	ULONG mBufSize;
};

class CIOAcceptBuffer : public CBufferManager<CIOAcceptBuffer>, public CIOBufferInterface
{
public:
	CIOAcceptBuffer()
	{
		mBufSize = GetBufferSize();
		mBuf = (char*)PopMemory();
	}
	virtual ~CIOAcceptBuffer()
	{
		PushMemory(mBuf);
	}

	inline char* GetMemory() { return mBuf; }
	inline void ReturnMemory() { PushMemory(mBuf); }

};

class CIORecvBuffer : public CBufferManager<CIORecvBuffer>, public CIOBufferInterface
{
public:
	CIORecvBuffer()
	{
		mBufSize = GetBufferSize();
		mBuf = (char*)PopMemory();
	}
	virtual ~CIORecvBuffer()
	{

	}

	inline char* GetMemory() { return mBuf; }
	inline void ReturnMemory() { PushMemory(mBuf); }
	inline LPWSABUF GetWsaBufPtr() { return &mWsaBuf; }
};


// Send는 약간 좀 다름
class CIOSendBuffer : public CBufferManager<CIOSendBuffer>, public CIOBufferInterface
{
public:
	CIOSendBuffer()
	{
		mBufSize = GetBufferSize();
		mBuf = (char*)PopMemory();
	}
	virtual ~CIOSendBuffer()
	{
		// 소멸자 필요
	}

	inline char* GetMemory() { return mBuf; }
	inline LPWSABUF GetWsaBufPtr() { return &mWsaBuf; }
	inline int GetUseWsaBufCount() { return (int)mWsaBufVector.size(); }
	inline ULONG GetUseBufSize() { return mUseBufSize; }

	void SetBuffer(void* InData, ULONG InSize)
	{
		mUseBufSize = InSize;

		

	}

	void Compress(ULONG InSize)
	{
		ULONG size = InSize;
		int useCount = GetUseWsaBufCount();
		int Count = 0;

		if (0 == useCount)
		{
			return;
		}

		for (int i = 0; i < useCount; i++)
		{
			if (mWsaBufVector[i].len <= size)
			{
				size -= mWsaBufVector[i].len;
				PushMemory(mBufferVector[i]);
				Count++;
			}
			else
			{
				mWsaBufVector[i].len -= size;
				break;
			}
		}

		mWsaBufVector.erase(mWsaBufVector.begin(), mWsaBufVector.begin() + Count);
		mBufferVector.erase(mBufferVector.begin(), mBufferVector.begin() + Count);

		mUseBufSize -= InSize;
	}

private:
	std::vector<WSABUF> mWsaBufVector;
	std::vector<char*> mBufferVector;
	ULONG mUseBufSize;
};

class CIOCloseBuffer : public CIOBufferInterface
{
public:
	CIOCloseBuffer() {}
	virtual ~CIOCloseBuffer() {}
};

MINNET_END