#include "Figure.h"
#include <iostream>

void Figure::draw(sf::RenderWindow& window) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].isEaten) {
			continue;
		}
		window.draw(figures[i].sprite);
	}
}

Figure* Figure::getFigure(int x, int y) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].isEaten)
			continue;
		if (figures[i].x == x && figures[i].y == y) {
			return &figures[i];
		}
	}
}

int Figure::getFigureIndex(int x, int y) {
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].isEaten)
			continue;
		if (figures[i].x == x && figures[i].y == y) {
			return i;
		}
	}
}

std::vector<Figure> Figure::figures = { Figure() };
void Figure::figuresInitialization() {
	figures.clear();
	sf::Sprite rook, pawn, queen, king, knight, bishop, Brook, Bpawn, Bqueen, Bking, Bknight, Bbishop;
	sf::Texture bq, bk, bn, bb, bp, br, wq, wk, wn, wp, wb, wr;
	wr.loadFromFile("../chess/images/wr.png");
	rook.setTexture(wr);
	wp.loadFromFile("../chess/images/wp.png");
	pawn.setTexture(wp);
	wq.loadFromFile("../chess/images/wq.png");
	queen.setTexture(wq);
	wk.loadFromFile("../chess/images/wk.png");
	king.setTexture(wk);
	wn.loadFromFile("../chess/images/wn.png");
	knight.setTexture(wn);
	wb.loadFromFile("../chess/images/wb.png");
	bishop.setTexture(wb);

	br.loadFromFile("../chess/images/br.png");
	Brook.setTexture(br);
	bp.loadFromFile("../chess/images/bp.png");
	Bpawn.setTexture(bp);
	bq.loadFromFile("../chess/images/bq.png");
	Bqueen.setTexture(bq);
	bk.loadFromFile("../chess/images/bk.png");
	Bking.setTexture(bk);
	bn.loadFromFile("../chess/images/bn.png");
	Bknight.setTexture(bn);
	bb.loadFromFile("../chess/images/bb.png");
	Bbishop.setTexture(bb);

	rook.setScale(Figures_ScaleX, Figures_ScaleY);
	Brook.setScale(Figures_ScaleX, Figures_ScaleY);
	bishop.setScale(Figures_ScaleX, Figures_ScaleY);
	Bbishop.setScale(Figures_ScaleX, Figures_ScaleY);
	knight.setScale(Figures_ScaleX, Figures_ScaleY);
	Bknight.setScale(Figures_ScaleX, Figures_ScaleY);
	queen.setScale(Figures_ScaleX, Figures_ScaleY);
	Bqueen.setScale(Figures_ScaleX, Figures_ScaleY);
	king.setScale(Figures_ScaleX, Figures_ScaleY);
	Bking.setScale(Figures_ScaleX, Figures_ScaleY);
	pawn.setScale(Figures_ScaleX, Figures_ScaleY);
	Bpawn.setScale(Figures_ScaleX, Figures_ScaleY);

	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (j > 1 && j < 6)
				continue;
			Figure f;
			f.x = i;
			f.y = j;
			f.isEaten = false;
			f.setCell(Board::getCell(i, j));
			if (j < 2) {
				f.setColor(State::Black);
			}
			if (j > 5) {
				f.setColor(State::White);
			}
			if (j == 1) {
				f.sprite = Bpawn;
				f.texture = bp;
				f.type = Type::Pawn;
			}
			if (j == 6) {
				f.sprite = pawn;
				f.texture = wp;
				f.type = Type::Pawn;
			}
			if (j == 0) {
				if (i == 4) {
					f.sprite = Bking;
					f.texture = bk;
					f.type = Type::King;
				} // king
				if (i == 3) {
					f.sprite = Bqueen;
					f.texture = bq;
					f.type = Type::Queen;
				} // queen
				if (i == 2 || i == 5) {
					f.sprite = Bbishop;
					f.texture = bb;
					f.type = Type::Bishop;
				} // bishop
				if (i == 1 || i == 6) {
					f.sprite = Bknight;
					f.texture = bn;
					f.type = Type::Knight;
				} // knight
				if (i == 0 || i == 7) {
					f.sprite = Brook;
					f.texture = br;
					f.type = Type::Rook;
				} // rook
			} // black
			if (j == 7) {
				if (i == 4) {
					f.sprite = king;
					f.texture = wk;
					f.type = Type::King;
				} // king
				if (i == 3) {
					f.sprite = queen;
					f.texture = wq;
					f.type = Type::Queen;
				} // queen
				if (i == 2 || i == 5) {
					f.sprite = bishop;
					f.texture = wb;
					f.type = Type::Bishop;
				} // bishop
				if (i == 1 || i == 6) {
					f.sprite = knight;
					f.texture = wn;
					f.type = Type::Knight;
				} // knight
				if (i == 0 || i == 7) {
					f.sprite = rook;
					f.texture = wr;
					f.type = Type::Rook;
				} // rook
			} // white
			f.sprite.setPosition(Board::getCell(i, j)->getSquare().getPosition());
			f.type = Board::getCell(i, j)->getPiece();
			figures.push_back(f);
		}
	}
}

