
#include "ServerManager.h"

#include "../../Buffer/BufferManager.h"
#include "../../Buffer/ObjectManager.h"

#include "Peer/Peer.h"

#include "IOUnit/IOAccept.h"
#include "IOUnit/IORecv.h"
#include "IOUnit/IOSend.h"
#include "IOUnit/IOClose.h"

NAMESPACE_BEGINE(MinNet)

void CServerManager::Constructor()
{
	// Peer Init
	CObjectManager<CPeer>::InitObjectManager(1, 1);

	// IOUnit Init
	CObjectManager<CIOAccept>::InitObjectManager(1, 1);
	CObjectManager<CIORecv>::InitObjectManager(1, 1);
	CObjectManager<CIOSend>::InitObjectManager(1, 1);
	CObjectManager<CIOClose>::InitObjectManager(1, 1);

	// IOBuffer Object Init
	CObjectManager<CIOAcceptBuffer>::InitObjectManager(1, 1);
	CObjectManager<CIORecvBuffer>::InitObjectManager(1, 1);
	CObjectManager<CIOSendBuffer>::InitObjectManager(1, 1);
	CObjectManager<CIOCloseBuffer>::InitObjectManager(1, 1);

	// IOBuffer Buffer Init
	CBufferManager<CIOAcceptBuffer>::InitBufferManager(64, 1, 1);
	CBufferManager<CIORecvBuffer>::InitBufferManager(512, 1, 1);
	CBufferManager<CIOSendBuffer>::InitBufferManager(512, 1, 1);
}

void CServerManager::Destructor()
{
	// Peer Clear
	CObjectManager<CPeer>::ClearObjectManager();

	// IOUnit Clear
	CObjectManager<CIOAccept>::ClearObjectManager();
	CObjectManager<CIORecv>::ClearObjectManager();
	CObjectManager<CIOSend>::ClearObjectManager();
	CObjectManager<CIOClose>::ClearObjectManager();

	// IOBuffer Object Clear
	CObjectManager<CIOAcceptBuffer>::ClearObjectManager();
	CObjectManager<CIORecvBuffer>::ClearObjectManager();
	CObjectManager<CIOSendBuffer>::ClearObjectManager();
	CObjectManager<CIOCloseBuffer>::ClearObjectManager();

	// IOBuffer Buffer Clear
	CBufferManager<CIOAcceptBuffer>::ClearBufferManager();
	CBufferManager<CIORecvBuffer>::ClearBufferManager();
	CBufferManager<CIOSendBuffer>::ClearBufferManager();
}

NAMESPACE_END