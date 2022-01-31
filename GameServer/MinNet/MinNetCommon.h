#pragma once

#include "Winsock2.h"
#include "mswsock.h"
#include "Windows.h"
#include "ws2tcpip.h"

#include <thread>
#include <queue>
#include <vector>
#include <list>

#define MINNET_BEGINE namespace MinNet{
#define MINNET_END }


MINNET_BEGINE

enum class BUF_DEALLOC_TYPE
{
	NON_CHECK,
	CHECK,
};

enum class IO_TYPE
{
	ACEEPT,
	RECV,
	SEND,
	CLOSE,
};

enum class IO_BUF_TYPE
{
	ACEEPT,
	RECV,
	SEND,
	CLOSE,
};

MINNET_END