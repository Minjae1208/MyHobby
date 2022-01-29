
#include "iocpWorker_std.h"


MINNET_BEGINE

CiocpWorker_std::CiocpWorker_std()
{

}

CiocpWorker_std::~CiocpWorker_std()
{

}

/**
	@brief thread »ý¼º
*/
void CiocpWorker_std::InitWorker(int InThreadCount)
{
	mState = true;

	for (int i = 0; i < InThreadCount; i++)
	{
		std::thread* thread = new std::thread();
		*thread =  std::thread(_WorkerRunFunc, this);
		mThreadVector.push_back(thread);
	}
}

void CiocpWorker_std::StopWorker()
{
	mState = false;
}

//void CiocpWorker_thread::_WorkerFunc()
//{
//	DWORD dwBytes = 0;
//	ULONGLONG* key = 0;
//	
//	bool result;
//
//	while (mState)
//	{
//		dwBytes = 0;
//		key = 0;
//
//		//result = GetQueuedCompletionStatus();
//	}
//}

void CiocpWorker_std::_WorkerRunFunc(LPVOID InThis)
{
	((CiocpWorker_std*)InThis)->_WorkerFunc();
}

MINNET_END

