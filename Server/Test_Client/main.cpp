#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

#include "winsock2.h"
#include "mswsock.h"
#include "ws2tcpip.h"


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

	while (true) {}

	WSACleanup();

	return 0;
}