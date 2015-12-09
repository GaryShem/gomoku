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
int Field::WhoWon(int turnIndex)
{
	int directions[4][2] = { { 1, 0 }, { 0, 1 }, { -1, 1 }, { 1, 1 } };
	//��������� ������ �����������
	for (int k = 0; k < 4; k++)
	{
		int limit_i = directions[k][0] * 4;
		int limit_j = directions[k][1] * 4;
		int count = 0;

		//��� �� ���� �� 4 � ������� ������� �� 4 � ������� �������
		int i = directions[k][0] * (-4);
		int j = directions[k][1] * (-4);
		while (i <= limit_i && j <= limit_j)
		{
			//���� ������ �� ���������
			//���� ��� ������ �� ��������� � "�������" �������, �� ����� �� ����� ������ �� ����,
			//������� ����� ������ ���������� �������� �����, � �� �������� �� ����
			if (IsWithinBounds(i, j) == false)
				continue;
			else if (_field[i*size + j] == _field[turnIndex])
			{ //�����, ���� �� ��������� ������ ������, �� ����������� ������� �����
				count++;
			}
			
			else //if (_field[i*size + j] != _field[turnIndex])
			{	//�����, ���� �� ��������� �� ��� ������ - ������ ��� �����, �� ����� ����������,
				//� �������� �������
				count = 0;
			}
			//��������� � ������ ��� �����������
			i += directions[k][0];
			j += directions[k][1];
		}
		if (count >= 5)
		{
			if (_field[turnIndex] == playerOneSymbol)
				return 1; //������� ����� ���� - ��������
			if (_field[turnIndex] == playerTwoSymbol)
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