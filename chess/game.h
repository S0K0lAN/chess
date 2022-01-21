#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>
#include "Board.h"
#include "Figure.h"
#include "header.h"

using namespace sf;

std::string moveToString(Cell initial, Move move) {
    std::string m;
    if (move.type == MoveType::LongCastling) {
        m = "0-0-0";
        return m;
    }
    if (move.type == MoveType::ShortCastling) {
        m = "0-0";
        return m;
    }
    m = char('a' + initial.x);
    m += char('8' - initial.y);
    if (move.type == MoveType::Eat)
        m += " : ";
    else
        m += " - ";
    m += char('a' + move.cell->x);
    m += char('8' - move.cell->y);
    return m;
}

sf::CircleShape getTag() {
    sf::CircleShape tag;
    tag.setFillColor(sf::Color(100, 100, 100, 165));
    tag.setRadius(Tag_Radius);
    tag.move(Tag_Initial_Position);

    return tag;
}

void gamePlay() {
    RenderWindow window(VideoMode(wW, wH), "Chess");
    Image icon;
    icon.loadFromFile("../chess/images/window_icon.png");
    window.setIcon(32, 32, icon.getPixelsPtr());
    window.setFramerateLimit(60);

    Board::fieldInitialization();
    Figure::figuresInitialization();

    Vector2f destination, initialFigurePosition;
    Vector2i mouse_pos;
    Move move;
    std::vector<Move> legalmoves;
    std::string moveDesignation;
    RectangleShape selectedSquare(Vector2f(Cell_Size, Cell_Size));
    selectedSquare.setFillColor(Color(246, 246, 105));
    bool canMove = false, isMove = false, unselect = false, drawTags = false, drawSelectedSquare = false, isBreak = false, isLongCastling = false, isShortCastling = false;
    int currentFigureNumber = -1, moveNumber = 1;
    float distance;
    long int queue = 0; // четное - белые, нечетное - черные
    Cell* selectedCell = &Cell();


    while (window.isOpen())
    {
        mouse_pos = Mouse::getPosition(window);

        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        // отслеживание клика мыши
        if (event.type == Event::MouseButtonPressed) {
            if (event.key.code == Mouse::Left) {
                if ((mouse_pos.x > start_of_field.x && mouse_pos.x < start_of_field.x + Cell_Size * 8) && (mouse_pos.y > start_of_field.y && mouse_pos.y < start_of_field.y + Cell_Size * 8)) {
                    for (int i = 0; i < 8; i++) {
                        for (int j = 0; j < 8; j++) {
                            if (Board::getCell(i, j)->isSelected) {
                                if (Board::getCell(i, j)->getState() != Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->getState()) {
                                    selectedCell = Board::getCell(i, j);
                                    move.cell = Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size);
                                    initialFigurePosition = Figure::figures[currentFigureNumber].getCell()->getSquare().getPosition();
                                    destination = move.cell->getSquare().getPosition();
                                    for (int i = 0; i < legalmoves.size(); i++) {
                                        if (*legalmoves[i].cell == *move.cell) {
                                            canMove = true;
                                            move.type = legalmoves[i].type;
                                        }
                                    }
                                    if (canMove) {
                                        unselect = true;
                                        Figure::figures[currentFigureNumber].move(move);
                                        if (move.type == MoveType::LongCastling)
                                            isLongCastling = true;
                                        if (move.type == MoveType::ShortCastling)
                                            isShortCastling = true;
                                    }
                                }
                                else {
                                    Board::getCell(i, j)->isSelected = false;
                                }
                            }
                        }
                    }
                    if (!Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->isSelected && !canMove) {
                        selectedSquare.setPosition(Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->getSquare().getPosition());
                        drawSelectedSquare = true;
                        if (Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->getPiece() != Type::None) {
                            if (static_cast<State>(queue % 2) == Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->getState()) {
                                Board::getCell((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size)->isSelected = true;
                                drawTags = true;
                                currentFigureNumber = Figure::getFigureIndex((mouse_pos.x - start_of_field.x) / Cell_Size, (mouse_pos.y - start_of_field.y) / Cell_Size);
                                legalmoves = Figure::figures[currentFigureNumber].getLegalMoves();
                            }
                        }
                    }
                    if (unselect)
                        selectedCell->isSelected = false;
                }
            }
        }
        // анимация передвижения
        if (canMove) {
            distance = sqrt(pow(destination.x - Figure::figures[currentFigureNumber].sprite.getPosition().x, 2) + pow(destination.y - Figure::figures[currentFigureNumber].sprite.getPosition().y, 2));
            if (isShortCastling) {
                if (queue % 2) {
                    Figure::getFigure(5, 0)->sprite.setPosition(Board::getCell(5, 0)->getSquare().getPosition());
                }
                else {
                    Figure::getFigure(5, 7)->sprite.setPosition(Board::getCell(5, 7)->getSquare().getPosition());
                }
            }
            if (isLongCastling) {
                if (queue % 2) {
                    Figure::getFigure(3, 0)->sprite.setPosition(Board::getCell(3, 0)->getSquare().getPosition());
                }
                else {
                    Figure::getFigure(3, 7)->sprite.setPosition(Board::getCell(3, 7)->getSquare().getPosition());
                }
            }
            if (distance > 1) {
                Figure::figures[currentFigureNumber].sprite.move((destination.x - initialFigurePosition.x) / 5, (destination.y - initialFigurePosition.y) / 5);
                isMove = true;
            }
            else {
                isMove = false;
                canMove = false;
                drawTags = false;
                drawSelectedSquare = false;
                isShortCastling = false;
                isLongCastling = false;
                unselect = false;
                if (queue % 2) {
                    moveDesignation += "    " + moveToString(*selectedCell, move);
                    std::cout << moveDesignation << std::endl;
                    moveDesignation = "";
                }
                else {
                    moveDesignation = std::to_string(moveNumber) + ". " + moveToString(*selectedCell, move);
                    moveNumber++;
                }
                queue++;
            }
        }

        // метки для клеток, на которые фигура может походить
        std::vector<CircleShape> tags(legalmoves.size(), getTag());
        for (int i = 0; i < tags.size(); i++) {
            tags[i].move(legalmoves[i].cell->getSquare().getPosition());
        }

        // отрисовка
        window.clear(Window_Color);
        Board::draw(window);
        if (drawSelectedSquare)
            window.draw(selectedSquare);
        Figure::draw(window);
        if (drawTags && !isMove) {
            for (int i = 0; i < tags.size(); i++)
                window.draw(tags[i]);
        }
        window.display();
    }
}