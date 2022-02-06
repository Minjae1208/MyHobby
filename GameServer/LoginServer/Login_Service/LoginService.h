#pragma once

#include "Service/Service.h"

class CLoginService : public MinNet::CService
{
private:
	CLoginService();
	virtual ~CLoginService();

protected:
	virtual void Constructor();
	virtual void Distrucotr();
};