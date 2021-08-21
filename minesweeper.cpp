#include "minesweeper.h"

Minesweeper::Minesweeper() {
	//random spawn of mines
	for (short i = 0; i < N; ++i) {
		short a, b;

		do a = rand() % SIZE, b  = rand() % SIZE;
		while (mines[a][b] != 0);

		mines[a][b] = 1;
	}

	//count of mines around cells
	for (short i = 0; i < SIZE; ++i)
		for (short j = 0; j < SIZE; ++j)
			for (char x = -1; x <= 1; ++x)
				for (char y = -1; y <= 1; ++y)
					if (i + x >= 0 && i + x < SIZE && j + y >= 0 && j + y < SIZE)
						numbers[i][j] += mines[i + x][j + y];

	//close all cells
	std::vector<sf::Sprite> cellsSprites;

	for (short i = 0; i < SIZE; ++i)
		for (short j = 0; j < SIZE; ++j)
			cells[i][j] = 10;
}

void Minesweeper::openCell(sf::Vector2i c) {
	if (cells[c.x][c.y] != 10) return;

	if (mines[c.x][c.y]) {
		for (short i = 0; i < SIZE; ++i)
			for (short j = 0; j < SIZE; ++j)
				cells[i][j] = mines[i][j] ? 9 : cells[i][j],
				state = -1;
	}
	else {
		cells[c.x][c.y] = numbers[c.x][c.y];

		bool opened[SIZE][SIZE] {};

		for (short i = 0; i < SIZE; ++i)
			for (short j = 0; j < SIZE; ++j) {
				if (cells[i][j] == 0 && !opened[i][j]) {
					opened[i][j] = 1;

					for (char x = -1; x <= 1; ++x)
						for (char y = -1; y <= 1; ++y)
							if (i + x >= 0 && i + x < SIZE && j + y >= 0 && j + y < SIZE)
								cells[i + x][j + y] = numbers[i + x][j + y];

					i = 0, j = 0;
				}


		}

		state = isWin();
	}
}

void Minesweeper::flag(sf::Vector2i c) {
	if (cells[c.x][c.y] == 10) cells[c.x][c.y] = 11;
	else if (cells[c.x][c.y] == 11) cells[c.x][c.y] = 10;
}

std::vector<sf::Sprite> Minesweeper::updateCells(sf::Texture& t) {
	std::vector<sf::Sprite>  cellsSprites;

	for (short i = 0; i < SIZE; ++i)
		for (short j = 0; j < SIZE; ++j) {
			sf::Sprite s (t);
			s.setTextureRect(sf::IntRect(32 * (int)cells[i][j], 0, 32, 32));
			s.setPosition(i * CELL, j * CELL);
			cellsSprites.push_back(s);
		}

	return cellsSprites;
}

char Minesweeper::gameState() {
	return state;
}

bool Minesweeper::isWin() {
	for (int i = 0; i < SIZE; ++i)
		for (int j = 0; j < SIZE; ++j)
			if (!mines[i][j] && cells[i][j] == 10)
				return 0;

	return 1;
}