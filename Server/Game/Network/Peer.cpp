
#include "pch.h"
#include "Peer.h"


CPeer::CPeer()
{

}

CPeer::~CPeer()
{
}

void CPeer::OnWorking(SStream::Shared stream)
{
	uint16 tag = stream->GetTag();


}

void CPeer::OnTest(SStream::Shared stream)
{
	C2S_Test test;
	memset(&test, 0, sizeof(C2S_Test));

	stream->ReadData((uint8*)&test);

	
	int bp = 0;
}
