#pragma once
#include <SFML/Graphics.hpp>
#include "prefs.h"


class Minesweeper {
public:
	Minesweeper();
	void openCell(sf::Vector2i);
	void flag(sf::Vector2i);
	std::vector<sf::Sprite> updateCells(sf::Texture&);

	char gameState();

private:
	bool mines[SIZE][SIZE] {};
	char numbers[SIZE][SIZE] {};
	char cells[SIZE][SIZE] {};
	char state = 0;
	bool isWin();
};