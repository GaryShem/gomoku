#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	Field::size
#include <string>
#include <array>

class Field
{
public:
	//размер поля
	static const int size = 15;
	//сколько нужно в ряд для победы
	static const int streak = 5;
	//состояние игры
	enum GameState { NotFinished, KrestikiWon, NolikiWon, Draw };
	//для самоидентификации игроков
	enum Player { Krestiki = 1, Noliki };
	//инициализация поля
	Field();
	~Field() {};

	//значки игроков и значок незанятого поля
	//можно играть в "слепое" гомоку - поставить везде пробельчики и играть по памяти
	static char* GameSymbols[3]; //= { ' ', 'X', 'O' };

	//получить текущее состояние игры (закончена ли и кто выиграл)
	GameState GetGamestate();

	//функция инициации хода
	GameState TakeTurn (int n);
	GameState TakeTurn(int row, int column);

	//запросить номер игрока, который сейчас делает ход
	Player GetActivePlayer();

	//запросить, что находится в определённой клеточке
	char GetCell(int cellIndex);
	char GetCell(int cellRow, int cellColumn);

	//преобразование массива к std::string. Мало ли.
	std::string toString();

	//определяет, закончена ли игра и кто победил
	GameState WhoWon(int turnIndex);
	GameState WhoWon(int turnRow, int turnColumn);
private:

	//сменить активного игрока
	void SwitchPlayer();

	//активный игрок
	Player _activePlayer = Player::Krestiki;

	//состояние игры
	GameState _gameState = NotFinished;

	//проверяет по координатам, находится ли клетка внутри поля
	bool IsWithinBounds(int n);
	bool IsWithinBounds(int row, int column);

	//пытаемся поставить знак указанного игрока
	//если ход валиден, метод вернёт true
	//если такой ход сделать нельзя (за пределами поля или уже есть знак) - вернёт false
	bool PlaceSymbol(int n);
	bool PlaceSymbol(int row, int column);

	int _lastTurn = -1;
	//направления - вниз, вправо, вправо-вниз, вправо-вверх
	enum Directions { DOWN, RIGHT, DOWNRIGHT, UPRIGHT};
	//внутреннее представление поля
	char _field[size*size];
};

#endif