#pragma once
#include <string>

class Player
{
public:
	Player(std::string playerName, int playerNumber);
	~Player();
	std::string GetName();
	int GetNumber();
	char GetSymbol();
private:
	std::string name;
	int number;
	char symbol;
};

