#pragma once

#include <minwindef.h>

class CIOManager;
class CIOModel;
class CRingBuffer;

class CIOUnit
{
private:
	friend class CIOModel;
	friend class CRIOModel;

protected:
	CIOManager* io_manager = nullptr;

	const uint32 id;
	SOCKET socket = INVALID_SOCKET;

	// @brief
	std::shared_ptr<CNetPeer> peer;
	// @brief
	std::unique_ptr<CIOModel> model;

	// @brief Recv 처리시에 사용될 Buffer
	char* recv_buffer;
	int recv_buffer_size;

	// @brief Send 처리시에 사용될 Buffer
	char* send_buffer;
	int send_buffer_size;

	// @brief 
	CRingBuffer* proc_buffer;

	// @brief IO 처리에 대한 lock
	std::mutex io_lock;
	// @brief 실제 데이터 처리에 대한 lock
	std::mutex proc_lock;
	// @brief Packet Read 처리에 대한 lock
	std::mutex read_lock;
	// @brief Send시 걸어둘 lock
	std::mutex send_lock;
	// @brief 
	std::mutex work_lock;

public:
	CIOUnit(CIOManager* manager, uint32 num);
	virtual ~CIOUnit();

public:
	const int GetID() { return id; };
	const SOCKET& GetSocket() { return socket; };
	void Init_Unit(SOCKET socket);

	// @brief IO Recv 처리
	virtual void IORecvWork(const int32 len) {};
	// @brief IO Send 처리
	virtual void IOSendWork(const int32 len) {};
	// @brief 데이터 처리
	void ProcWork();

	void SetRecv();

protected:
	bool CheckBuffer(int32& len);
	bool ReadRecv(const int32 len);
	bool ReadProc(char* pData, int32& len);
	void OnWork(char* pData, int32 len);
};


class CIOUnit_RIO : public CIOUnit
{
private:

public:
	CIOUnit_RIO(CIOManager* manager, uint32 num);
	virtual ~CIOUnit_RIO();

	virtual void IORecvWork(const int32 len);
	virtual void IOSendWork(const int32 len);
};

class CIOUnit_IOCP : public CIOUnit
{

public:
	CIOUnit_IOCP(CIOManager* manager, uint32 num);
	virtual ~CIOUnit_IOCP();

};

class CIOUnit_IOCPEx : public CIOUnit
{


public:
	CIOUnit_IOCPEx(CIOManager* manager, uint32 num);
	virtual ~CIOUnit_IOCPEx();
};