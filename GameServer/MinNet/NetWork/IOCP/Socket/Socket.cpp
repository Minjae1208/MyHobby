
#include "Socket.h"

MINNET_BEGINE

CSocket::CSocket(int InIndex)
{
	mIndex = InIndex;

	OnCreateSocket();
}

CSocket::~CSocket()
{

}

void CSocket::OnCreateSocket()
{
	mSock = socket(AF_INET, SOL_SOCKET, IPPROTO_TCP);
	if (mSock == INVALID_SOCKET)
	{
		// error
	}

}

void CSocket::OnCloseSocket()
{
	closesocket(mSock);
}


MINNET_END