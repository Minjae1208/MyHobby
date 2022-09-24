#pragma once

class CAccepter;

// @brief ���� ���� ��Ʈ��ũ Ŭ����
class CNetWork : public CSingleton<CNetWork>
{
private:
	SOCKET listen_socket;
	HANDLE network_handle;

	friend class CAccepter;
	std::shared_ptr<CAccepter> accepter;

public:
	CNetWork();
	~CNetWork();

public:
	bool Start();
	void Stop();

private:
	bool Init_NetWork();

};