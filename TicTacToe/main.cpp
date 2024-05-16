
#include <iostream>
#include <array>
#include "include/SFML/Graphics.hpp"


void print_board(std::array<std::array<char, 3>, 3>* pGrid) {
	auto grid = *pGrid;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
}

int main() {
	// initialize empty row template
	std::array<char, 3> row = { 'x', 'x', 'x' };

	// initialize and populate grid with rows
	std::array<std::array<char, 3>, 3> grid = { row, row, row };

	// print starting board
	std::cout << "Starting board:" << std::endl;
	print_board(&grid);

	int window_width = 500;
	int window_height = 500;

	// initialize a SFML window
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tic Tac Toe");

	// initialize grid lines for board
	sf::RectangleShape vertical_line1;
	vertical_line1.setSize(sf::Vector2f(window_width / 100, window_height));
	vertical_line1.setPosition(sf::Vector2f(window_width / 3, 0));

	sf::RectangleShape vertical_line2;
	vertical_line2.setSize(sf::Vector2f(window_width / 100, window_height));
	vertical_line2.setPosition(sf::Vector2f(window_width - window_width / 3, 0));

	sf::RectangleShape horizontal_line1;
	horizontal_line1.setSize(sf::Vector2f(window_width, window_height / 100));
	horizontal_line1.setPosition(sf::Vector2f(0, window_height / 3));

	sf::RectangleShape horizontal_line2;
	horizontal_line2.setSize(sf::Vector2f(window_width, window_height / 100));
	horizontal_line2.setPosition(sf::Vector2f(0, window_height - window_height / 3));

	// runtime loop
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		// clear the display window, render objects
		window.clear();

		window.draw(vertical_line1);
		window.draw(vertical_line2);

		window.draw(horizontal_line1);
		window.draw(horizontal_line2);

		window.display();
	}

	return 0;
}
