#pragma once
#include <minwindef.h>

class CIOManager;
class CIOModel;

class CIOUnit
{
protected:
	CIOManager* io_manager = nullptr;

	SOCKET socket;

	// @brief
	std::shared_ptr<CNetPeer> peer;
	// @brief
	std::unique_ptr<CIOModel> model;

	

	// @brief IO ó���� ���� lock
	std::mutex io_lock;
	// @brief ���� ������ ó���� ���� lock
	std::mutex proc_lock;
	// @brief Packet Read ó���� ���� lock
	std::mutex read_lock;
	// @brief Send�� �ɾ�� lock
	std::mutex send_lock;
	// @brief Recv�� �ɾ�� lock
	std::mutex recv_lock;

public:
	CIOUnit(CIOManager* manager) { io_manager = manager; };
	~CIOUnit() {};

public:

	const SOCKET& GetSocket() { return socket; }
	void Init_Unit(SOCKET socket);

	// @brief IO Recv ó��
	virtual void IORecvWork(const ULONG size) {};
	// @brief IO Send ó��
	virtual void IOSendWork(const ULONG size) {};
	// @brief ������ ó��
	bool ProcWork() { return false; };


protected:
	bool ReadPacket(const ULONG size);

};


class CIOUnit_RIO : public CIOUnit
{
private:

public:
	CIOUnit_RIO(CIOManager* manager);
	~CIOUnit_RIO();

	virtual void IORecvWork(const ULONG size);
	virtual void IOSendWork(const ULONG size);

};

class CIOUnit_IOCP : public CIOUnit
{

public:
	CIOUnit_IOCP(CIOManager* manager);
	~CIOUnit_IOCP();

};

class CIOUnit_IOCPEx : public CIOUnit
{


public:
	CIOUnit_IOCPEx(CIOManager* manager);
	~CIOUnit_IOCPEx();
};