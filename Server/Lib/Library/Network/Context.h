#pragma once

#include "winsock2.h"

enum class IO_Type
{
	IO_NONE = 0,
	IO_ACCEPT= 0,
	IO_SEND = 0,
	IO_RECV = 0,
	IO_PROC = 0,
};

class CIOUnit;

class CContext
{
private:
	CIOUnit* unit;
	IO_Type type;

public:
	CContext(CIOUnit* pUnit, IO_Type type)
	{
		this->unit = pUnit;
		this->type = type;
	}

	CIOUnit* GetUnit() { return unit; }
	IO_Type GetType() { return type; }
};

class CRIO_Context : public RIO_BUF, public CContext
{
private:

public:
	CRIO_Context(CIOUnit* pUnit, IO_Type type) : CContext(pUnit, type) {};
};

class CIO_Context : public WSAOVERLAPPED, public CContext
{
public:
	CIO_Context(CIOUnit* pUnit, IO_Type type) : CContext(pUnit, type) {};
};


