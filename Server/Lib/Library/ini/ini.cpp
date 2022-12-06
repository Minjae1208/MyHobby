
#include "pch.h"
#include "ini.h"
#include "Tool/StringUtil.h"

CIni::CIni()
{
	app = new CServer_ini();
}

CIni::~CIni()
{
	if (app != nullptr)
		delete app;
}

void CIni::Init()
{
	TCHAR szBuffer[512];
	GetModuleFileName(GetModuleHandle(0), (LPTSTR)szBuffer, MAX_PATH);

	std::wstring ws = szBuffer;
	size_t pos = ws.find_last_of(L'\\');
	ws = ws.substr(0, pos);

	ws += L"//info.ini";

	mINI::INIFile ini_file(SUtil::w2s(ws) + "//info.ini");
	mINI::INIStructure ini;
	ini_file.read(ini);

	// 서버 ID 세팅
	app->SetID(SUtil::s2v<int16>(ini["Server"]["ID"]));
	app->SetIO((uint8)SUtil::s2v<int16>(ini["Server"]["IO"]));
	app->SetMaxPeer(SUtil::s2v<int16>(ini["Server"]["Peer"]));
	app->SetMaxConn(SUtil::s2v<int16>(ini["Server"]["Conn"]));

	// 서버에서 사용할 DB 세팅
	int i = 10;
}
