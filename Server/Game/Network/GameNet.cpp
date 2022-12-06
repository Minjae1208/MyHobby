
#include "pch.h"
#include "GameNet.h"
#include "Peer.h"

CGameNet::CGameNet()
{
}

CGameNet::~CGameNet()
{
}

bool CGameNet::Start()
{
	Create();

	switch ((EIOType)CIni::Instance()->GetApp()->GetIO())
	{
	case EIOType::RIO:		io_manager = std::make_shared<CRIOManager>(this); break;
	case EIOType::IOCP:		io_manager = std::make_shared<CIOCPManager>(this); break;
	case EIOType::IOCP_EX:	io_manager = std::make_shared<CIOCPManager_Ex>(this); break;
	default: return false;
	}

	// Peer 持失
	if (io_manager->Init_Manager([]() { return std::make_shared<CPeer>(); }, CIni::Instance()->GetApp()->GetMaxPeer()) == false)
		return false;

	// Conn 持失


	return true;
}
