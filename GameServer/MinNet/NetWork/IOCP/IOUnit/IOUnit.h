#pragma once

#include "../../../MinNetCommon.h"
#include "IOBuf.h"
#include "../Socket/Socket.h"

MINNET_BEGINE

class CIOUnit : public OVERLAPPED
{
public:
	CIOUnit(IO_TYPE InType)
	{
		mType = InType;

		switch (mType)
		{
		case IO_TYPE::ACEEPT:
			mBufferInterface = new CIOAccpetBuffer();
			break;
		case IO_TYPE::RECV:
			mBufferInterface = new CIORecvBuffer();
			break;
		case IO_TYPE::SEND:
			mBufferInterface = new CIOAccpetBuffer();
			break;
		case IO_TYPE::CLOSE:
			break;
		}

		InitOverlapped();
	}
	virtual ~CIOUnit() {}

public:
	inline CSocket* GetSocket() { return mSock; }
	inline CIOBufferInterface* GetIOBuffer() { return mBufferInterface; }

	void SetSocket(CSocket* InSock)
	{
		mSock = InSock;
	}

private:
	void InitOverlapped()
	{
		ZeroMemory((OVERLAPPED*)this, sizeof(OVERLAPPED));
	}

private:
	IO_TYPE mType;
	CSocket* mSock;
	CIOBufferInterface* mBufferInterface;
};

MINNET_END