#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	Field::size
#include <string>
#include <array>

class Field
{
public:
	//������ ����
	static const int size = 15;
	//������� ����� � ��� ��� ������
	static const int streak = 5;
	//��������� ����
	enum GameState { NotFinished, KrestikiWon, NolikiWon, Draw };
	//��� ����������������� �������
	enum Player { Krestiki = 1, Noliki };
	//������������� ����
	Field();
	~Field() {};

	//������ ������� � ������ ���������� ����
	//����� ������ � "������" ������ - ��������� ����� ����������� � ������ �� ������
	static char* GameSymbols[3]; //= { ' ', 'X', 'O' };

	//�������� ������� ��������� ���� (��������� �� � ��� �������)
	GameState GetGamestate();

	//������� ��������� ����
	GameState TakeTurn (int n);
	GameState TakeTurn(int row, int column);

	//��������� ����� ������, ������� ������ ������ ���
	Player GetActivePlayer();

	//���������, ��� ��������� � ����������� ��������
	char GetCell(int cellIndex);
	char GetCell(int cellRow, int cellColumn);

	//�������������� ������� � std::string. ���� ��.
	std::string toString();

	//����������, ��������� �� ���� � ��� �������
	GameState WhoWon(int turnIndex);
	GameState WhoWon(int turnRow, int turnColumn);
private:

	//������� ��������� ������
	void SwitchPlayer();

	//�������� �����
	Player _activePlayer = Player::Krestiki;

	//��������� ����
	GameState _gameState = NotFinished;

	//��������� �� �����������, ��������� �� ������ ������ ����
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);

	//�������� ��������� ���� ���������� ������
	//���� ��� �������, ����� ����� true
	//���� ����� ��� ������� ������ (�� ��������� ���� ��� ��� ���� ����) - ����� false
	bool PlaceSymbol(int n);
	bool PlaceSymbol(int row, int column);

	int _lastTurn = -1;
	//����������� - ����, ������, ������-����, ������-�����
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	//���������� ������������� ����
	char _field[size*size];
};

#endif