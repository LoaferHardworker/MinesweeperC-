#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include "minesweeper.h"
#include "prefs.h"
#include "tiles.h"
#include "font.h"

int main() {
	srand(time(0));

	sf::Texture t; t.loadFromMemory(&tiles_jpg, tiles_jpg_len);
	sf::Font font; font.loadFromMemory(&font_ttf, font_ttf_len);
	sf::Text text (L"", font, CELL * 1.5);
	text.setFillColor(sf::Color(170, 30, 50));

	Minesweeper game;
	std::vector<sf::Sprite> cellsSprites = game.updateCells(t);

	//window
	sf::RenderWindow window(sf::VideoMode(SIZE * CELL, SIZE * CELL), L"Minesweeper");
	window.setFramerateLimit(15);

	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (game.gameState()) {
					game = Minesweeper();
					text.setString("");
				}
				else {
					sf::Vector2i c = sf::Mouse::getPosition(window) / CELL;

					if (event.key.code == sf::Mouse::Left) game.openCell(c);
					if (event.key.code == sf::Mouse::Right) game.flag(c);

					char state = game.gameState();
					if (state == 1) {
						text.setString(L"Win!");
						text.setFillColor(sf::Color::Black);
					}
					if (state == -1) {
						text.setString(L"Lose!");
						text.setFillColor(sf::Color(170, 30, 50));
					}
				}

				cellsSprites = game.updateCells(t);
			}
		}

		window.clear();

		for (short i = 0; i < cellsSprites.size(); ++i)
			window.draw(cellsSprites[i]);
		window.draw(text);

		window.display();
	}
}
