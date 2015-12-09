#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	15
#include <string>
#include <array>

class Field
{
public:
	//номер игрока на этой машине
	int GetPlayerNumber;
	//размер поля
	static const int size = SIZE;
	//инициализация поля
	Field();
	~Field();
	//значки игроков
	const char playerOneSymbol = 'X';
	const char playerTwoSymbol = 'O';
	//преобразование массива к std::string. Мало ли.
	std::string toString();
	//пытаемся сделать ход
	//если ход валиден, метод вернёт true
	//если такой ход сделать нельзя (за пределами поля или уже есть знак) - вернёт false
	bool MakeTurn(int n, char symbol);
	bool MakeTurn(int row, int column, char symbol);
	//проверяет по координатам, находится ли клетка внутри поля
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);
	//определяет, закончена ли игра и кто победил
	int WhoWon(int turnIndex);
	int WhoWon(int turnRow, int turnColumn);
private:
	int _playerNumber;
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	char _field[size*size];
};

#endif