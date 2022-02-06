#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

#include "../../MinNetCommon.h"
#include "Worker/iocpWorker_std.h"

NAMESPACE_BEGINE(MinNet)

class CSocket;
class CIOUnit;

typedef CiocpWorker_std CiocpWorker;

class CiocpClient : public CiocpWorker
{
public:
	CiocpClient();
	virtual ~CiocpClient();

protected:
	bool InitNetWork(int InPort, int InWorkerCount);

	virtual void _WorkerFunc();
	
	virtual void OnConnect(CIOUnit* InIO);
	virtual void OnRecv(CIOUnit* InIO, DWORD InLen);
	virtual void OnSend(CIOUnit* InIO, DWORD InLen);
	virtual void OnClose(CIOUnit* InIO);
	
	void StopNetWork();
private:
	bool _StartUp();
	bool _CreateSocket();
	bool _Bind(int InPort);
	bool _Handle();
	bool _WsaIoCtl(GUID InGuid);
	bool _ConnectEx();

	void _DeAllocIoUnit(CIOUnit* InIO);

private:
	HANDLE mIOCP;
	CSocket* mSock;
	SOCKADDR_IN mAddr;
	LPFN_CONNECTEX mConEx;
};

NAMESPACE_END