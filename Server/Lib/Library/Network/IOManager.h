#pragma once

class CNetWork;
class CIOUnit;

// @brief IO Manager 기본 틀
class CIOManager
{
protected:
	// @brief 관리 class
	CNetWork* network = nullptr;
	// @brief Thread Controller
	bool accept_run = false;
	bool io_run = false;
	bool proc_run = false;

	SOCKET listen_socket;
	// @brief IO Handle
	HANDLE io_handle;
	// @brief Proc Handle
	HANDLE proc_handle;
	
	// @brief **** 설명 추가하기
	std::mutex unit_lock;

	// @brief **** 설명 추가하기
	std::thread accept_worker;
	// @brief **** 설명 추가하기
	std::vector<std::thread> io_workers;
	// @brief **** 설명 추가하기
	std::vector<CIOUnit*> io_units;

public:
	CIOManager(CNetWork* net);
	virtual ~CIOManager();

public:
	HANDLE GetHandle() { return io_handle; }

	// @brief
	virtual bool Init_Manager();
	// @brief RIO 및 IOCP-Accept 에서 사용 | IOCP-AcceptEx는 사용안함
	virtual void Accepter_Run();
	// @brief 
	virtual void IO_Run(int index) {};
	// @brief 
	void Process_Run();
	// @brief
	virtual void IO_Stop() {};
	// @brief Accept 처리 함수
	virtual void OnAccept(SOCKET socket) {};
	// @brief
	virtual CIOUnit* AllocUnit(SOCKET socket) { return nullptr; };

};


// @brief RIO Manager
class CRIOManager : public CIOManager
{
private:
	bool proc_run;

	GUID guid;
	std::vector<RIO_CQ> cqs;
	RIO_EXTENSION_FUNCTION_TABLE table;
	
	std::vector<std::thread> process_workers;

public:
	CRIOManager(CNetWork* net);
	virtual ~CRIOManager();

public:
	virtual bool Init_Manager();
	virtual void IO_Run(int index);
	// @brief Accept 처리 함수
	virtual void OnAccept(SOCKET socket);
	// @brief 
	virtual CIOUnit* AllocUnit(SOCKET socket);

	const RIO_EXTENSION_FUNCTION_TABLE& GetTable() { return table; };

private:
	// @biref 
	bool Init_RIO_Table();
	// @biref 
	bool Init_RIO_CQ();
};


// @brief IOCP-Accept Manager
class CIOCPManager : public CIOManager
{
private:

public:
	CIOCPManager(CNetWork* net);
	virtual ~CIOCPManager();

public:
	virtual bool Init_Manager();
	virtual void IO_Run(int index);
	// @brief Accept 처리 함수
	virtual void OnAccept(SOCKET socket);
	// @brief 
	virtual CIOUnit* AllocUnit(SOCKET socket);
};


// @brief IOCP-AcceptEx Manager
class CIOCPManager_Ex : public CIOManager
{
private:

public:
	CIOCPManager_Ex(CNetWork* net);
	virtual ~CIOCPManager_Ex();

public:
	virtual bool Init_Manager();
	// @brief AccpetEx만 Accepter Thread를 사용하지 않기 때문에 빈 함수로 세팅
	virtual void Accepter_Run() {};

	virtual void IO_Run(int index);

	virtual void OnAccept(SOCKET socket);

};