#pragma once

enum class EIOType : uint8 
{
	NONE	= 0,
	RIO		= 1,
	IOCP	= 2,
	IOCP_EX = 3,
	MAX
};

enum class EDBType : uint8
{
	NONE = 0,
	USER = 1,
	GAME = 2,
	MAX
};

enum class EServerType : uint8
{
	NONE	= 0,
	LOGIN	= 1,
	LOBBY	= 2,
	GAME	= 3,
	MAX
};

enum class EPacketTag : uint16
{
	NONE = 0,
	TEST = 1,

	MAX
};