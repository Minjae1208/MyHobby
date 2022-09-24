#pragma once

#include "Type.h"

#include <vector>

class CServerHeader
{
public:
#pragma pack(1)
	struct Header
	{
		Header()
		{
			size = sizeof(Header);
			tag = 0;
			uid = 0;
			res = 0;
		}

		uint16 size;
		uint16 tag;
		uint64 uid;
		uint8 res;
	};
#pragma pack()

public:
	CServerHeader() {}
	uint16 init(uint8* pInBuffer)
	{
		header = (Header*)pInBuffer;
		return sizeof(Header);
	}

	Header* header = nullptr;

};

class CDBHeader
{
public:
#pragma pack(1)
	struct Header
	{
		Header()
		{
			size = sizeof(Header);
			tag = 0;
			uid = 0;
			res = 0;
		}

		uint16 size;
		uint16 tag;
		uint64 uid;
		uint8 res;
	};
#pragma pack()
};

template<typename T>
class CStream
{
public:
	typedef std::shared_ptr<CStream<T>>		Shared;
	typedef std::weak_ptr<CStream<T>>		Weak;

public:
	CStream(uint16 InSize = _default)
	{

	}

	CStream(uint8* pInData, uint16 InSize)
	{
		if (pInData != nullptr)
		{
			Clear();
			Write(pInData[i], InSize, false);
			_read = _header->init(_buffer.data());
		}
	}

	~CStream() {}

	void Clear()
	{
		_read = 0;
		_write = 0;
		_buffer.clear();
	}



// ===============================================
// Header
// ===============================================
	void SetSize(uint16 InSize) { _header->size = InSize; }
	uint16 GetSize() { return _header->size; }

	void SetTag(uint16 InTag) { _header->tag = InTag; }
	uint16 GetTag() { return _header->tag; }

	void SetUid(uint64 InUid) { _header->uid = InUid; }
	uint64 GetUid() { return _header->uid; }

	void SetRes(uint8 InRes) { _header->res = InRes; }
	uint8 GetRes() { return _header->res; }


// ===============================================
// Write
// ===============================================
	void Write(uint8 InData, int16 InLen, bool InAdd)
	{
		for (int16 i = 0; i < InLen; i++)
			Write(InData, InAdd);
	}

	void Write(uint8 InData, bool InAdd)
	{
		uint16 len = (uint16)sizeof(InData);
		if (_buffer.size() < _write + len)
			_buffer.resize(_write + len);
		memcpy(&_buffer[_write], (uint8*)&InData, len);
		_write += len;
		if(InAdd)
			SetSize(_write);
	}

// ===============================================
// Read
// ===============================================
	template<typename T>
	T Read()
	{
		T data = Read(_read);
		_read += sizeof(T);
		return data;
	}

	T Read(uint16 InIndex)
	{
		T data;
		if (InIndex + sizeof(T) <= _buffer.size())
		{
			memcpy(&data, (uint8*)&_buffer[InIndex], sizeof(T));
			return data;
		}
		return 0;
	}

// ===============================================
// Stream
// ===============================================
	void WriteBuffer(uint8* InBuffer, uint16 InSize)
	{
		// Setting Write Size
		Write(InSize, true);
		// Write Data
		Write(InBuffer, InSize, true);
	}
	void ReadBuffer(uint8* InBuffer)
	{
		// Setting Read Size
		uint16 size = read<uint16>();
		// Copy By size
		memcpy(InBuffer, &_buffer[_read], size);
		_read += size;
	}

private:
	static const uint16 _default = 4096;

	T _header;
	uint16 _read;
	uint16 _write;
	std::vector<uint8> _buffer;
};

typedef CStream<CServerHeader> ServerStream;
typedef CStream<CDBHeader> DBStream;
