#pragma once
#include "header.h"

class Cell
{
public:

	int x;
	int y;
	bool isSelected = false;
	bool isUnderAttackByWhite = false;
	bool isUnderAttackByBlack = false;

	bool operator ==(Cell cell);

	Cell();

	~Cell();

	State getState();

	void setState(State state);

	Type getPiece();

	void setPiece(Type piece);

	sf::RectangleShape& getSquare();

private:
	sf::RectangleShape square;
	State state;
	Type piece;

};