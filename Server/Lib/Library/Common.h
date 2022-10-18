#pragma once

#pragma comment(lib,"ws2_32.lib")
#pragma comment(lib,"mswsock.lib")

#include "winsock2.h"
#include "mswsock.h"
#include "ws2tcpip.h"

#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <deque>

#include <thread>
#include <mutex>

//#include "NetWork/IOManager.h"
#include "NetWork/NetPeer.h"
#include "NetWork/IOModel.h"
//#include "NetWork/IOUnit.h"
#include "NetWork/Context.h"

#include "Tool/Singleton.h"
#include "Tool/Stream.h"
#include "Tool/Type.h"
#include "Tool/Lock.h"