
#include "pch.h"
#include "BufferManager.h"

#include "Buffer.h"

CBufferManager::CBufferManager()
{

}

CBufferManager::~CBufferManager()
{

}

void CBufferManager::MakeBuffer(size_t size, int32 count)
{
	iter it = buffers.find(size);
	if(it == buffers.end())
	{
		CBuffer* buffer = new CBuffer(size, count);
		buffers.insert({ size, buffer });
	}
}

char* CBufferManager::Get(size_t size)
{
	iter it = buffers.find(size);
	if (it != buffers.end())
	{
		return it->second->Pop();
	}
	else
	{
		// error
		return nullptr;
	}
}

bool CBufferManager::Put(char* pData, size_t size)
{
	iter it = buffers.find(size);
	if (it != buffers.end())
	{
		it->second->Push(pData);
	}
	
	return false;
}
