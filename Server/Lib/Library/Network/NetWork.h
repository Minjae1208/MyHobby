#pragma once

class CIOManager;
class CNetPeer;

using CreateNetPeerFunc = std::function<std::shared_ptr<CNetPeer>()>;
using CreateIOManagerFunc = std::function<std::shared_ptr<CIOManager>()>;


// @brief IO Manager를 관리해주는 클래스
class CNetWork
{
	friend class CIOManager;

protected:
	// IO 동작 스레드들 관리 클래스
	std::shared_ptr<CIOManager> io_manager;
	// Server to Server IO Manager
	//std::shared_ptr<CIOManager> io_manager;

public:
	CNetWork();
	~CNetWork();

public:
	// 네트워크 시작 전 세팅
	void Create();
	// 네트워크 시작하기
	virtual bool Start() = 0;
	// 네트워크 멈추기
	void Stop();
};

