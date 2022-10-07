#pragma once

class CIOManager;

// @brief IO Manager�� �������ִ� Ŭ����
class CNetWork
{
	friend class CIOManager;

private:
	std::shared_ptr<CIOManager> io_manager;

	// IOUnit List

	// 

	// Accept�� Thread
	std::thread accepter;
	// IO�� Thread
	std::vector<std::thread> workers;

public:
	CNetWork();
	~CNetWork();

public:
	// ��Ʈ��ũ �����ϱ�
	bool Start();
	// ��Ʈ��ũ ���߱�
	void Stop();
};

