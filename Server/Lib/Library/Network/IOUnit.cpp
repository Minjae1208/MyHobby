
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

	// �б� �� �� �ɱ�
	CLock lock(read_lock);
	
	// �б�

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
	// ������ �б�
	ReadPacket(size);


	// IO ó�� �� �� �ɱ�
	CLock lock(io_lock);


	model->Recv();


}

void CIOUnit_RIO::IOSendWork(const ULONG size)
{
}


