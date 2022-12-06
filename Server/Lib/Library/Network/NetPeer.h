#pragma once

#include "Tool/Stream.h"

// @brief **** ���� �߰��ϱ�
class CNetPeer
{
public:
	typedef std::shared_ptr<CNetPeer> Shared;
private:

public:
	virtual void OnAccept(SStream::Shared stream) = 0;
	virtual void OnConnect(SStream::Shared stream) = 0;
	virtual void OnClose(SStream::Shared stream) = 0;
	virtual void OnWorking(SStream::Shared stream) = 0;
	
	virtual void OnTest(SStream::Shared stream) = 0;

};

// @brief **** ���� �߰��ϱ�
//template <typename T>
//std::shared_ptr<T> Create()
//{
//	std::shared_ptr<T> peer = std::make_shared<T>();
//	return peer;
//};