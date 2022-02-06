#pragma once

#include "../../../MinNetCommon.h"
#include "IOBuffer.h"
#include "../Socket/Socket.h"
#include "../Peer/Peer.h"

MINNET_BEGINE

class CIOUnit : public OVERLAPPED
{
public:
	CIOUnit(IO_TYPE InType, CSocket* InSock)
	{
		mSock = InSock;
		mType = InType;
		
		switch (mType)
		{
		case IO_TYPE::ACEEPT:
			mBufferInterface = new CIOAcceptBuffer();
			break;
		case IO_TYPE::RECV:
			mBufferInterface = new CIORecvBuffer();
			break;
		case IO_TYPE::SEND:
			mBufferInterface = new CIOSendBuffer();
			break;
		case IO_TYPE::CLOSE:
			mBufferInterface = new CIOCloseBuffer();
			break;
		}

		InitOverlapped();
	}
	virtual ~CIOUnit() {}

public:
	inline CSocket* GetSocket() { return mSock; }
	inline LPOVERLAPPED GetOverlappedPtr() { return (LPOVERLAPPED)this; }
	inline CIOBufferInterface* GetIOBuffer() { return mBufferInterface; }
	inline IO_TYPE GetIOType() { return mType; }

	void SetPeer(CPeer* InPeer)
	{
		mPeer = InPeer;
		mPeer->SetIOUnit(this);
		mPeer->InCrease();
	}
	inline CPeer* GetPeer() { return mPeer; }

private:
	void InitOverlapped()
	{
		ZeroMemory((OVERLAPPED*)this, sizeof(OVERLAPPED));
	}

private:
	IO_TYPE mType;
	CSocket* mSock;
	CIOBufferInterface* mBufferInterface;
	CPeer* mPeer;
};

MINNET_END