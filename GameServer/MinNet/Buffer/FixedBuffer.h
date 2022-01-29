#pragma once
#include "../MinNetCommon.h"


MINNET_BEGINE

class CFixedBuffer
{
public:
	CFixedBuffer();
	~CFixedBuffer();

public:
	void Init(BUF_DEALLOC_TYPE InType, ULONG InSize, int InBufCount, int InBufNextCount);
	ULONG GetFixedSize();

	char* Pop();
	void Push(char* InBuf);

private:
	void _Alloc(int InCount);
	void _DeAlloc();
	void _Join();

private:
	CRITICAL_SECTION mBufCS;
	BUF_DEALLOC_TYPE mType;

	ULONG mBufSize;
	int mNextBufCount;
	int mBufMaxCount;
	int mBufIndex; 

	std::vector<char*> mFixedBuf;
	std::list<char*> mOriginBuf;
};

MINNET_END