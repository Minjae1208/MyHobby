#pragma once

class CIOManager;

// @brief IO Manager를 관리해주는 클래스
class CNetWork
{
	friend class CIOManager;

private:
	std::shared_ptr<CIOManager> io_manager;

	// IOUnit List

	// 

	// Accept용 Thread
	std::thread accepter;
	// IO용 Thread
	std::vector<std::thread> workers;

public:
	CNetWork();
	~CNetWork();

public:
	// 네트워크 시작하기
	bool Start();
	// 네트워크 멈추기
	void Stop();
};

