
#include "pch.h"
#include "IOUnit.h"
#include "IOModel.h"

#include "Buffer/RingBuffer.h"
#include "Buffer/BufferManager.h"

// ===========================================================================================
//										Unit Interface
// ===========================================================================================

CIOUnit::CIOUnit(CIOManager* manager, uint32 num) : id(num)
{
	io_manager = manager;
	
	
	char* recv_ = CBufferManager::Instance()->Get(16384);
	char* send_ = CBufferManager::Instance()->Get(16384);
	char* proc_ = CBufferManager::Instance()->Get(16384);
	//char* send_ = CBufferManager::Instance()->Get(16384);

	if (recv_ == nullptr || send_ == nullptr || proc_ == nullptr)
	{
		// error
		return;
	}

	recv_buffer = recv_;
	recv_buffer_size = 16384;
	send_buffer = send_;
	send_buffer_size = 16384;

	proc_buffer = new CRingBuffer(proc_, 16384);
	//send_buffer = new CRingBuffer(send_, 16384);
}

CIOUnit::~CIOUnit()
{
	// Buffer 되돌려주기
	CBufferManager::Instance()->Put(proc_buffer->GetBuffer(), 16384);
	CBufferManager::Instance()->Put(recv_buffer, recv_buffer_size);
	CBufferManager::Instance()->Put(send_buffer, send_buffer_size);
}

void CIOUnit::Init_Unit(SOCKET socket)
{
	model->Create();


}

void CIOUnit::ProcWork()
{
	char proc[16304];
	int32 len = 0;

	while (false != ReadProc(proc, len))
	{
		OnWork(proc, len);
	}

	model->Proc();
}

void CIOUnit::SetRecv()
{
	// Recv Setting
	if (false == model->Recv())
	{
		// error
	}
}

bool CIOUnit::CheckBuffer(int32& len)
{
	int32 use_len = proc_buffer->GetLength();

	if (0 >= len || len < 4)
		return false;

	int buffer_len = 0;
	proc_buffer->ReadData((char*)&buffer_len, 4);

	if (buffer_len <= 0 || buffer_len > 16384)
		return false;

	len = buffer_len;

	return true;
}

bool CIOUnit::ReadRecv(const int32 len)
{
	if (len <= 0)
		return false;

	// 읽기 전 락 걸기
	std::lock_guard<std::mutex> lock_guard(read_lock);
	
	if (false == proc_buffer->WriteData(recv_buffer, len))
	{
		// error
		return false;
	}

	return true;
}

bool CIOUnit::ReadProc(char* pData, int32& len)
{
	// 읽기 전 락 걸기
	std::lock_guard<std::mutex> lock_guard(read_lock);

	// 더 읽을 수 있는게 있는지 확인하기
	if (false == CheckBuffer(len))
		return false;

	return proc_buffer->ReadData(pData, len);
}

void CIOUnit::OnWork(char* pData, int32 len)
{

}

// ===========================================================================================
//										RIO Unit
// ===========================================================================================

CIOUnit_RIO::CIOUnit_RIO(CIOManager* manager, uint32 num) : CIOUnit(manager, num)
{
	model = std::make_unique<CRIOModel>(this, (CRIOManager*)io_manager);


}

CIOUnit_RIO::~CIOUnit_RIO()
{
}

void CIOUnit_RIO::IORecvWork(const int32 len)
{
	// 데이터 읽기
	if (false == ReadRecv(len))
	{
		// error
		return;
	}

	// IO 처리 전 락 걸기
	std::lock_guard<std::mutex> lock_guard(io_lock);

	// 데이터 유효성 검사

	// Proc Thread로 넘겨주기
	if (false == model->Proc())
	{
		// error
		return;
	}

	SetRecv();
}

void CIOUnit_RIO::IOSendWork(const int32 len)
{




}
