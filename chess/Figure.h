#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Board.h"
#include "Cell.h"
#include "Move.h"
#include "header.h"

class Figure
{
private:
	State color;
	Cell* cell;
public:
	Type type;
	static std::vector<Figure> figures;
	sf::Sprite sprite;
	sf::Texture texture;
	bool isFirstMove = true;
	bool isEaten = false;
	int x, y;
	std::vector<Cell*> underAttack;

	void move(Move to);

	static bool isCheck(State state);

	static std::vector<Move> getAllMoves(State state);

	static void figuresInitialization();

	static Figure* getFigure(int x, int y);

	static int getFigureIndex(int x, int y);

	std::vector<Move> getLegalMoves();

	std::vector<Move> getLegalPawnMoves();

	std::vector<Move> getLegalQueenMoves();

	std::vector<Move> getLegalKingMoves();

	std::vector<Move> getLegalKnightMoves();

	std::vector<Move> getLegalBishopMoves();

	std::vector<Move> getLegalRookMoves();
	
	static void draw(sf::RenderWindow& window);

	State getColor();

	void setColor(State color);

	Cell* getCell();

	void setCell(Cell* cell);

	Figure();

	Figure(const Figure& other);

	~Figure();
};