void Figure::move(Move to) {
	if (to.type == MoveType::Move) {
		this->getCell()->setState(State::Free);
		this->getCell()->setPiece(Type::None);
		to.cell->setState(this->getColor());
		to.cell->setPiece(this->type);
		this->setCell(to.cell);
		this->x = to.cell->x;
		this->y = to.cell->y;
	}
	if (to.type == MoveType::Eat) {
		this->getCell()->setState(State::Free);
		this->getCell()->setPiece(Type::None);
		to.cell->setState(this->getColor());
		to.cell->setPiece(this->type);
		getFigure(to.cell->x, to.cell->y)->isEaten = true;
		this->setCell(to.cell);
		this->x = to.cell->x;
		this->y = to.cell->y;
	}

	Move move;
	if (to.type == MoveType::ShortCastling) {
		if (this->getColor() == State::White) {
			this->getCell()->setState(State::Free);
			this->getCell()->setPiece(Type::None);
			to.cell->setPiece(Type::King);
			to.cell->setState(State::White);
			this->setCell(to.cell);
			this->x = to.cell->x;
			this->y = to.cell->y;
			move.cell = Board::getCell(5, 7);
			move.type = MoveType::Move;
			getFigure(7, 7)->move(move);
		}
		if (this->getColor() == State::Black) {
			this->getCell()->setState(State::Free);
			this->getCell()->setPiece(Type::None);
			to.cell->setPiece(Type::King);
			to.cell->setState(State::Black);
			this->setCell(to.cell);
			this->x = to.cell->x;
			this->y = to.cell->y;
			move.cell = Board::getCell(5, 0);
			move.type = MoveType::Move;
			getFigure(7, 0)->move(move);
		}
	}

	if (to.type == MoveType::LongCastling) {
		if (this->getColor() == State::White) {
			this->getCell()->setState(State::Free);
			this->getCell()->setPiece(Type::None);
			to.cell->setPiece(Type::King);
			to.cell->setState(State::White);
			this->setCell(to.cell);
			this->x = to.cell->x;
			this->y = to.cell->y;
			move.cell = Board::getCell(3, 7);
			move.type = MoveType::Move;
			getFigure(0, 7)->move(move);
		}
		if (this->getColor() == State::Black) {
			this->getCell()->setState(State::Free);
			this->getCell()->setPiece(Type::None);
			to.cell->setPiece(Type::King);
			to.cell->setState(State::Black);
			this->setCell(to.cell);
			this->x = to.cell->x;
			this->y = to.cell->y;
			move.cell = Board::getCell(3, 0);
			move.type = MoveType::Move;
			getFigure(0, 0)->move(move);
		}
	}
	this->isFirstMove = 0;
	for (int i = 0; i < this->underAttack.size(); i++) {
		if (this->color == State::Black)
			this->underAttack[i]->isUnderAttackByBlack = false;
		else
			this->underAttack[i]->isUnderAttackByWhite = false;
	}
	this->underAttack.clear();
	this->getLegalMoves();
}

