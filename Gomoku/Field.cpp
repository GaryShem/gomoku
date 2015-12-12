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

Field::GameState Field::GetGamestate()
{
	return _gameState;
}

/**
������������ ��������:
������: �������-������ � ������� ������
-1	- ���� ���������� ������
0	- ���� �� ��������
1	- ������� 1-� �����
2	- ������� 2-� �����
*/
Field::GameState Field::TakeTurn(int n)
{
	if (_gameState != NotFinished)
		throw "Game is over, no turns can be taken";
	GameState winner;
	if ((winner = WhoWon(_lastTurn)) != NotFinished)
	{
		_gameState = winner;
		return winner;
	}

	//���� �������� ����� �� ������� ����
	if (IsWithinBounds(n) == false)
		throw "your desired turn is outside the field";

	//���� �������� ����� � ��� ������� ��������
	if (PlaceSymbol(n) == false)
		throw "this cell is occupied";
	
	SwitchPlayer();

	_lastTurn = n;
	_gameState = WhoWon(n);
	return _gameState;
}

Field::GameState Field::TakeTurn(int row, int column)
{
	return TakeTurn(row*size + column);
}

char Field::GetCell(int cellIndex)
{
	if (IsWithinBounds(cellIndex) == false)
		throw "Cell out of bounds";
	return _field[cellIndex];
}

char Field::GetCell(int cellRow, int cellColumn)
{
	return GetCell(cellRow*size + cellColumn);
}

Field::Player Field::GetActivePlayer()
{
	return _activePlayer;
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

//���������, ��������� �� ��������� ������ � �������� ����
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
	���������� ����������.
	������������ ��������:
	-1	- ���� ���������� ������
	0	- ���� �� ��������
	1	- ������� 1-� �����
	2	- ������� 2-� �����
*/
Field::GameState Field::WhoWon(int turnIndex)
{
	//����� ����� ���� ������ � ����� ������ ����, ����� ������ �����
	//� ���� ������ �� �����, ��� ���� ��-������ ������������
	if (turnIndex < 0)
		return NotFinished;
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
		int count = 0;
	//��������� ������ �����������
	for (int k = 0; k < 4 && count < 5; k++)
	{
		count = 0;
		//��� �� ���� �� �� �������� � ��������
		//����� 9 ����� - �� 4 � ������� � ������� ������� (����� � ������� ������� ���� 5 - ��� ���������� ��������)
		int row = (turnIndex/size) + directions[k][0] * (-4);
		int column = (turnIndex%size) + directions[k][1] * (-4);
		for (int step = 0, limit = streak*2-1; step < limit && count < 5; step++)
		{
			//���� ��� ������ �� ��������� ����, �� ��� �� ����� ���� ������ �����
			//������� ����� ������ ���������� �������� �����, � �� �������� �� ����
			if (IsWithinBounds(row, column) == false)
			{
				//��������� � ������ ��� �����������
				//row += directions[k][0];
				//column += directions[k][1];
				//continue;
			}
			else if (_field[row*size + column] == _field[turnIndex])
			{ //�����, ���� �� ��������� ������ ������, �� ����������� ������� �����
				count++;
			}
			
			else //if (_field[i*size + j] != _field[turnIndex])
			{	//�����, ���� �� ��������� �� ��� ������ - ������ ��� �����, �� ����� ����������,
				//� �������� �������
				count = 0;
			}
			//��������� � ������ ��� �����������
			row += directions[k][0];
			column += directions[k][1];
		}
		if (count >= 5)
		{
			if (_field[turnIndex] == 1)
				return KrestikiWon; //������� ����� ���� - ��������
			if (_field[turnIndex] == 2)
				return NolikiWon; //������� ����� ��� - ������
		}
	}
	if (toString().find(GameSymbols[0]) == std::string::npos)
		return Draw; //��� ���� ���������, ���������� ���� �� ����� - ���� ����������� ������
	return NotFinished; //���� �� ��������
}

Field::GameState Field::WhoWon(int turnRow, int turnColumn)
{
	return WhoWon(turnRow*size + turnColumn);
}

void Field::SwitchPlayer()
{
	if (_activePlayer == Krestiki)
		_activePlayer = Noliki;
	else
		_activePlayer = Krestiki;
}

bool Field::PlaceSymbol(int n)
{
	if (_field[n] == 0)
	{
		_field[n] = (int)_activePlayer;
		return true;
	}
	else return false;
}

bool Field::PlaceSymbol(int row, int column)
{
	return PlaceSymbol(row*size + column);
}