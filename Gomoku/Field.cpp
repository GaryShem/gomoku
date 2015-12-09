#include "stdafx.h"
#include "Field.h"

const char Field::GameSymbols[3] = { ' ', 'X', 'O' };

Field::Field()
{
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			_field[i][j] = ' ';
	for (char c : _field)
		c = GameSymbols[0];
	_field[size*size + 1] = 0;
}

/**
Возвращаемые значения:
Ошибка: Эксепшн-строка с текстом ошибки
-1	- игра окончилась ничьей
0	- игра не окончена
1	- победил 1-й игрок
2	- победил 2-й игрок
*/
int Field::TakeTurn(int n, int player)
{
	int winner;
	if ((winner = WhoWon(_lastTurn)) != 0)
		return winner;
	return 0;
}

int Field::TakeTurn(int row, int column, int player)
{
	return TakeTurn(row*size + column, player);
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
int Field::WhoWon(int turnIndex = -1)
{
	//такое может быть только на первый ход
	//в этом случае мы знаем, что игра по-любому продолжается
	if (turnIndex < 0)
		return 0;
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
	if (_field[turnIndex])
	//проверяем каждое направление
	for (int k = 0; k < 4; k++)
	{
		int count = 0;

		//идём по нему от от меньшего к большему
		//всего 9 шагов - по 4 в меньшую и большую стороны (чтобы с текущей клеткой было 5 - это предельные значения)
		int row = directions[k][0] * (-4);
		int column = directions[k][1] * (-4);
		for (int step = 0; step < 9; step++)
		{
			//если эта клетка за пределами с "меньшей" стороны, то потом мы можем прийти на поле,
			//поэтому лучше просто пропустить итерацию цикла, а не выходить из него
			if (IsWithinBounds(row, column) == false)
				continue;
			else if (_field[row*size + column] == _field[turnIndex])
			{ //иначе, если мы встретили нужный символ, то увеличиваем счётчик серии
				count++;
			}
			
			else //if (_field[i*size + j] != _field[turnIndex])
			{	//иначе, если мы встретили не тот символ - пустой или чужой, то серия прервалась,
				//и обнуляем счётчик
				count = 0;
			}
			//двигаемся в нужном нам направлении
			row += directions[k][0];
			column += directions[k][1];
		}
		if (count >= 5)
		{
			if (_field[turnIndex] == 1)
				return 1; //победил игрок один - крестики
			if (_field[turnIndex] == 2)
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

bool Field::PlaceSymbol(int n, int player)
{
	if (_field[n] == ' ')
	{
		if (player == 1)
			_field[n] = 1;
		if (player == 2)
			_field[n] = 2;
		return true;
	}
	else return false;
}

bool Field::PlaceSymbol(int row, int column, int player)
{
	return PlaceSymbol(row*size + column, player);
}