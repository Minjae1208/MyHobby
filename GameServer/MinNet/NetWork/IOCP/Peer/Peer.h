#pragma once

#include "../../../MinNetCommon.h"
#include "../../../Buffer/ObjectManager.h"
#include "SafeRefCount.h"

NAMESPACE_BEGINE(MinNet)

class CIOUnit;

class CPeer : public CObjectManager<CPeer>, public CSafeRefCount
{
public:
	CPeer();
	virtual ~CPeer();

	CIOUnit* GetIOUnit();
	void SetIOUnit(CIOUnit* InIO);

	//bool 

	void Connect();
	void DisConnect();

	void InCrease();
	void DeCrease();

private:
	int mIndex;
	CIOUnit* ioUnit;

};


NAMESPACE_END