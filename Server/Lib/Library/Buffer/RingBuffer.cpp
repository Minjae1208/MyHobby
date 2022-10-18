
#include "pch.h"
#include "RingBuffer.h"

CRingBuffer::CRingBuffer(char* pBuffer, size_t size)
{
	this->buffer = pBuffer;
	this->size = size;
}

CRingBuffer::~CRingBuffer()
{
	buffer = nullptr;
}

char* CRingBuffer::GetBuffer()
{
	return buffer;
}

bool CRingBuffer::ReadData(char* pData, size_t len)
{
	if (len > GetLength())
		return false;

	if (len < size - read_pos)
	{
		memcpy(pData, buffer + read_pos, len);
	}
	else
	{
		int32 first_pos = size - read_pos;
		int32 second_pos = len - first_pos;

		memcpy(pData, buffer + read_pos, first_pos);
		if (second_pos > 0)
			memcpy(pData + first_pos, buffer, second_pos);
	}

	// Read Position Setting
	read_pos = (read_pos + len) % size;

	return true;
}

bool CRingBuffer::WriteData(char* pData, size_t len)
{
	if (len <= 0)
		return false;
		
	if (len + write_pos >= size)
	{
		int32 first_pos = size - write_pos;
		int32 second_pos = len - first_pos;

		memcpy(buffer + write_pos, pData, first_pos);
		if (second_pos > 0)
			memcpy(buffer, pData + first_pos, second_pos);
	}
	else
	{
		memcpy(buffer + write_pos, pData, len);
	}

	// Write Position Setting
	write_pos = (write_pos + len) % (int32)size;

	return true;
}

int32 CRingBuffer::GetLength()
{
	int32 len = write_pos - read_pos;
	if (len < 0)
		len = size + len;
	return len;
}
