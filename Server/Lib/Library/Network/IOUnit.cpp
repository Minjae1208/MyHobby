
#include "pch.h"
#include "IOUnit.h"
#include "IOModel.h"

void CIOUnit::Init_Unit(SOCKET socket)
{
	model->Create();

}

bool CIOUnit::ReadPacket(const ULONG size)
{
	if (size <= 0)
		return false;

	// 읽기 전 락 걸기
	CLock lock(read_lock);
	
	// 읽기

	return true;
}

CIOUnit_RIO::CIOUnit_RIO(CIOManager* manager) : CIOUnit(manager)
{
	model = std::make_unique<CRIOModel>(this, (CRIOManager*)io_manager);
}

CIOUnit_RIO::~CIOUnit_RIO()
{
}

void CIOUnit_RIO::IORecvWork(const ULONG size)
{
	// 데이터 읽기
	ReadPacket(size);


	// IO 처리 전 락 걸기
	CLock lock(io_lock);


	model->Recv();


}

void CIOUnit_RIO::IOSendWork(const ULONG size)
{
}


