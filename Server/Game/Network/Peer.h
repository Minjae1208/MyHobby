#pragma once

class CPeer : public CNetPeer
{
public:
	CPeer();
	~CPeer();

public:

	virtual void OnAccept(SStream::Shared stream) {};
	virtual void OnConnect(SStream::Shared stream) {};
	virtual void OnClose(SStream::Shared stream) {};
	virtual void OnWorking(SStream::Shared stream);
	virtual void OnTest(SStream::Shared stream);

};