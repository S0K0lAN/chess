#pragma once
#include <SFML/Graphics.hpp>

enum class MoveType {
	Move, Eat, LongCastling, ShortCastling
};

enum class State {
	White, Black, Free
};

enum class Type {
	King, Queen, Rook, Bishop, Knight, Pawn, None
};

constexpr float wW = 1920;

constexpr float wH = 1080;

constexpr float Cell_Size = 100;

constexpr float Tag_Radius = 12.5;

constexpr float Figures_ScaleX = Cell_Size / 150;

constexpr float Figures_ScaleY = Cell_Size / 150;

constexpr float Field_ScaleX = 8 * Cell_Size / 1200;

constexpr float Field_ScaleY = 8 * Cell_Size / 1200;

//#define Color_Black sf::Color(115, 62, 31)
//
//#define Color_White sf::Color(204, 169, 119)

#define Color_Black sf::Color(122, 88, 62)

#define Color_White sf::Color(197, 171, 138)

//#define Color_White sf::Color(238, 238, 210)
//
//#define Color_Black sf::Color(118, 150, 86)

#define Window_Color sf::Color(49, 46, 43)


const sf::Vector2f Tag_Initial_Position = sf::Vector2f((Cell_Size - 2 * Tag_Radius) / 2, (Cell_Size - 2 * Tag_Radius) / 2);

const sf::Vector2f start_of_field = sf::Vector2f((wW - 8 * Cell_Size) / 2, (wH - 8 * Cell_Size) / 2);