std::vector<Move> Figure::getLegalMoves() {
	std::vector<Move> legalmoves;
	switch (this->type) {
	case Type::King:
		legalmoves = this->getLegalKingMoves();
		break;
	case Type::Queen:
		legalmoves = this->getLegalQueenMoves();
		break;
	case Type::Rook:
		legalmoves = this->getLegalRookMoves();
		break;
	case Type::Bishop:
		legalmoves = this->getLegalBishopMoves();
		break;
	case Type::Knight:
		legalmoves = this->getLegalKnightMoves();
		break;
	case Type::Pawn:
		legalmoves = this->getLegalPawnMoves();
		break;
	}
	if (this->type == Type::Pawn) {
		if (this->color == State::Black) {
			if (this->x - 1 >= 0 && this->y + 1 < 8) {
				if (Board::getCell(this->x - 1, this->y + 1)->getState() == this->color
					|| Board::getCell(this->x - 1, this->y + 1)->getState() == State::Free) {
					Board::getCell(this->x - 1, this->y + 1)->isUnderAttackByBlack = true;
					this->underAttack.push_back(Board::getCell(this->x - 1, this->y + 1));
				}
			}
			if (this->x + 1 < 8 && this->y + 1 < 8) {
				if (Board::getCell(this->x + 1, this->y + 1)->getState() == this->color
					|| Board::getCell(this->x + 1, this->y + 1)->getState() == State::Free) {
					Board::getCell(this->x + 1, this->y + 1)->isUnderAttackByBlack = true;
					this->underAttack.push_back(Board::getCell(this->x + 1, this->y + 1));
				}
			}
		}
		else {
			if (this->x - 1 >= 0 && this->y - 1 >= 0) {
				if (Board::getCell(this->x - 1, this->y - 1)->getState() == this->color
					|| Board::getCell(this->x - 1, this->y - 1)->getState() == State::Free) {
					Board::getCell(this->x - 1, this->y - 1)->isUnderAttackByWhite = true;
					this->underAttack.push_back(Board::getCell(this->x - 1, this->y - 1));
				}
			}
			if (this->x + 1 < 8 && this->y - 1 >= 0) {
				if (Board::getCell(this->x + 1, this->y - 1)->getState() == this->color
					|| Board::getCell(this->x + 1, this->y - 1)->getState() == State::Free) {
					Board::getCell(this->x + 1, this->y - 1)->isUnderAttackByWhite = true;
					this->underAttack.push_back(Board::getCell(this->x + 1, this->y - 1));
				}
			}
		}
	}
	else {
		for (int i = 0; i < legalmoves.size(); i++) {
			if (this->color == State::Black) {
				if (legalmoves[i].cell->getState() == State::Free
					|| legalmoves[i].cell->getState() == this->color) {
					legalmoves[i].cell->isUnderAttackByBlack = true;
					this->underAttack.push_back(legalmoves[i].cell);
				}
			}
			else {
				if (legalmoves[i].cell->getState() == State::Free
					|| legalmoves[i].cell->getState() == this->color) {
					legalmoves[i].cell->isUnderAttackByWhite = true;
					this->underAttack.push_back(legalmoves[i].cell);
				}
			}
		}
	}

	return legalmoves;
}

