#pragma once

// @brief **** 설명 추가하기
class CNetPeer
{
public:
	typedef std::shared_ptr<CNetPeer> Shared;
private:

public:
	CNetPeer();
	~CNetPeer();

	
};

// @brief **** 설명 추가하기
template <typename T>
std::shared_ptr<T> Create()
{
	std::shared_ptr<T> peer = std::make_shared<T>();
	return peer;
};