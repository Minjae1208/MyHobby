#pragma once

class CIOManager;
class CNetPeer;

using CreateNetPeerFunc = std::function<std::shared_ptr<CNetPeer>()>;
using CreateIOManagerFunc = std::function<std::shared_ptr<CIOManager>()>;


// @brief IO Manager�� �������ִ� Ŭ����
class CNetWork
{
	friend class CIOManager;

protected:
	// IO ���� ������� ���� Ŭ����
	std::shared_ptr<CIOManager> io_manager;
	// Server to Server IO Manager
	//std::shared_ptr<CIOManager> io_manager;

public:
	CNetWork();
	~CNetWork();

public:
	// ��Ʈ��ũ ���� �� ����
	void Create();
	// ��Ʈ��ũ �����ϱ�
	virtual bool Start() = 0;
	// ��Ʈ��ũ ���߱�
	void Stop();
};

