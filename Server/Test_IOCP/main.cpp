#include "pch.h"
#include "Starter/Starter.h"

int main()
{
	CStarter starter;

	starter.Start();

	while (true) {}

	WSACleanup();

	return 0;
}