#pragma once
#include "Field.h"

class Network
{
public:
	Network();
	~Network();
	void CreateServer();
	void ConnectToServer(char* ip);
	void SendTurn(int cellIndex);
	int ReceiveTurn();
	HANDLE gomokuServerPipe = INVALID_HANDLE_VALUE;
	HANDLE gomokuClientPipe = INVALID_HANDLE_VALUE;
	Field::Player currentPlayer;
};

