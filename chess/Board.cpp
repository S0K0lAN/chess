#include "Board.h"`

Cell* Board::getCell(int i, int j) {
	return &field[i][j];
}


Cell Board::field[8][8] = { Cell() };
void Board::fieldInitialization() {
	for (int i = 0; i < 8; ++i) {
		for (int j = 0; j < 8; ++j) {
			field[i][j].getSquare().setSize(sf::Vector2f(Cell_Size, Cell_Size));
			field[i][j].getSquare().setPosition(Cell_Size * i, Cell_Size * j);
			field[i][j].x = i;
			field[i][j].y = j;
			if (j < 2) {
				field[i][j].setState(State::Black);
			}
			else if (j > 5) {
				field[i][j].setState(State::White);
			}
			else {
				field[i][j].setState(State::Free);
			}
			if (i % 2) {
				if (j % 2)
					field[i][j].getSquare().setFillColor(Color_White);
				else
					field[i][j].getSquare().setFillColor(Color_Black);
			}
			else {
				if (j % 2)
					field[i][j].getSquare().setFillColor(Color_Black);
				else
					field[i][j].getSquare().setFillColor(Color_White);
			}
			field[i][j].getSquare().move(start_of_field);
		}
	}

	field[0][0].setPiece(Type::Rook);
	field[1][0].setPiece(Type::Knight);
	field[2][0].setPiece(Type::Bishop);
	field[3][0].setPiece(Type::Queen);
	field[4][0].setPiece(Type::King);
	field[5][0].setPiece(Type::Bishop);
	field[6][0].setPiece(Type::Knight);
	field[7][0].setPiece(Type::Rook);

	for (int i = 0; i < 8; i++) {
		for (int j = 1; j < 7; j++) {
			field[i][j].setPiece(Type::None);
		}
	}

	field[0][7].setPiece(Type::Rook);
	field[1][7].setPiece(Type::Knight);
	field[2][7].setPiece(Type::Bishop);
	field[3][7].setPiece(Type::Queen);
	field[4][7].setPiece(Type::King);
	field[5][7].setPiece(Type::Bishop);
	field[6][7].setPiece(Type::Knight);
	field[7][7].setPiece(Type::Rook);

	for (int i = 0; i < 8; i++) {
		field[i][1].setPiece(Type::Pawn);
		field[i][6].setPiece(Type::Pawn);
	}
}

void Board::draw(sf::RenderWindow& window) {
	// отрисовка границ
	sf::RectangleShape bounds;
	bounds.setSize(sf::Vector2f(Cell_Size * 8 + 10, Cell_Size * 8 + 10));
	bounds.move(start_of_field.x - 5, start_of_field.y - 5);
	bounds.setOutlineThickness(30);
	bounds.setFillColor(Color_Black);
	bounds.setOutlineColor(Color_White);
	window.draw(bounds);

	// буквы и цифры
	sf::Font font;
	font.loadFromFile("../chess/Nanum_Gothic/NanumGothic-Bold.ttf");
	sf::Text letters[8];
	sf::Text digits[8];
	for (int i = 0; i < 8; ++i) {
		letters[i].setString(char('8' - i));
		letters[i].setFillColor(Color_Black);
		letters[i].setFont(font);
		letters[i].setCharacterSize(20);
		letters[i].setPosition(-25, Cell_Size * (i + 0.5) - (letters[i].getGlobalBounds().height / 2));
		letters[i].move(start_of_field);
		window.draw(letters[i]);

		digits[i].setString(char('a' + i));
		digits[i].setFillColor(Color_Black);
		digits[i].setFont(font);
		digits[i].setPosition(Cell_Size * (i + 0.5) - (digits[i].getGlobalBounds().width / 2), Cell_Size * 8 + 5);
		digits[i].setCharacterSize(20);
		digits[i].move(start_of_field);
		window.draw(digits[i]);
	}

	// отрисовка поля
	sf::Texture fieldTexture;
	fieldTexture.loadFromFile("../chess/images/field.png");
	sf::Sprite fieldSprite;
	fieldSprite.setTexture(fieldTexture);
	fieldSprite.setScale(Field_ScaleX, Field_ScaleY);
	fieldSprite.move(start_of_field);
	window.draw(fieldSprite);
}

Board::~Board() {}

Board::Board() {}