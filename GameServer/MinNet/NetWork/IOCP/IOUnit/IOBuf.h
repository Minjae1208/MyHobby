#pragma once

#include "../../../Buffer/ObjectManager.h"
#include "../../../Buffer/BufferManager.h"

MINNET_BEGINE

class CIOBufferInterface : public CObjectManager<CIOBufferInterface>
{
public:
	CIOBufferInterface();
	~CIOBufferInterface();
};

class CIOAccpetBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
{
public:
	CIOAccpetBuffer()
	{
		Buf = (char*)PopMemory();
	}
	~CIOAccpetBuffer();

public:
	char* Buf;
};

class CIORecvBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
{
public:
	CIORecvBuffer()
	{
		Buf = (char*)PopMemory();
	}
	~CIORecvBuffer();

public:
	char* Buf;
};


// Send는 약간 좀 다름
class CIOSendBuffer : public CBufferManager<CIOAccpetBuffer>, public CIOBufferInterface
{
public:
	CIOSendBuffer()
	{
		Buf = (char*)PopMemory();
	}
	~CIOSendBuffer();

public:
	char* Buf;
};

MINNET_END