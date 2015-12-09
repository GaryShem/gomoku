#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	15
#include <string>
#include <array>

class Field
{
public:
	//����� ������ �� ���� ������
	int GetPlayerNumber;
	//������ ����
	static const int size = SIZE;
	//������������� ����
	Field();
	~Field();
	//������ �������
	const char playerOneSymbol = 'X';
	const char playerTwoSymbol = 'O';
	//�������������� ������� � std::string. ���� ��.
	std::string toString();
	//�������� ������� ���
	//���� ��� �������, ����� ����� true
	//���� ����� ��� ������� ������ (�� ��������� ���� ��� ��� ���� ����) - ����� false
	bool MakeTurn(int n, char symbol);
	bool MakeTurn(int row, int column, char symbol);
	//��������� �� �����������, ��������� �� ������ ������ ����
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);
	//����������, ��������� �� ���� � ��� �������
	int WhoWon(int turnIndex);
	int WhoWon(int turnRow, int turnColumn);
private:
	int _playerNumber;
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	char _field[size*size];
};

#endif