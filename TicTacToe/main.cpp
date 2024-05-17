
#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "include/SFML/Graphics.hpp"

static int window_width = 500;
static int window_height = 500;
static int box_side_length = window_width / 5;

// prints the board state to the output console
void print_board(std::array<std::array<char, 3>, 3>* pGrid) {
	auto grid = *pGrid;
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			std::cout << grid[i][j];
		}
		std::cout << std::endl;
	}
}

void make_box() {

}

void make_circle() {

}

void check_click(std::array<std::array<std::array<sf::Vector2i) {

}

sf::RectangleShape make_line(sf::Vector2f dimensions, sf::Vector2f position) {
	sf::RectangleShape rect;
	rect.setSize(dimensions);
	rect.setPosition(position);

	return rect;
}

int main() {
	// initialize empty row template
	std::array<char, 3> row = { 'x', 'x', 'x' };

	// declare and initialize grid with rows
	std::array<std::array<char, 3>, 3> grid = { row, row, row };

	// declare vectors to hold the circles and boxes to be drawn each frame. 
	std::vector<sf::RectangleShape> boxes;
	std::vector<sf::CircleShape> circles;

	// Calculate the size of each cell
	int cellSizeX = window_width / 3;
	int cellSizeY = window_width / 3;

	std::array<std::array<std::array<sf::Vector2i, 2>, 3>, 3> click_boxes;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			click_boxes[i][j][0] = sf::Vector2i(j * cellSizeX, i * cellSizeY); // Top left corner
			click_boxes[i][j][1] = sf::Vector2i((j + 1) * cellSizeX, (i + 1) * cellSizeY); // Bottom right corner

			std::cout << click_boxes[i][j][0].x << " " << click_boxes[i][j][0].y << std::endl;
			std::cout << click_boxes[i][j][1].x << " " << click_boxes[i][j][1].y << std::endl;
			std::cout << std::endl;
		}
	}

	// print starting board
	std::cout << "Starting board:" << std::endl;
	print_board(&grid);

	// initialize a SFML window
	sf::RenderWindow window(sf::VideoMode(window_width, window_height), "Tic Tac Toe");

	// initialize grid lines for board
	sf::RectangleShape vertical_line1 = make_line(sf::Vector2f(window_width / 100, window_height), sf::Vector2f(window_width / 3, 0));
	sf::RectangleShape vertical_line2 = make_line(sf::Vector2f(window_width / 100, window_height), sf::Vector2f(window_width - window_width / 3, 0));
	sf::RectangleShape horizontal_line1 = make_line(sf::Vector2f(window_width, window_height / 100), sf::Vector2f(0, window_height / 3));
	sf::RectangleShape horizontal_line2 = make_line(sf::Vector2f(window_width, window_height / 100), sf::Vector2f(0, window_height - window_height / 3));

	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(box_side_length, box_side_length));
	box.setPosition(window_width * (5.0/6.0) - box_side_length / 2, window_width * 0.07);
	boxes.push_back(box);

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

		//window.draw(cross);

		// draw calls for any circles and boxes that are present in the game
		for (int index = 0; index < boxes.size(); index++) {
			window.draw(boxes.at(index));
		}

		for (int index = 0; index < circles.size(); index++) {
			window.draw(circles.at(index));
		}

		check_click();

		window.display();
	}

	return 0;
}
