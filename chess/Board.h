#pragma once
#include "Cell.h"
#include "header.h"

class Board
{
private:
	static Cell field[8][8];
public:

	static Cell* getCell(int i, int j);

	static void fieldInitialization();

	static void draw(sf::RenderWindow& window);

	Board();

	~Board();
};