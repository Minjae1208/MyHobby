#pragma once


class CNetWork
{
public:
	CNetWork();
	~CNetWork();

public:
	bool Start();
	void Stop();

private:
	bool Init_NetWork();


private:
	SOCKET listen_socket;
	HANDLE network_handle;
};