
#include "pch.h"
#include "IOModel.h"
#include "IOManager.h"
#include "IOUnit.h"
#include "Context.h"

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
	// **** 버퍼 세팅하자
	//recv_buffid = manager->GetTable().RIORegisterBuffer();
	if (recv_buffid == RIO_INVALID_BUFFERID)
	{
		// error
		return false;
	}
	//send_buffid = manager->GetTable().RIORegisterBuffer();
	if (send_buffid == RIO_INVALID_BUFFERID)
	{
		// error
		return false;
	}

	// RQ 생성
	rq = manager->GetTable().RIOCreateRequestQueue(unit->GetSocket(), 1, 1, 1, 1, (RIO_CQ)manager->GetHandle(), (RIO_CQ)manager->GetHandle(), nullptr);

	if (rq == RIO_INVALID_RQ)
	{
		// error
		return false;
	}

	


	return true;
}

bool CRIOModel::Recv()
{
	// Connect 체크

	recv_context->BufferId = recv_buffid;
	//recv_context->Length = ;
	//recv_context->Offset = ;

	DWORD flags = 0;


	if (false == manager->GetTable().RIOReceive(rq, (PRIO_BUF)recv_context, 1, flags, recv_context))
	{
		// error
		return false;
	}

	return true;
}

bool CRIOModel::Send()
{
	// Connect 체크

	send_context->BufferId = send_buffid;
	//send_context->Length = ;
	//send_context->Offset = ;

	DWORD flags = 0;


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
