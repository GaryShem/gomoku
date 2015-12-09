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
������������ ��������:
������: �������-������ � ������� ������
-1	- ���� ���������� ������
0	- ���� �� ��������
1	- ������� 1-� �����
2	- ������� 2-� �����
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
	������������ ��������:
	-1	- ���� ���������� ������
	0	- ���� �� ��������
	1	- ������� 1-� �����
	2	- ������� 2-� �����
*/
int Field::WhoWon(int turnIndex = -1)
{
	//����� ����� ���� ������ �� ������ ���
	//� ���� ������ �� �����, ��� ���� ��-������ ������������
	if (turnIndex < 0)
		return 0;
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
	if (_field[turnIndex])
	//��������� ������ �����������
	for (int k = 0; k < 4; k++)
	{
		int count = 0;

		//��� �� ���� �� �� �������� � ��������
		//����� 9 ����� - �� 4 � ������� � ������� ������� (����� � ������� ������� ���� 5 - ��� ���������� ��������)
		int row = directions[k][0] * (-4);
		int column = directions[k][1] * (-4);
		for (int step = 0; step < 9; step++)
		{
			//���� ��� ������ �� ��������� � "�������" �������, �� ����� �� ����� ������ �� ����,
			//������� ����� ������ ���������� �������� �����, � �� �������� �� ����
			if (IsWithinBounds(row, column) == false)
				continue;
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
				return 1; //������� ����� ���� - ��������
			if (_field[turnIndex] == 2)
				return 2; //������� ����� ��� - ������
		}
	}
	if (toString().find(' ') == std::string::npos)
		return -1; //��� ���� ���������, ���������� ���� �� ����� - ���� ����������� ������
	return 0; //���� �� ��������
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