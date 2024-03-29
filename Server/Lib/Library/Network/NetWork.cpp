#include "pch.h"

#include "NetWork.h"

#include "Buffer/BufferManager.h"

CNetWork::CNetWork()
{
}

CNetWork::~CNetWork()
{

}

void CNetWork::Create()
{
	CIni::Instance()->Init();

	// 서버에서 사용할 메모리 세팅

}

//bool CNetWork::Start(CreateIOManagerFunc func)
//{
//	// Set IO Manager - 임시 RIO | IOCP(Accept) | IOCP(AcceptEx)로 나눠주기
//	//io_manager = func();
//	//if (1)
//	//else if (2)	io_manager = std::make_shared<CIOCPManager>(this);
//	//else if (3)	io_manager = std::make_shared<CIOCPManager_Ex>(this);
//
//	//// 네트워크 세팅
//	//if (io_manager->Init_Manager([]() { return std::make_shared<>() }) == false)
//	//	return false;
//
//	//// Set Accepter Thread
//	//accepter = std::thread([this]() { this->io_manager->Accepter_Run(); });
//
//	//// Set IO Worker
//	//for (int i = 0; i < 1; i++)
//	//{
//	//	workers.emplace_back(std::thread([this, index = i]() { this->io_manager->IO_Run(index); }));
//	//}
//
//	// Buffer Manager Setting **** 추후 Recv & Send 데이터 크기는 따로 데이터를 읽어서 세팅할 예정
//	//CBufferManager::Instance()->MakeBuffer(16384, 100);
//
//
//	return true;
//}

void CNetWork::Stop()
{
	io_manager->Accepter_Stop();
	io_manager->IO_Stop();
	io_manager->Process_Stop();

	// 전체 메모리 정리
}