std::vector<Move> Figure::getLegalRookMoves() {
	std::vector<Move> horizontalmoves, verticalmoves, moves;
	Move move;
	for (int i = 0; i < 8; i++) {
		if (Board::getCell(i, this->y)->getState() == State::Free) {
			move.cell = Board::getCell(i, this->y);
			move.type = MoveType::Move;
			horizontalmoves.push_back(move);
		}
		else if (i < this->x) { 
			if (Board::getCell(i, this->y)->getState() != this->getColor()) {
				horizontalmoves.clear();
				move.cell = Board::getCell(i, this->y);
				move.type = MoveType::Eat;
				horizontalmoves.push_back(move);
			}
			if (Board::getCell(i, this->y)->getState() == this->getColor()) {
				horizontalmoves.clear();
				if (this->color == State::Black) {
					Board::getCell(i, this->y)->isUnderAttackByBlack = true;
				}
				else {
					Board::getCell(i, this->y)->isUnderAttackByWhite = false;
				}
			}
		}
		else if (i > this->x) {
			if (Board::getCell(i, this->y)->getState() != this->getColor()) {
				move.cell = Board::getCell(i, this->y);
				move.type = MoveType::Eat;
				horizontalmoves.push_back(move);
				break;
			}
			if (Board::getCell(i, this->y)->getState() == this->getColor()) {
				this->underAttack.push_back(Board::getCell(i, this->y));
				if (this->color == State::Black) {
					Board::getCell(i, this->y)->isUnderAttackByBlack = true;
				}
				else {
					Board::getCell(i, this->y)->isUnderAttackByWhite = false;
				}
				break;
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		if (Board::getCell(this->x, i)->getState() == State::Free) {
			move.cell = Board::getCell(this->x, i);
			move.type = MoveType::Move;
			verticalmoves.push_back(move);
		}
		else if (i < this->y) {
			if (Board::getCell(this->x, i)->getState() != this->getColor()) {
				verticalmoves.clear();
				move.cell = Board::getCell(this->x, i);
				move.type = MoveType::Eat;
				verticalmoves.push_back(move);
			}
			if (Board::getCell(this->x, i)->getState() == this->getColor()) {
				verticalmoves.clear();
				if (this->color == State::Black) {
					Board::getCell(this->x, i)->isUnderAttackByBlack = true;
				}
				else {
					Board::getCell(this->x, i)->isUnderAttackByWhite = false;
				}
			}
		}
		else if (i > this->y) {
			if (Board::getCell(this->x, i)->getState() != this->getColor()) {
				move.cell = Board::getCell(this->x, i);
				move.type = MoveType::Eat;
				verticalmoves.push_back(move);
				break;
			}
			if (Board::getCell(this->x, i)->getState() == this->getColor()) {
				break;
				if (this->color == State::Black) {
					Board::getCell(this->x, i)->isUnderAttackByBlack = true;
				}
				else {
					Board::getCell(this->x, i)->isUnderAttackByWhite = false;
				}
			}
		}
	}
	for (int i = 0; i < horizontalmoves.size(); i++) {
		moves.push_back(horizontalmoves[i]);
	}
	for (int i = 0; i < verticalmoves.size(); i++) {
		moves.push_back(verticalmoves[i]);
	}
	return moves;
}

std::vector<Move> Figure::getLegalPawnMoves() {
	std::vector<Move> moves;
	Move move;
	int coordx, coordy;
	if (this->isFirstMove) {
		if ((this->getColor() == State::White)
			&& (Board::getCell(this->x, this->y - 2)->getState() == State::Free) 
			&& (Board::getCell(this->x, this->y - 1)->getState() == State::Free)) {
			move.cell = (Board::getCell(this->x, this->y - 2));
			move.type = MoveType::Move;
			moves.push_back(move);
		}
		if ((this->getColor() == State::Black) 
			&& (Board::getCell(this->x, this->y + 2)->getState() == State::Free) 
			&& (Board::getCell(this->x, this->y + 1)->getState() == State::Free)) {
			move.cell = (Board::getCell(this->x, this->y + 2));
			move.type = MoveType::Move;
			moves.push_back(move);
		}
	}

	if ((this->color == State::White) && (this->y != 6)) {
		this->isFirstMove = false;
	}
	if ((this->color == State::Black) && (this->y != 1)) {
		this->isFirstMove = false;
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
			if (Board::getCell(coordx, coordy)->getState() == State::White) {
				this->underAttack.push_back(Board::getCell(coordx, coordy));
				Board::getCell(coordx, coordy)->isUnderAttackByWhite = true;
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
			if (Board::getCell(coordx, coordy)->getState() == State::White) {
				this->underAttack.push_back(Board::getCell(coordx, coordy));
				Board::getCell(coordx, coordy)->isUnderAttackByWhite = true;
			}
		}

		coordx = this->x;
		coordy = this->y - 1;
		if (coordy >= 0) {
			if (Board::getCell(coordx, coordy)->getState() == State::Free) {
				move.cell = Board::getCell(coordx, coordy);
				move.type = MoveType::Move;
				moves.push_back(move);
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
			if (Board::getCell(coordx, coordy)->getState() == State::Black) {
				this->underAttack.push_back(Board::getCell(coordx, coordy));
				Board::getCell(coordx, coordy)->isUnderAttackByBlack = true;
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
			if (Board::getCell(coordx, coordy)->getState() == State::Black) {
				this->underAttack.push_back(Board::getCell(coordx, coordy));
				Board::getCell(coordx, coordy)->isUnderAttackByBlack = true;
			}
		}

		coordx = this->x;
		coordy = this->y + 1;
		if (coordy >= 0) {
			if (Board::getCell(coordx, coordy)->getState() == State::Free) {
				move.cell = Board::getCell(coordx, coordy);
				move.type = MoveType::Move;
				moves.push_back(move);
			}
		}
	}
	return moves;
}

std::vector<Move> Figure::getLegalBishopMoves() {
	Move move;
	std::vector<Move> mainmoves, sidemoves, moves;
	int mainX, mainY, sideX, sideY, x, y;
	if (this->x > this->y) {
		mainY = 0;
		mainX = this->x - this->y;
	}
	else {
		mainX = 0;
		mainY = this->y - this->x;
	}
	if (7 - this->y > this->x) {
		sideX = 0;
		sideY = 7 - ((7 - this->y) - this->x);
	}
	else {
		sideY = 7;
		sideX = this->x - (7 - this->y);
	}
	

	for (int i = 0; i < 8; i++) {
		if (mainX + i - 1 == 7 || mainY + i - 1 == 7)
			break;
		if (mainX + i == this->x && mainY + i == this->y)
			continue;
		if (Board::getCell(mainX + i, mainY + i)->getState() == State::Free) {
			move.cell = Board::getCell(mainX + i, mainY + i);
			move.type = MoveType::Move;
			mainmoves.push_back(move);
		}
		else if (mainX + i < this->x && mainY + i < this->y) {
			if (Board::getCell(mainX + i, mainY + i)->getState() != this->getColor()) {
				mainmoves.clear();
				move.cell = Board::getCell(mainX + i, mainY + i);
				move.type = MoveType::Eat;
				mainmoves.push_back(move);
			}
			if (Board::getCell(mainX + i, mainY + i)->getState() == this->getColor()) {
				mainmoves.clear();
			}
		}
		else if (mainX + i > this->x && mainY + i > this->y) {
			if (Board::getCell(mainX + i, mainY + i)->getState() != this->getColor()) {
				move.cell = Board::getCell(mainX + i, mainY + i);
				move.type = MoveType::Eat;
				mainmoves.push_back(move);
				break;
			}
			if (Board::getCell(mainX + i, mainY + i)->getState() == this->getColor()) {
				break;
			}
		}
	}

	for (int i = 0; i < 8; i++) {
		if (sideX + i - 1 == 7 || sideY - i + 1 == 0)
			break;
		if (sideX + i == this->x && sideY - i == this->y)
			continue;
		if (Board::getCell(sideX + i, sideY - i)->getState() == State::Free) {
			move.cell = Board::getCell(sideX + i, sideY - i);
			move.type = MoveType::Move;
			sidemoves.push_back(move);
		}
		else if (sideX + i < this->x && sideY - i > this->y) {
			if (Board::getCell(sideX + i, sideY - i)->getState() != this->getColor()) {
				sidemoves.clear();
				move.cell = Board::getCell(sideX + i, sideY - i);
				move.type = MoveType::Eat;
				sidemoves.push_back(move);
			}
			if (Board::getCell(sideX + i, sideY - i)->getState() == this->getColor()) {
				sidemoves.clear();
			}
		}
		else if (sideX + i > this->x && sideY - i < this->y) {
			if (Board::getCell(sideX + i, sideY - i)->getState() != this->getColor()) {
				move.cell = Board::getCell(sideX + i, sideY - i);
				move.type = MoveType::Eat;
				sidemoves.push_back(move);
				break;
			}
			if (Board::getCell(sideX + i, sideY - i)->getState() == this->getColor()) {
				break;
			}
		}
	}

	for (int i = 0; i < mainmoves.size(); i++) {
		moves.push_back(mainmoves[i]);
	}
	for (int i = 0; i < sidemoves.size(); i++) {
		moves.push_back(sidemoves[i]);
	}
	return moves;
}

std::vector<Move> Figure::getLegalQueenMoves() {
	std::vector<Move> bishop, rook, moves;
	bishop = this->getLegalBishopMoves();
	rook = this->getLegalRookMoves();

	for (int i = 0; i < bishop.size(); i++) {
		moves.push_back(bishop[i]);
	}
	for (int i = 0; i < rook.size(); i++) {
		moves.push_back(rook[i]);
	}
	return moves;
}

std::vector<Move> Figure::getLegalKnightMoves() {
	std::vector<Move> moves;
	Move move;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i == this->x && j == this->y)
				continue;
			if (abs(i - this->x) == 2 && abs(j - this->y) == 1) {
				if (Board::getCell(i, j)->getState() == State::Free) {
					move.cell = Board::getCell(i, j);
					move.type = MoveType::Move;
					moves.push_back(move);
				}
				else if (Board::getCell(i, j)->getState() == this->getColor())
					continue;
				else if (Board::getCell(i, j)->getState() != this->getColor()) {
					move.cell = Board::getCell(i, j);
					move.type = MoveType::Eat;
					moves.push_back(move);
				}
			}

			if (abs(i - this->x) == 1 && abs(j - this->y) == 2) {
				if (Board::getCell(i, j)->getState() == State::Free) {
					move.cell = Board::getCell(i, j);
					move.type = MoveType::Move;
					moves.push_back(move);
				}
				else if (Board::getCell(i, j)->getState() == this->getColor())
					continue;
				else if (Board::getCell(i, j)->getState() != this->getColor()) {
					move.cell = Board::getCell(i, j);
					move.type = MoveType::Eat;
					moves.push_back(move);
				}
			}
		}
	}
	return moves;
}

std::vector<Move> Figure::getAllMoves(State state) {
	std::vector<Move> allmoves, temp;
	for (int i = 0; i < figures.size(); i++) {
		if (figures[i].getColor() != state)
			continue;
		temp = figures[i].getLegalMoves();
		for (int x = 0; x < temp.size(); x++) {
			allmoves.push_back(temp[x]);
		}
	}
	return allmoves;
}

std::vector<Move> Figure::getLegalKingMoves() {
	std::vector<Move> legalmoves;
	Move move;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (abs(this->x - Board::getCell(i, j)->x) <= 1
				&& abs(this->y - Board::getCell(i, j)->y) <= 1) {
				if (this->color == State::Black) {
					if (!Board::getCell(i, j)->isUnderAttackByWhite) {
						if (Board::getCell(i, j)->getState() == State::Free) {
							move.cell = Board::getCell(i, j);
							move.type = MoveType::Move;
							legalmoves.push_back(move);
						}
						else {
							if (Board::getCell(i, j)->getState() == this->color)
								continue;
							else {
								move.cell = Board::getCell(i, j);
								move.type = MoveType::Eat;
								legalmoves.push_back(move);
							}
						}
					}
				}
				else {
					if (!Board::getCell(i, j)->isUnderAttackByBlack) {
						if (Board::getCell(i, j)->getState() == State::Free) {
							move.cell = Board::getCell(i, j);
							move.type = MoveType::Move;
							legalmoves.push_back(move);
						}
						else {
							if (Board::getCell(i, j)->getState() == this->color)
								continue;
							else {
								move.cell = Board::getCell(i, j);
								move.type = MoveType::Eat;
								legalmoves.push_back(move);
							}
						}
					}
				}
			}
		}
	}
	
	switch (this->getColor()) {
	case State::White:
		if (this->isFirstMove
			&& getFigure(7, 7)->isFirstMove
			&& Board::getCell(5, 7)->getState() == State::Free
			&& Board::getCell(6, 7)->getState() == State::Free) {
			move.cell = Board::getCell(6, 7);
			move.type = MoveType::ShortCastling;
			legalmoves.push_back(move);
		}
		if (this->isFirstMove
			&& getFigure(0, 7)->isFirstMove
			&& Board::getCell(2, 7)->getState() == State::Free
			&& Board::getCell(3, 7)->getState() == State::Free) {
			move.cell = Board::getCell(2, 7);
			move.type = MoveType::LongCastling;
			legalmoves.push_back(move);
		}
		break;
	case State::Black:
		if (this->isFirstMove
			&& getFigure(7, 0)->isFirstMove
			&& Board::getCell(5, 0)->getState() == State::Free
			&& Board::getCell(6, 0)->getState() == State::Free) {
			move.cell = Board::getCell(6, 0);
			move.type = MoveType::ShortCastling;
			legalmoves.push_back(move);
		}
		if (this->isFirstMove
			&& getFigure(0, 0)->isFirstMove
			&& Board::getCell(2, 0)->getState() == State::Free
			&& Board::getCell(3, 0)->getState() == State::Free) {
			move.cell = Board::getCell(2, 0);
			move.type = MoveType::LongCastling;
			legalmoves.push_back(move);			}
		break;
	}


	return legalmoves;
}

bool Figure::isCheck(State state) {
	std::vector<Move> moves;
	for (int i = 0; i < figures.size(); i++) {
		if (state == figures[i].getColor()) {
			moves = figures[i].getLegalMoves();
			for (int x = 0; x < moves.size(); x++) {
				if (moves[x].type == MoveType::Eat
					&& moves[x].cell->getPiece() == Type::King
					&& moves[x].cell->getState() != figures[i].getColor()) {
					return true;
				}
			}
		}
	}
	return false;
}

State Figure::getColor() {
	return this->color;
}

void Figure::setColor(State color) {
	this->color = color;
}

Cell* Figure::getCell() {
	return this->cell;
}

void Figure::setCell(Cell* cell) {
	this->cell = cell;
}

Figure::Figure() {}

Figure::~Figure() {}

Figure::Figure(const Figure& other)
	: color(other.color), texture(other.texture), sprite(other.sprite), cell(other.cell), x(other.x), y(other.y), type(other.type), isFirstMove(other.isFirstMove), isEaten(other.isEaten)
{
	sprite.setTexture(texture);
}