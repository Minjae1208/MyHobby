#pragma once
#include "../MinNetCommon.h"

MINNET_BEGINE

class CService
{
private:
	CService();
	virtual ~CService();

	static CService* instance;

public:
	static CService* Get();
	static void Purge();

	bool InitService(std::wstring InCmd, LPTSTR InSriName);

protected:
	virtual void Constructor() {}
	virtual void Distrucotr() {}

private:
	bool _Install(LPCTSTR InSriName);
	bool _UnInstall(LPCTSTR InSriName);
	bool _Start(LPTSTR InSriName);

	bool _SetServiceState(DWORD InState);
	void _SriHandle(DWORD InState);
	void _SriMain(DWORD argc, LPTSTR* argv);
	void _Run();

	static void WINAPI _SriStaticMain(DWORD argc, LPTSTR* argv);
	static void WINAPI _SriStaticHandle(DWORD InSignal);

private: 
	// 
	LPTSTR mSriName;

	// 
	HANDLE mEvent;

	// 
	DWORD mNowSriState;

	// 
	SERVICE_STATUS_HANDLE mSriHandle;

	// 
	SERVICE_STATUS mSriState;
};

MINNET_END