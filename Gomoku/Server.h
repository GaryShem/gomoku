#pragma once

class Server
{
public:
	static const int fieldSize = 15;
	Server();
	~Server();
	void Init();
	void Close();
	void SendTurn(int turnIndex);
	int ReceiveTurn();
private:
	char fieldState[fieldSize*fieldSize];
	HANDLE p1 = INVALID_HANDLE_VALUE;
	HANDLE p2 = INVALID_HANDLE_VALUE;
};

