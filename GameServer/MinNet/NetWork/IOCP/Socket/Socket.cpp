
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
	mSock = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);
	if (INVALID_SOCKET == mSock)
		return;

	mState = SOCKET_STATE::DISCONNECT;
}



bool CSocket::IsConnect()
{
	if (SOCKET_STATE::CONNECT == mState)
		return true;
	else
		return false;
}



void CSocket::OnConnectSocket()
{
	mState = SOCKET_STATE::CONNECT;
}



void CSocket::OnCloseSocket()
{
	mState = SOCKET_STATE::DISCONNECT;
	closesocket(mSock);
}


MINNET_END