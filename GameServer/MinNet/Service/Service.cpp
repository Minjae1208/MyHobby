#include "Service.h"

#include <tchar.h>

MINNET_BEGINE

CService* CService::instance = nullptr;

CService::CService()
{
	mEvent = CreateEvent(NULL, FALSE, FALSE, NULL);
}

CService::~CService()
{
	CloseHandle(mEvent);
}

CService * CService::Get()
{
	if (nullptr == instance)
		instance = new CService();

	return instance;
}

void CService::Purge()
{
	if (nullptr != instance)
	{
		delete instance;
		instance = nullptr;
	}
}

/**
	@brief Service Initialize Function
	@param InCmd 서비스 조작 명령
	@param InSriName 서비스 이름
*/
bool CService::InitService(std::wstring InCmd, LPTSTR InSriName)
{
	if (L"Install" == InCmd)
		return _Install(InSriName);
	else if (L"Uninstall" == InCmd)
		return  _UnInstall(InSriName);
	else
		return  _Start(InSriName);
}

/**
	@brief Service Install Function (서비스 생성)
	@param InSriName 서비스 이름
*/
bool CService::_Install(LPCTSTR InSriName)
{
	SC_HANDLE scm = NULL;
	SC_HANDLE sri = NULL;

	TCHAR SriFilePath[MAX_PATH] = { 0, };

	SriFilePath[0] = '"';
	GetModuleFileName(NULL, SriFilePath + 1, MAX_PATH - 1);
	_tcscat_s(SriFilePath, _T("\""));

	scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (NULL == scm)
	{
		int err = GetLastError();

		return false;
	}

	sri = CreateService(
		scm,
		InSriName,      // Service Name
		InSriName,		// Service Summary
		SERVICE_ALL_ACCESS,
		SERVICE_WIN32_OWN_PROCESS | SERVICE_INTERACTIVE_PROCESS,
		SERVICE_DEMAND_START,
		SERVICE_ERROR_NORMAL,
		SriFilePath,			// Path
		NULL, NULL, NULL, NULL, NULL
	);

	if (NULL == sri)
	{
		CloseServiceHandle(scm);
		int err = GetLastError();

		return false;
	}

	CloseServiceHandle(scm);
	CloseServiceHandle(sri);

	return true;
}

/**
	@brief Service UnInstall Function (서비스 삭제)
	@param InSriName 서비스 이름
*/
bool CService::_UnInstall(LPCTSTR InSriName)
{
	SC_HANDLE scm = nullptr;
	SC_HANDLE sri = nullptr;

	scm = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);
	if (NULL == scm)
	{
		int err = GetLastError();

		return false;
	}

	sri = OpenService(scm, InSriName, SERVICE_ALL_ACCESS);
	if (NULL == sri)
	{
		CloseServiceHandle(scm);
		int err = GetLastError();

		return false;
	}

	SERVICE_STATUS ss;
	QueryServiceStatus(sri, &ss);
	if (SERVICE_STOPPED != ss.dwCurrentState) 
	{
		ControlService(sri, SERVICE_CONTROL_STOP, &ss);
		Sleep(2000);
	}

	if (false == DeleteService(sri))
	{
		int err = GetLastError();

		CloseServiceHandle(scm);
		CloseServiceHandle(sri);

		return false;
	}

	CloseServiceHandle(scm);
	CloseServiceHandle(sri);

	return true;
}

/**
	@brief Service Start Function (서비스 실행)
	@param InSriName 서비스 이름
*/
bool CService::_Start(LPTSTR InSriName)
{
	mSriName = InSriName;

	SERVICE_TABLE_ENTRY table[] =
	{
		{mSriName, _SriStaticMain} ,
		{NULL, NULL}
	};

	if (false == StartServiceCtrlDispatcher(table))
	{
		int err = GetLastError();

		return false;
	}

	return true;
}

/**
	@brief 
	@param 
*/
bool CService::_SetServiceState(DWORD InState)
{
	mSriState.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
	mSriState.dwCurrentState = InState;
	mSriState.dwControlsAccepted = SERVICE_ACCEPT_PAUSE_CONTINUE | SERVICE_ACCEPT_STOP;
	mSriState.dwWin32ExitCode = 0;
	mSriState.dwServiceSpecificExitCode = 0;
	mSriState.dwCheckPoint = 0;
	mSriState.dwWaitHint = 0;

	mNowSriState = InState;
	if (false == SetServiceStatus(mSriHandle, &mSriState))
		return false;

	return true;
}

/**
	@brief 
	@param 
*/
void CService::_SriHandle(DWORD InState)
{
	switch (InState)
	{
	case SERVICE_CONTROL_STOP:
		_SetServiceState(SERVICE_STOP_PENDING);
		SetEvent(mEvent);
		break;
	case SERVICE_CONTROL_PAUSE:
		_SetServiceState(SERVICE_PAUSE_PENDING);
		_SetServiceState(SERVICE_PAUSED);
		break;
	case SERVICE_CONTROL_CONTINUE:
		_SetServiceState(SERVICE_CONTINUE_PENDING);
		_SetServiceState(SERVICE_RUNNING);
		break;
	case SERVICE_CONTROL_INTERROGATE:
		break;
	default:
		_SetServiceState(mNowSriState);
	}
}

/**
	@brief Service Main Function
*/
void CService::_SriMain(DWORD argc, LPTSTR * argv)
{
	mSriHandle = RegisterServiceCtrlHandler(mSriName, _SriStaticHandle);
	if (mSriHandle == 0)
	{
		int err = GetLastError();

		return;
	}

	_SetServiceState(SERVICE_START_PENDING);
	_SetServiceState(SERVICE_RUNNING);

	//Constructor();

	_Run();

	//Distrucotr();

	_SetServiceState(SERVICE_STOPPED);
}

void CService::_Run()
{
	while (1)
	{
		
		if (WaitForSingleObject(mEvent, 10000) == WAIT_OBJECT_0)
			break;
	}
}

/**
	@brief 
*/
void WINAPI CService::_SriStaticMain(DWORD argc, LPTSTR * argv)
{
	CService::Get()->_SriMain(argc, argv);
}

/**
	@brief 
	@param 
*/
void WINAPI CService::_SriStaticHandle(DWORD InSignal)
{
	CService::Get()->_SriHandle(InSignal);
}

MINNET_END