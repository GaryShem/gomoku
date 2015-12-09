#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	15
#include <string>
#include <array>

class Field
{
public:
	//������ ����
	static const int size = SIZE;
	static const int streak = 5;

	//������������� ����
	Field();
	~Field() {};

	//������ ������� � ������ ���������� ����
	//����� ������ � "������" ������ - ��������� ����� ����������� � ������ �� ������
	static char* GameSymbols[3]; //= { ' ', 'X', 'O' };
//	const char playerOneSymbol = 'X';
//	const char playerTwoSymbol = 'O';
//	const char neutralSymbol = ' ';

	//������� ��������� ����
	int TakeTurn (int n, int& player);
	int TakeTurn (int row, int column, int& player);

	//�������������� ������� � std::string. ���� ��.
	std::string toString();

	//����������, ��������� �� ���� � ��� �������
	int WhoWon(int turnIndex);
	int WhoWon(int turnRow, int turnColumn);
private:
	//��������� �� �����������, ��������� �� ������ ������ ����
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);

	//�������� ��������� ���� ���������� ������
	//���� ��� �������, ����� ����� true
	//���� ����� ��� ������� ������ (�� ��������� ���� ��� ��� ���� ����) - ����� false
	bool PlaceSymbol(int n);
	bool PlaceSymbol(int row, int column);

	int _lastTurn = -1;
	//����� ������, ������� ����� ������
	int _activePlayerNumber = 1;
	//����������� - ����, ������, ������-����, ������-�����
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	//���������� ������������� ����
	char _field[size*size];
};

#endif