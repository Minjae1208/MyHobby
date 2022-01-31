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

	}

	inline char* GetMemory() { return mBuf; }
	inline LPWSABUF GetWsaBufPtr() { return &mWsaBuf; }

	void SetBuffer(void* InData, ULONG InSize)
	{

	}

};

class CIOCloseBuffer : public CIOBufferInterface
{
public:
	CIOCloseBuffer() {}
	virtual ~CIOCloseBuffer() {}
};

MINNET_END