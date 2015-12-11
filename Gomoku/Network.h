#pragma once
class Network
{
public:
	Network();
	~Network();
	void CreateServer();
	void ConnectToServer(char* ip);
	void SendTurn(int cellIndex);
	int ReceiveTurn();
	HANDLE gomokuPipe = INVALID_HANDLE_VALUE;
};

