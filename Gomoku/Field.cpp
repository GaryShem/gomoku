#include "stdafx.h"
#include "Field.h"

char* Field::GameSymbols[3] = { " ", "X", "O" };

Field::Field()
{
//	for (int i = 0; i < size; i++)
//		for (int j = 0; j < size; j++)
//			_field[i][j] = ' ';
	for (char c : _field)
		c = 0;
}

int Field::GetGamestate()
{
	return _gameState;
}

/**
Возвращаемые значения:
Ошибка: Эксепшн-строка с текстом ошибки
-1	- игра окончилась ничьей
0	- игра не окончена
1	- победил 1-й игрок
2	- победил 2-й игрок
*/
int Field::TakeTurn(int n, int& player)
{
	if (_gameState != 0)
		throw "Game is over, no turns can be taken";
	int winner;
	if ((winner = WhoWon(_lastTurn)) != 0)
	{
		_gameState = winner;
		return winner;
	}

	//если пытаются пойти за пределы поля
	if (IsWithinBounds(n) == false)
		throw "your desired turn is outside the field";

	//если пытаются пойти в уже занятую клеточку
	if (PlaceSymbol(n) == false)
		throw "this cell is occupied";

	player = _activePlayerNumber;

	_activePlayerNumber = (_activePlayerNumber % 2) + 1;

	_lastTurn = n;
	_gameState = WhoWon(n);
	return _gameState;
}

int Field::TakeTurn(int row, int column, int& player)
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
	{
		result += GameSymbols[c];
	}
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
	Определяет победителя.
	Возвращаемые значения:
	-1	- игра окончилась ничьёй
	0	- игра не окончена
	1	- победил 1-й игрок
	2	- победил 2-й игрок
*/
int Field::WhoWon(int turnIndex)
{
	//такое может быть только в самом начале игры, перед первым ходом
	//в этом случае мы знаем, что игра по-любому продолжается
	if (turnIndex < 0)
		return 0;
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
		int count = 0;
	//проверяем каждое направление
	for (int k = 0; k < 4 && count < 5; k++)
	{
		count = 0;
		//идём по нему от от меньшего к большему
		//всего 9 шагов - по 4 в меньшую и большую стороны (чтобы с текущей клеткой было 5 - это предельные значения)
		int row = (turnIndex/size) + directions[k][0] * (-4);
		int column = (turnIndex%size) + directions[k][1] * (-4);
		for (int step = 0, limit = streak*2-1; step < limit && count < 5; step++)
		{
			//если эта клетка за пределами поля, то она не может быть частью серии
			//поэтому лучше просто пропустить итерацию цикла, а не выходить из него
			if (IsWithinBounds(row, column) == false)
			{
				//двигаемся в нужном нам направлении
				//row += directions[k][0];
				//column += directions[k][1];
				//continue;
			}
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
	if (toString().find(GameSymbols[0]) == std::string::npos)
		return -1; //все поля заполнены, победителя быть не может - игра закончилась ничьёй
	return 0; //игра не окончена
}

int Field::WhoWon(int turnRow, int turnColumn)
{
	return WhoWon(turnRow*size + turnColumn);
}

bool Field::PlaceSymbol(int n)
{
	if (_field[n] == 0)
	{
		_field[n] = _activePlayerNumber;
		return true;
	}
	else return false;
}

bool Field::PlaceSymbol(int row, int column)
{
	return PlaceSymbol(row*size + column);
}