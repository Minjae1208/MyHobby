#pragma once

// @brief IO Manager �⺻ Ʋ
class CIOManager
{
public:
	bool is_fail = false;

protected:
	HANDLE io_handle;

public:
	CIOManager();
	virtual ~CIOManager();
	HANDLE GetHandle() { return io_handle; }
	virtual void IO_Run(int index) {};
	virtual void IO_Stop() {};

	virtual void OnAccept(SOCKET socket) {};
};


// @brief RIO Manager
class CRIOManager : public CIOManager
{
private:
	GUID guid;
	RIO_EXTENSION_FUNCTION_TABLE table;

	std::vector<RIO_CQ> cqs;

public:
	CRIOManager();
	~CRIOManager();

public:
	virtual void IO_Run(int index);

	virtual void OnAccept(SOCKET socket);

private:
	// @biref
	void Init_RIO_Table();
	// @biref
	void Init_RIO_CQ();
};


// @brief IOCP-Accept Manager
class CIOCPManager : public CIOManager
{
private:

public:
	CIOCPManager();
	~CIOCPManager();

public:
	virtual void IO_Run(int index);

	virtual void OnAccept(SOCKET socket);
};


// @brief IOCP-AcceptEx Manager
class CIOCPManager_Ex : public CIOManager
{
private:

public:
	CIOCPManager_Ex();
	~CIOCPManager_Ex();

public:
	virtual void IO_Run(int index);

	virtual void OnAccept(SOCKET socket);

};