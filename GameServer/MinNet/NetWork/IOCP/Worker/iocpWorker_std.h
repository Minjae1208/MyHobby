#pragma once

#include "../../../MinNetCommon.h"

MINNET_BEGINE

/**
	@brief std::thread를 이용한 iocp Worker Thread CLass
*/
class CiocpWorker_std
{
public:
	CiocpWorker_std();
	virtual ~CiocpWorker_std();

protected:
	inline bool GetState() { return mState; }
	void InitWorker(int InThreadCount);
	void StopWorker();

private:
	virtual void _WorkerFunc() {}
	static void _WorkerRunFunc(LPVOID InThis);

private:
	bool mState;
	std::vector<std::thread*> mThreadVector;
};

MINNET_END