#include "pch.h"


int main()
{
	WSADATA wsa;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsa))
		return 0;

	SOCKET listen_socket = WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, NULL, 0, WSA_FLAG_OVERLAPPED);

	const int rcvlen = 0, sndlen = 0;
	::setsockopt(listen_socket, SOL_SOCKET, SO_RCVBUF, (const char*)&rcvlen, sizeof(rcvlen));
	::setsockopt(listen_socket, SOL_SOCKET, SO_SNDBUF, (const char*)&sndlen, sizeof(sndlen));

	sockaddr_in addr;
	inet_pton(AF_INET, "127.0.0.1", &addr.sin_addr);
	addr.sin_port = htons(8990);
	addr.sin_family = AF_INET;
	

	if (SOCKET_ERROR == ::connect(listen_socket, (sockaddr*)&addr, sizeof(sockaddr_in)))
	{
		int LastError = WSAGetLastError();
		if (WSAEWOULDBLOCK != LastError)
		{
			return 0;
		}
	}

	C2S_Test test;
	test.v1 = 10;
	test.v2 = 20;
	test.v3 = 30;
	test.v4 = 40;

	SStream::Shared stream = std::make_shared<SStream>();
	stream->SetTag((uint16)EPacketTag::TEST);
	stream->WriteData((uint8*)&test, sizeof(C2S_Test));

	bool res = send(listen_socket, (const char*)stream->GetData(), stream->GetSize(), 0);
	if (res == SOCKET_ERROR)
	{
		int i = 0;
	}


	while (true) 
	{
		
	}

	WSACleanup();

	return 0;
}