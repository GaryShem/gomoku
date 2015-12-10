#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	15
#include <string>
#include <array>

class Field
{
public:
	//размер поля
	static const int size = SIZE;
	static const int streak = 5;

	//инициализация поля
	Field();
	~Field() {};

	//значки игроков и значок незанятого поля
	//можно играть в "слепое" гомоку - поставить везде пробельчики и играть по памяти
	static char* GameSymbols[3]; //= { ' ', 'X', 'O' };

	int GetGamestate();

	//функция инициации хода
	int TakeTurn (int n, int& player);
	int TakeTurn (int row, int column, int& player);

	//преобразование массива к std::string. Мало ли.
	std::string toString();

	//определяет, закончена ли игра и кто победил
	int WhoWon(int turnIndex);
	int WhoWon(int turnRow, int turnColumn);
private:
	//состояние игры
	int _gameState = 0;

	//проверяет по координатам, находится ли клетка внутри поля
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);

	//пытаемся поставить знак указанного игрока
	//если ход валиден, метод вернёт true
	//если такой ход сделать нельзя (за пределами поля или уже есть знак) - вернёт false
	bool PlaceSymbol(int n);
	bool PlaceSymbol(int row, int column);

	int _lastTurn = -1;
	//номер игрока, который ходит сейчас
	int _activePlayerNumber = 1;
	//направления - вниз, вправо, вправо-вниз, вправо-вверх
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	//внутреннее представление поля
	char _field[size*size];
};

#endif