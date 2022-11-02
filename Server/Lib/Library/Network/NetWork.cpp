#include "pch.h"

#include "NetWork.h"
#include "IOManager.h"

#include "Buffer/BufferManager.h"

CNetWork::CNetWork()
{
}

CNetWork::~CNetWork()
{

}

bool CNetWork::Start()
{
	// Set IO Manager - �ӽ� RIO | IOCP(Accept) | IOCP(AcceptEx)�� �����ֱ�
	if (1)		io_manager = std::make_shared<CRIOManager>(this);
	else if (2)	io_manager = std::make_shared<CIOCPManager>(this);
	else if (3)	io_manager = std::make_shared<CIOCPManager_Ex>(this);
	//else		// error

	//// ��Ʈ��ũ ����
	if (io_manager->Init_Manager() == false)
		return false;

	//// Set Accepter Thread
	//accepter = std::thread([this]() { this->io_manager->Accepter_Run(); });

	//// Set IO Worker
	//for (int i = 0; i < 1; i++)
	//{
	//	workers.emplace_back(std::thread([this, index = i]() { this->io_manager->IO_Run(index); }));
	//}

	// Buffer Manager Setting **** ���� Recv & Send ������ ũ��� ���� �����͸� �о ������ ����
	CBufferManager::Instance()->MakeBuffer(16384, 100);


	return true;
}

void CNetWork::Stop()
{
	io_manager->Accepter_Stop();
	io_manager->IO_Stop();
	io_manager->Process_Stop();

	// ��ü �޸� ����
}

