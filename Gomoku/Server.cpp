#include "stdafx.h"
#include "Server.h"


Server::Server()
{
}


Server::~Server()
{
	Close();
}

void Server::Init()
{
	if (p1 == INVALID_HANDLE_VALUE)
		p1 = CreateNamedPipe(L"\\\\.\\pipe\\asdfGomokuP1", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, sizeof(int), sizeof(int), 2000, NULL);
	else
		DisconnectNamedPipe(p1);
	if (p2 == INVALID_HANDLE_VALUE)
		p2 = CreateNamedPipe(L"\\\\.\\pipe\\asdfGomokuP2", PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE, 1, sizeof(int), sizeof(int), 2000, NULL);
	else
		DisconnectNamedPipe(p2);

	if (p1 == INVALID_HANDLE_VALUE || p2 == INVALID_HANDLE_VALUE)
		throw EXCEPTION_INVALID_HANDLE;
}

void Server::SendTurn(int turnIndex)
{

}

int Server::ReceiveTurn()
{
	return 0;
}

void Server::Close()
{
	if (p1 != INVALID_HANDLE_VALUE)
		CloseHandle(p1);
	if (p2 != INVALID_HANDLE_VALUE)
		CloseHandle(p2);
}