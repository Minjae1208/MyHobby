#pragma once

class CIOManager;

// @brief 서버 메인 네트워크 클래스
class CNetWork : public CSingleton<CNetWork>
{
private:
	SOCKET listen_socket;
	std::unique_ptr<CIOManager> io_manager;

	// Accept용 Thread
	std::thread accepter;

	// IO용 Thread
	std::vector<std::thread> workers;

public:
	CNetWork();
	~CNetWork();

public:
	bool Start();
	void Stop();

	// @brief RIO 및 IOCP-Accept 에서 사용 | IOCP-AcceptEx는 사용안함
	void AccepterRun();

private:
	bool Init_NetWork();
};

