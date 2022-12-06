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

template<typename T>
class CStream
{
public:
	typedef std::shared_ptr<CStream<T>>		Shared;
	typedef std::weak_ptr<CStream<T>>		Weak;

public:
	CStream(uint16 InSize = _default)
	{
		Clear();
		_buffer.reserve(InSize);
		typename T::Header h;
		Write((uint8*)&h, sizeof(T::Header), false);
		_read = _header.init(_buffer.data());
	}

	CStream(uint8* pInData, uint16 InSize)
	{
		if (pInData != nullptr)
		{
			Clear();
			Write(pInData, InSize, false);
			_read = _header.init(_buffer.data());
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
	void SetSize(uint16 InSize) { _header.header->size = InSize; }
	uint16 GetSize() { return _header.header->size; }

	void SetTag(uint16 InTag) { _header.header->tag = InTag; }
	uint16 GetTag() { return _header.header->tag; }

	void SetUid(uint64 InUid) { _header.header->uid = InUid; }
	uint64 GetUid() { return _header.header->uid; }

	void SetRes(uint8 InRes) { _header.header->res = InRes; }
	uint8 GetRes() { return _header.header->res; }


// ===============================================
// Write
// ===============================================
	void Write(uint8* pInData, int16 InLen, bool adder = true)
	{
		for (int16 i = 0; i < InLen; i++)
			Write(pInData[i], adder);
	}

	template<typename P>
	void Write(P InData, bool adder = true)
	{
		uint16 len = sizeof(InData);
		if (_buffer.size() < _write + len)
			_buffer.resize(_write + len);
		
		memcpy(&_buffer[_write], (uint8*)&InData, len);
		_write += len;
		if(adder)
			SetSize(_write);
	}

// ===============================================
// Read
// ===============================================
	template<typename R>
	R Read()
	{
		R data = Read<R>(_read);
		_read += sizeof(R);
		return data;
	}

	template<typename R>
	R Read(uint16 InIndex)
	{
		R data;
		if (InIndex + sizeof(R) <= _buffer.size())
		{
			memcpy(&data, (uint8*)&_buffer[InIndex], sizeof(R));
			return data;
		}
		return 0;
	}

// ===============================================
// Buffer
// ===============================================
	void CopyData(uint8* pInData, uint16 InSize)
	{
		if (pInData != nullptr)
		{
			_buffer.resize(InSize);
			_read = _header.init(&_buffer[0]);
			Write(pInData, InSize);
		}
	}

	uint8* GetData()
	{
		return &_buffer[0];
	}

// ===============================================
// Stream
// ===============================================
	void WriteData(uint8* pInData, uint16 InSize, bool adder = true)
	{
		// Setting Write Size
		Write(InSize, adder);
		// Write Data
		Write(pInData, InSize, adder);
	}

	template<typename P>
	void WriteValue(P value) { Write(value); }

	void ReadData(uint8* pInData)
	{
		// Setting Read Size
		uint16 size = Read<uint16>();
		// Copy By size
		memcpy(pInData, &_buffer[_read], size);
		_read += size;
	}

	template<typename R>
	void ReadValue(R& value) { value = Read<R>(); }

private:
	static const uint16 _default = 4096;

	T _header;
	uint16 _read;
	uint16 _write;
	std::vector<uint8> _buffer;
};

typedef CStream<CServerHeader> SStream;
