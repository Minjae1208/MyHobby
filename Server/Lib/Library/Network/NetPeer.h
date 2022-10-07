#pragma once

// @brief **** ���� �߰��ϱ�
class CNetPeer
{
public:
	typedef std::shared_ptr<CNetPeer> Shared;
private:

public:
	CNetPeer();
	~CNetPeer();

	
};

// @brief **** ���� �߰��ϱ�
template <typename T>
std::shared_ptr<T> Create()
{
	std::shared_ptr<T> peer = std::make_shared<T>();
	return peer;
};