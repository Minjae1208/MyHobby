#pragma once

#include "Tool/Stream.h"

// @brief **** 설명 추가하기
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

// @brief **** 설명 추가하기
//template <typename T>
//std::shared_ptr<T> Create()
//{
//	std::shared_ptr<T> peer = std::make_shared<T>();
//	return peer;
//};