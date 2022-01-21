#include "Cell.h"

void Cell::setState(State state) {
	this->state = state;
}

bool Cell::operator==(Cell cell) {
	return (this->x == cell.x) && (this->y == cell.y);
}

State Cell::getState() {
	return this->state;
}

sf::RectangleShape& Cell::getSquare() {
	return this->square;
}

Type Cell::getPiece() {
	return this->piece;
}

void Cell::setPiece(Type piece) {
	this->piece = piece;
}

Cell::Cell() {}

Cell::~Cell() {}