#pragma once
#include "Cell.h"

class Move {
public:
	Cell* cell;
	MoveType type;
	Move() {}
	~Move() {}
};
