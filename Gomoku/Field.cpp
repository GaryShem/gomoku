#include "stdafx.h"
#include "Field.h"


Field::Field()
{
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			_field[i][j] = ' ';
	for (char c : _field)
		c = ' ';
	_field[size*size + 1] = 0;
}


Field::~Field()
{
}

std::string Field::toString()
{
	std::string result = "";
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			result += _field[i][j];
	for (char c : _field)
		result += c;
	return result;
}

bool Field::MakeTurn(int n, char symbol)
{
	if (_field[n] == ' ')
	{
		_field[n] = symbol;
		return true;
	}
	else return false;
}

bool Field::MakeTurn(int row, int column, char symbol)
{
	return MakeTurn(row*size + column, symbol);
}

//проверяет, находится ли выбранная клетка в пределах поля
bool Field::IsWithinBounds(int n)
{
	if (n < 0 || n >= size*size)
		return false;
	return true;
}

bool Field::IsWithinBounds(int row, int column)
{
	return IsWithinBounds(row*size + column);
}

/**
	Возвращаемые значения:
	-1	- игра окончилась ничьёй
	0	- игра не окончена
	1	- победил 1-й игрок
	2	- победил 2-й игрок
*/
int Field::WhoWon(int turnIndex)
{
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
	//проверяем каждое направление
	for (int k = 0; k < 4; k++)
	{
		int limit_i = directions[k][0] * 4;
		int limit_j = directions[k][1] * 4;
		int count = 0;

		//идём по нему от 4 с меньшей стороны до 4 в большую сторону
		int i = directions[k][0] * (-4);
		int j = directions[k][1] * (-4);
		while (i <= limit_i && j <= limit_j)
		{
			//если клетка за пределами
			//если эта клетка за пределами с "меньшей" стороны, то потом мы можем прийти на поле,
			//поэтому лучше просто пропустить итерацию цикла, а не выходить из него
			if (IsWithinBounds(i, j) == false)
				continue;
			else if (_field[i*size + j] == _field[turnIndex])
			{ //иначе, если мы встретили нужный символ, то увеличиваем счётчик серии
				count++;
			}
			
			else //if (_field[i*size + j] != _field[turnIndex])
			{	//иначе, если мы встретили не тот символ - пустой или чужой, то серия прервалась,
				//и обнуляем счётчик
				count = 0;
			}
			//двигаемся в нужном нам направлении
			i += directions[k][0];
			j += directions[k][1];
		}
		if (count >= 5)
		{
			if (_field[turnIndex] == playerOneSymbol)
				return 1; //победил игрок один - крестики
			if (_field[turnIndex] == playerTwoSymbol)
				return 2; //победил игрок два - нолики
		}
	}
	if (toString().find(' ') == std::string::npos)
		return -1; //все поля заполнены, победителя быть не может - игра закончилась ничьёй
	return 0; //игра не окончена
}

int Field::WhoWon(int turnRow, int turnColumn)
{
	return WhoWon(turnRow*size + turnColumn);
}