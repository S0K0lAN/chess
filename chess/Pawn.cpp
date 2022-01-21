#include "Pawn.h"

State Pawn::getColor() {
	return this->color;
}

void Pawn::setColor(State color) {
	this->color = color;
}

void Pawn::eat() {
	this->is_eaten = 1;
}

void Pawn::move(Move to) {
	if (to.type == MoveType::Move) {
		this->getCell().setState(State::Free);
		this->getCell().setPiece(Type::None);
		to.cell->setState(this->getColor());
		to.cell->setPiece(Type::Pawn);
		this->setCell(*to.cell);
	}
	if (to.type == MoveType::Eat) {
		this->getCell().setState(State::Free);
		this->getCell().setPiece(Type::None);
		to.cell->setState(this->getColor());
		to.cell->setPiece(Type::Pawn);
		this->setCell(*to.cell);
		
	}
}

std::vector<Move> Pawn::getLegalMoves() {
	std::vector<Move> moves;
	Move move;
	int coordx, coordy;
	if (this->isFirstMove) {
		if ((this->getColor() == State::White) && (Board::getCell(this->x, this->y - 2)->getState() == State::Free)) {
			move.cell = (Board::getCell(this->x, this->y - 2));
			move.type = MoveType::Move;
			moves.push_back(move);
		}
		if ((this->getColor() == State::Black) && (Board::getCell(this->x, this->y + 2)->getState() == State::Free)) {
			move.cell = (Board::getCell(this->x, this->y + 2));
			move.type = MoveType::Move;
			moves.push_back(move);
		}
	}

	if (this->getColor() == State::White) {
		coordx = this->x + 1;
		coordy = this->y - 1;
		if (coordx <= 7 && coordy >= 0) {
			if ((Board::getCell(coordx, coordy)->getState() != State::Free) && (Board::getCell(coordx, coordy)->getState() != this->getColor())) {
				move.cell = (Board::getCell(coordx, coordy));
				move.type = MoveType::Eat;
				moves.push_back(move);
			}
		}

		coordx = this->x - 1;
		coordy = this->y - 1;
		if (coordx >= 0 && coordy >= 0) {
			if ((Board::getCell(coordx, coordy)->getState() != State::Free) && (Board::getCell(coordx, coordy)->getState() != this->getColor())) {
				move.cell = (Board::getCell(coordx, coordy));
				move.type = MoveType::Eat;
				moves.push_back(move);
			}
		}

		coordx = this->x;
		coordy = this->y - 1;
		if (coordy >= 0) {
			if (Board::getCell(coordx, coordy)->getState() == State::Free) {
				move.cell = Board::getCell(coordx, coordy);
				move.type = MoveType::Move;
			}
		}
	}

	if (this->getColor() == State::Black) {
		coordx = this->x + 1;
		coordy = this->y + 1;
		if (coordx <= 7 && coordy <= 7) {
			if ((Board::getCell(coordx, coordy)->getState() != State::Free) && (Board::getCell(coordx, coordy)->getState() != this->getColor())) {
				move.cell = (Board::getCell(coordx, coordy));
				move.type = MoveType::Eat;
				moves.push_back(move);
			}
		}

		coordx = this->x - 1;
		coordy = this->y + 1;
		if (coordx >= 0 && coordy <= 7) {
			if ((Board::getCell(coordx, coordy)->getState() != State::Free) && (Board::getCell(coordx, coordy)->getState() != this->getColor())) {
				move.cell = (Board::getCell(coordx, coordy));
				move.type = MoveType::Eat;
				moves.push_back(move);
			}
		}

		coordx = this->x;
		coordy = this->y + 1;
		if (coordy >= 0) {
			if (Board::getCell(coordx, coordy)->getState() == State::Free) {
				move.cell = Board::getCell(coordx, coordy);
				move.type = MoveType::Move;
			}
		}
	}
	return moves;
}

Cell& Pawn::getCell() {
	return this->cell;
}

void Pawn::setCell(Cell cell) {
	this->cell = cell;
}