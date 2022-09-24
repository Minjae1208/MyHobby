#pragma once

class CAccepter;

// @brief 서버 메인 네트워크 클래스
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