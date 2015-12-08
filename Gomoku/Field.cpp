#include "stdafx.h"
#include "Field.h"


Field::Field()
{
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			field[i][j] = ' ';
	for (char c : field)
		c = ' ';
}


Field::~Field()
{
}

std::string Field::toString()
{
	std::string result = "";
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			result += field[i][j];
	for (char c : field)
		result += c;
	return result;
}

bool Field::MakeTurn(int n, char symbol)
{
	if (field[n] == ' ')
		field[n] = symbol;
}

bool Field::MakeTurn(int row, int column, char symbol)
{
	if (field[row*size+column] == ' ')
		field[row*size+column] = symbol;
}