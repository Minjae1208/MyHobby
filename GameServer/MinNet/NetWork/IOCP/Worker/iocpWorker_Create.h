
#include "../../../MinNetCommon.h"

MINNET_BEGINE

class CiocpWorker_Create
{
public:
	CiocpWorker_Create();
	virtual ~CiocpWorker_Create();

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