#pragma once

#include "IOManager.h"

#include "../../../Buffer/BufferManager.h"
#include "../../../Buffer/ObjectManager.h"

#include "IOAccept.h"
#include "IORecv.h"
#include "IOSend.h"
#include "IOClose.h"

MINNET_BEGINE


/**
	@brief 시작 전 반드시 Constructor를 호출
*/
void CIOManager::Constructor()
{
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

/**
	@brief 종료 전 반드시 Destructor를 호출
*/
void CIOManager::Destructor()
{
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

MINNET_END