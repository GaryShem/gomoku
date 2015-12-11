#include "stdafx.h"
#include "Network.h"
#include <sstream>


Network::Network()
{
}


void Network::CreateServer()
{
	gomokuPipe = CreateNamedPipe(L"\\\\.\\pipe\\asdfGomokuPipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, sizeof(int), sizeof(int), 2000, NULL);
	if (gomokuPipe == INVALID_HANDLE_VALUE)
		throw "Could not create a server";
	ConnectNamedPipe(gomokuPipe, NULL);
}

void Network::SendTurn(int cellIndex)
{
	DWORD bytesWritten;
	WriteFile(gomokuPipe, &cellIndex, sizeof(cellIndex), &bytesWritten, NULL);
}

int Network::ReceiveTurn()
{
	int cellIndex;
	DWORD bytesRead;
	ReadFile(gomokuPipe, &cellIndex, sizeof(cellIndex), &bytesRead, NULL);
	return cellIndex;
}

void Network::ConnectToServer(char* ip)
{
	std::ostringstream ss;
	ss << "\\\\" << ip << "\\pipe\\asdfGomokuPipe";
	gomokuPipe = CreateFileA(ss.str().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (gomokuPipe == INVALID_HANDLE_VALUE)
		throw "Could not connect to the server";
}

Network::~Network()
{
	if (gomokuPipe != INVALID_HANDLE_VALUE)
		CloseHandle(gomokuPipe);
}
