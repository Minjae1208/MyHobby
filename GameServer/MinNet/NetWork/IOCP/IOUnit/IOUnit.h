#pragma once

#include "../../../MinNetCommon.h"
#include "IOBuf.h"
#include "../../Socket/Socket.h"

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
			mBuf = new CIOAccpetBuffer();
			break;
		case IO_TYPE::RECV:
			mBuf = new CIORecvBuffer();
			break;
		case IO_TYPE::SEND:
			mBuf = new CIOAccpetBuffer();
			break;
		case IO_TYPE::CLOSE:
			break;
		}

		InitOverlapped();
	}
	~CIOUnit() {}

public:
	inline LPWSABUF GetWsaBufPtr() { return &mWsaBuf; }
	inline CSocket* GetSocket() { return mSock; }
	inline CIOBufferInterface* GetIOBuffer() { return mBuf; }

	void SetSocket(CSocket* InSock)
	{
		mSock = InSock;
	}

private:
	void InitOverlapped()
	{
		//ZeroMemory((OVERLAPPED)this, sizeof(OVERLAPPED));
	}

private:
	IO_TYPE mType;
	CSocket* mSock;
	WSABUF mWsaBuf;
	CIOBufferInterface* mBuf;
};

MINNET_END