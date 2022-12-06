#pragma once

class CGameNet : public CSingleton<CGameNet>, public CNetWork
{
public:
	CGameNet();
	~CGameNet();



public:
	virtual bool Start();
};