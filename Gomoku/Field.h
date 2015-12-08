#ifndef FIELD_H_
#define FIELD_H_

#define SIZE	15
#include <string>

class Field
{
public:
	static const int size = SIZE;
	char field[size*size];
	Field();
	~Field();
	std::string toString();
	bool MakeTurn(int n, char symbol);
	bool MakeTurn(int row, int column, char symbol);
};

#endif