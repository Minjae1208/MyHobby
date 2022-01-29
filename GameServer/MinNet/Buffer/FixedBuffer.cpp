
#include "FixedBuffer.h"

MINNET_BEGINE

CFixedBuffer::CFixedBuffer()
{
	InitializeCriticalSection(&mBufCS);

	mBufSize = 0;
	mNextBufCount = 0;
	mBufMaxCount = 0;
	mBufIndex = 0;
}

CFixedBuffer::~CFixedBuffer()
{
	DeleteCriticalSection(&mBufCS);
}

/**
	@brief Fixed Buffer 초기화
	@param InType : Dealloc 체크
	@param InSize : Buffer의 사이즈
	@param InBufCount : 초기화할 Buffer의 개수
	@param InBufNextCount : Alloc을 더 해야할 경우 생성할 Buffer의 개수	
*/
void CFixedBuffer::Init(BUF_DEALLOC_TYPE InType, ULONG InSize, int InBufCount, int InBufNextCount)
{
	mType = InType;
	mBufSize = InSize;
	mNextBufCount = InBufNextCount;

	_Alloc(InBufCount);
}

ULONG CFixedBuffer::GetFixedSize()
{
	return mBufSize;
}

/**
	@brief Buffer 가져오기
	@return Buffer의 시작 위치를 줌
*/
char * CFixedBuffer::Pop()
{
	char* ptr = nullptr;

	EnterCriticalSection(&mBufCS);

	if (mBufIndex == mBufMaxCount - 1)
	{
		_Alloc(mNextBufCount);
	}

	ptr = mFixedBuf[mBufIndex];
	mBufIndex++;

	LeaveCriticalSection(&mBufCS);

	return ptr;
}

/**
	@brief Buffer 반납하기
	@param 반납할 버퍼의 시작 포인터
*/
void CFixedBuffer::Push(char * InBuf)
{
	EnterCriticalSection(&mBufCS);

	mBufIndex--;
	mFixedBuf[mBufIndex] = InBuf;

	LeaveCriticalSection(&mBufCS);
}

/**
	@brief 버퍼 할당하기
	@param 할당할 버퍼의 개수
*/
void CFixedBuffer::_Alloc(int InCount)
{
	char* buf = new char[mBufSize * InCount];
	char* CurrPtr = buf;

	mFixedBuf.resize(InCount);

	for (int i = mBufMaxCount; i < mBufMaxCount + InCount; i++)
	{
		mFixedBuf[i] = CurrPtr;
		CurrPtr += mBufSize;
	}

	mBufMaxCount += InCount;
	mOriginBuf.push_back(buf);
}


/**
	@brief 버퍼 해제하기
*/
void CFixedBuffer::_DeAlloc()
{
	while (false == mOriginBuf.empty())
	{
		delete mOriginBuf.back();
		mOriginBuf.pop_back();
	}
}

/**
	@brief 버퍼 해제 전 확인
*/
void CFixedBuffer::_Join()
{
	while (true)
	{
		bool result = false;

		EnterCriticalSection(&mBufCS);

		if (0 == mBufIndex)
		{
			result = true;
		}

		if (true == result)
		{
			_DeAlloc();
			LeaveCriticalSection(&mBufCS);
			break;
		}
		else
		{
			LeaveCriticalSection(&mBufCS);
			::Sleep(500);
		}
	}
}




MINNET_END


