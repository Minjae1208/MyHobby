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

class CIOAccpetBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
{
public:
	CIOAccpetBuffer()
	{
		mBufSize = GetBufferSize();
		mBuf = (char*)PopMemory();
	}
	virtual ~CIOAccpetBuffer()
	{
		PushMemory(mBuf);
	}

};

class CIORecvBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
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
class CIOSendBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
{
public:
	CIOSendBuffer()
	{
		mBufSize = GetBufferSize();
		mBuf = (char*)PopMemory();
	}
	virtual ~CIOSendBuffer()
	{

	}

	inline char* GetMemory() { return mBuf; }
	inline LPWSABUF GetWsaBufPtr() { return &mWsaBuf; }

	void SetBuffer(void* InData, ULONG InSize)
	{

	}

};

MINNET_END