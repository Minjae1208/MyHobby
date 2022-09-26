#pragma once

class CIOManager;

// @brief ���� ���� ��Ʈ��ũ Ŭ����
class CNetWork : public CSingleton<CNetWork>
{
private:
	SOCKET listen_socket;
	std::unique_ptr<CIOManager> io_manager;

	// Accept�� Thread
	std::thread accepter;

	// IO�� Thread
	std::vector<std::thread> workers;

public:
	CNetWork();
	~CNetWork();

public:
	bool Start();
	void Stop();

	// @brief RIO �� IOCP-Accept ���� ��� | IOCP-AcceptEx�� ������
	void AccepterRun();

private:
	bool Init_NetWork();
};

