
#include "Peer.h"
#include "../IOUnit/IOUnit.h"

NAMESPACE_BEGINE(MinNet)

CPeer::CPeer()
{

}

CPeer::~CPeer()
{

}

CIOUnit * CPeer::GetIOUnit()
{
	return nullptr;
}

void CPeer::SetIOUnit(CIOUnit * InIO)
{
	ioUnit = InIO;
	mIndex = InIO->GetSocket()->GetIndex();
	InCrease();
}

void CPeer::Connect()
{
	InCrease();
}

void CPeer::DisConnect()
{
	DeCrease();
}

void CPeer::InCrease()
{
	IncreaseRefCount();
}

void CPeer::DeCrease()
{
	if (0 == DecreaseRefCount())
	{
		delete this;
	}
}


NAMESPACE_END