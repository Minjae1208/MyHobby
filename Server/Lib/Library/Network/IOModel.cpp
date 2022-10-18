
#include "pch.h"
#include "IOModel.h"
#include "IOManager.h"
#include "IOUnit.h"
#include "Context.h"

CIOModel::CIOModel(CIOUnit* pUnit)
{
	unit = pUnit;
	proc = new CIO_Context(unit, IO_Type::IO_PROC);
}

bool CIOModel::Proc()
{
	// Proc 넘기기 전에 Buffer에서 읽을 수 있는게 있는지 확인하기
	int32 len = 0;
	if (false == unit->CheckBuffer(len))
		return false;

	if (0 == PostQueuedCompletionStatus(unit->io_manager->GetProcHandle(), 0, (ULONG_PTR)unit, (OVERLAPPED*)proc))
	{
		int32 err = GetLastError();
		return false;
	}

	return true;
}

// ===========================================================================================
//										RIO Model
// ===========================================================================================
CRIOModel::CRIOModel(CIOUnit* pUnit, CRIOManager* pManager) : CIOModel(pUnit)
{
	manager = pManager;

	// **** 나중에 object Pool로 수정하자
	recv_context = new CRIO_Context(pUnit, IO_Type::IO_RECV);
	send_context = new CRIO_Context(pUnit, IO_Type::IO_SEND);
}

CRIOModel::~CRIOModel()
{

}

bool CRIOModel::Create()
{
	// Recv Buffer 연결
	recv_buffid = manager->GetTable().RIORegisterBuffer(unit->recv_buffer, unit->recv_buffer_size);
	if (recv_buffid == RIO_INVALID_BUFFERID)
	{
		// error
		return false;
	}

	// Send Buffer 연결
	send_buffid = manager->GetTable().RIORegisterBuffer(unit->send_buffer, unit->send_buffer_size);
	if (send_buffid == RIO_INVALID_BUFFERID)
	{
		// error
		return false;
	}

	// RQ 생성
	rq = manager->GetTable().RIOCreateRequestQueue(unit->GetSocket(), 1, 1, 1, 1, (RIO_CQ)manager->GetIOHandle(), (RIO_CQ)manager->GetIOHandle(), nullptr);

	if (rq == RIO_INVALID_RQ)
	{
		// error
		return false;
	}

	return true;
}

bool CRIOModel::Recv()
{
	recv_context->BufferId = recv_buffid;
	recv_context->Length = unit->recv_buffer_size;
	recv_context->Offset = 0;

	DWORD flags = 0;

	// Recv Setting
	if (false == manager->GetTable().RIOReceive(rq, (PRIO_BUF)recv_context, 1, flags, recv_context))
	{
		// error
		return false;
	}

	return true;
}

bool CRIOModel::Send()
{
	send_context->BufferId = send_buffid;
	send_context->Length = unit->send_buffer_size;
	send_context->Offset = 0;

	DWORD flags = 0;

	// Send Setting
	if (false == manager->GetTable().RIOSend(rq, (PRIO_BUF)send_context, 1, flags, send_context))
	{
		// error
		return false;
	}

	return true;
}


// ===========================================================================================
//									IOCP Model - Accept
// ===========================================================================================
CIOCPModel::CIOCPModel(CIOUnit* pUnit) : CIOModel(pUnit)
{

}

CIOCPModel::~CIOCPModel()
{

}

bool CIOCPModel::Create()
{


	return false;
}

bool CIOCPModel::Recv()
{
	return false;
}

bool CIOCPModel::Send()
{
	return false;
}


// ===========================================================================================
//									IOCP Model - AcceptEx
// ===========================================================================================
CIOCPModel_Ex::CIOCPModel_Ex(CIOUnit* pUnit) : CIOModel(pUnit)
{

}

CIOCPModel_Ex::~CIOCPModel_Ex()
{

}

bool CIOCPModel_Ex::Recv()
{
	return false;
}

bool CIOCPModel_Ex::Send()
{
	return false;
}
