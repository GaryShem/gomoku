#include "stdafx.h"
#include "Player.h"

Player::Player(std::string playerName, int playerNumber)
{
	name = playerName;
	number = playerNumber;
	if (playerNumber != 1 && playerNumber != 2)
		throw "Invalid player number";
	if (playerNumber == 1)
	{
		symbol = 'X';
	}
	else
	{
		symbol = 'O';
	}

	//symbol = playerSymbol;
}

std::string Player::GetName()
{
	return name;
}

int Player::GetNumber()
{
	return number;
}

char Player::GetSymbol()
{
	return symbol;
}

Player::~Player()
{
}
