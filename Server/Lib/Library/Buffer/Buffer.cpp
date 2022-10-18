
#include "pch.h"
#include "Buffer.h"

CBuffer::CBuffer(size_t size, int count)
{
	this->size = size;
	this->count = count;

	int maxCount = 2000000000 / (int)size;

	// 최대 할당 size를 넘기면 분할해서 해줘아햔담.
	if (maxCount < count)
	{
		int currCount = count;

		while (0 >= currCount)
		{
			int cnt = 0;

			if (maxCount > currCount)	cnt = currCount;
			else						cnt = maxCount;

			_Alloc(cnt);
			currCount -= cnt;
		}
	}
	else
	{
		_Alloc(count);
	}
}

CBuffer::~CBuffer()
{
	for (auto& ptr : origin_ptr)
	{
		if (ptr != nullptr)
			delete ptr;
	}
}

char* CBuffer::Pop()
{
	CLock lock(index_lock);

	if (index > pool.size())
	{
		_Alloc(count/2);
	}
	
	char* ptr = pool[index];
	index++;

	return ptr;
}

void CBuffer::Push(char* pData)
{
	CLock lock(index_lock);

	if (nullptr == pData)
	{
		// error
	}

	index--;
	pool[index] = pData;
}

void CBuffer::_Alloc(int count)
{
	if (count <= 0)
	{
		// error
	}

	char* origin = new char[size * count];
	char* curr = origin;

	pool.resize(total_count + count);
	for (int i = total_count; i < total_count + count; i++)
	{
		pool[i] = curr;
		curr += size;
	}

	origin_ptr.push_back(origin);
}
