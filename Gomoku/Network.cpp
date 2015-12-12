#include "stdafx.h"
#include "Network.h"
#include <sstream>
#include "Field.h"


Network::Network()
{
}


void Network::CreateServer()
{
	gomokuServerPipe = CreateNamedPipe(L"\\\\.\\pipe\\asdfGomokuServerPipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, sizeof(int), sizeof(int), 2000, NULL);
	if (gomokuServerPipe == INVALID_HANDLE_VALUE)
		throw "Could not create a server";

	gomokuClientPipe = CreateNamedPipe(L"\\\\.\\pipe\\asdfGomokuClientPipe", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, sizeof(int), sizeof(int), 2000, NULL);
	if (gomokuClientPipe == INVALID_HANDLE_VALUE)
		throw "Could not create a server";

	ConnectNamedPipe(gomokuServerPipe, NULL);
	ConnectNamedPipe(gomokuClientPipe, NULL);
}

void Network::SendTurn(int cellIndex)
{
	DWORD bytesWritten;
	switch (currentPlayer)
	{
	case Field::Krestiki:
		WriteFile(gomokuServerPipe, &cellIndex, sizeof(cellIndex), &bytesWritten, NULL);
		break;
	case Field::Noliki:
		WriteFile(gomokuClientPipe, &cellIndex, sizeof(cellIndex), &bytesWritten, NULL);
		break;
	}
}
//receive - получить
int Network::ReceiveTurn()
{
	int cellIndex;
	DWORD bytesRead;
	switch (currentPlayer)
	{
	case Field::Krestiki:
		ReadFile(gomokuClientPipe, &cellIndex, sizeof(cellIndex), &bytesRead, NULL);
		break;
	case Field::Noliki:
		ReadFile(gomokuServerPipe, &cellIndex, sizeof(cellIndex), &bytesRead, NULL);
		break;
	default:
		return -1000;
		break;
	}
	return cellIndex;
}

void Network::ConnectToServer(char* ip)
{
	std::ostringstream server, client;
	server << "\\\\" << ip << "\\pipe\\asdfGomokuServerPipe";
	gomokuServerPipe = CreateFileA(server.str().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (gomokuServerPipe == INVALID_HANDLE_VALUE)
		throw "Could not connect to the server";
	client << "\\\\" << ip << "\\pipe\\asdfGomokuClientPipe";
	gomokuClientPipe = CreateFileA(client.str().c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (gomokuClientPipe == INVALID_HANDLE_VALUE)
		throw "Could not connect to the server";
}

Network::~Network()
{
	if (gomokuServerPipe != INVALID_HANDLE_VALUE)
		CloseHandle(gomokuServerPipe);
}
