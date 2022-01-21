#pragma once
#include <SFML/Graphics.hpp>
#include "Cell.h"
#include "Board.h"
#include <vector>
#include "header.h"

class Pawn
{
private:
	sf::Sprite sprite;
	int is_eaten = 0;
	State color;
	Cell cell;
public:
	bool isFirstMove = 1;
	int x, y;

	void move(Move to);

	std::vector<Move> getLegalMoves();

	State getColor();

	void setColor(State color);

	Cell& getCell();

	void setCell(Cell cell);

	void eat();

};
