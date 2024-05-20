
/// TODO: refactor the damn main function please it's killing me

#include <iostream>
#include <array>
#include <vector>
#include <cmath>
#include "include/SFML/Graphics.hpp"

const int WINDOW_WIDTH = 500;
const int WINDOW_HEIGHT = 500;
const int BOX_SIDE_LENGTH = WINDOW_WIDTH / 5;
const int BOARD_SIZE = 3;

// prints the board state to the output console
static void print_board(char grid[BOARD_SIZE][BOARD_SIZE]) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			std::cout << grid[i][j];
		}

		std::cout << std::endl;
	}
}

// some dumbass function to check if someone won or not
char check_win(char grid[BOARD_SIZE][BOARD_SIZE]) {
	// check rows and columns
	for (int i = 0; i < BOARD_SIZE; ++i) {
		if (grid[i][0] != ' ' && grid[i][0] == grid[i][1] && grid[i][1] == grid[i][2])
			return grid[i][0];
		if (grid[0][i] != ' ' && grid[0][i] == grid[1][i] && grid[1][i] == grid[2][i])
			return grid[0][i];
	}

	// check diagonals
	if (grid[0][0] != ' ' && grid[0][0] == grid[1][1] && grid[1][1] == grid[2][2])
		return grid[0][0];
	if (grid[0][2] != ' ' && grid[0][2] == grid[1][1] && grid[1][1] == grid[2][0])
		return grid[0][2];

	// check for possible future moves
	for (int row = 0; row < BOARD_SIZE; row++) {
		for (int col = 0; col < BOARD_SIZE; col++) {
			if (grid[row][col] == ' ') {
				return ' ';
			}
		}
	}

	// if not returned earlier, board must be full, return as NO_POSSIBLE_MOVE
	return 'N';
}

static std::array<sf::Vector2i, 2> check_click(sf::Vector2i click_boxes[BOARD_SIZE][BOARD_SIZE][2], sf::RenderWindow *window) {
	// get mouse position relative to the window
	sf::Vector2i mouse_position = sf::Mouse::getPosition(*window);

	// declare container for clicked cell coordinates
	sf::Vector2i clicked_cell;

	// boolean for breaking parent loop
	bool found_box = false;

	// declare and initialize positional modifier values
	int mod_x;
	int mod_y = 1;
	sf::Vector2i mods;

	// loop through every grid cell, compare mouse position with cell boundaries
	for (int row = 0; row < BOARD_SIZE; row++) {
		mod_x = 1;
		for (int col = 0; col < BOARD_SIZE; col++) {
			// declare and initialize two points for quick reference
			sf::Vector2i top_left = click_boxes[row][col][0];
			sf::Vector2i bottom_right = click_boxes[row][col][1];

			// check if mouse position is between these two points
			if (mouse_position.x >= top_left.x && mouse_position.x <= bottom_right.x 
					&& mouse_position.y >= top_left.y && mouse_position.y <= bottom_right.y) {
				clicked_cell = sf::Vector2i(col, row);
				found_box = true;
				break;
			}

			mod_x += 2;
		}

		if (found_box)
			break;

		mod_y += 2;
	}

	mods = sf::Vector2i(mod_x, mod_y);
	
	std::array<sf::Vector2i, 2> cell_and_mods = { clicked_cell, mods };

	return cell_and_mods;
}

static bool is_empty_cell(char grid[BOARD_SIZE][BOARD_SIZE], sf::Vector2i clicked_cell) {
	if (grid[clicked_cell.y][clicked_cell.x] != ' ') {
		std::cout << "Box @ (" << clicked_cell.x << ", " << clicked_cell.y << ") is not empty!" << std::endl;
		return false;
	}

	return true;
}

static void place_box(std::vector<sf::RectangleShape> &boxes, char grid[BOARD_SIZE][BOARD_SIZE], sf::Vector2f position, sf::Vector2i clicked_cell) {
	sf::RectangleShape box = sf::RectangleShape(sf::Vector2f(BOX_SIDE_LENGTH, BOX_SIDE_LENGTH));
	box.setPosition(position);
	boxes.push_back(box);

	grid[clicked_cell.y][clicked_cell.x] = 'X';
}

static void place_circle(std::vector<sf::CircleShape> &circles, char grid[BOARD_SIZE][BOARD_SIZE], sf::Vector2f position, sf::Vector2i clicked_cell) {
	sf::CircleShape circle = sf::CircleShape(BOX_SIDE_LENGTH / 2.0);
	circle.setPosition(position);
	circles.push_back(circle);

	grid[clicked_cell.y][clicked_cell.x] = 'O';
}

static sf::RectangleShape make_line(sf::Vector2f dimensions, sf::Vector2f position) {
	sf::RectangleShape rect;
	rect.setSize(dimensions);
	rect.setPosition(position);

	return rect;
}

int main() {
	// declare and initialize grid with rows
	char grid[BOARD_SIZE][BOARD_SIZE] = 
					  { {' ', ' ', ' '},
						{' ', ' ', ' '},
						{' ', ' ', ' '} };

	// declare vectors to hold the circles and boxes to be drawn each frame. 
	std::vector<sf::RectangleShape> boxes;
	std::vector<sf::CircleShape> circles;

	// Calculate the size of each cell
	int cellSizeX = WINDOW_WIDTH / BOARD_SIZE;
	int cellSizeY = WINDOW_WIDTH / BOARD_SIZE;

	sf::Vector2i click_boxes[BOARD_SIZE][BOARD_SIZE][2];

	for (int i = 0; i < BOARD_SIZE; ++i) {
		for (int j = 0; j < BOARD_SIZE; ++j) {
			click_boxes[i][j][0] = sf::Vector2i(j * cellSizeX, i * cellSizeY); // Top left corner
			click_boxes[i][j][1] = sf::Vector2i((j + 1) * cellSizeX, (i + 1) * cellSizeY); // Bottom right corner

			std::cout << click_boxes[i][j][0].x << " " << click_boxes[i][j][0].y << std::endl;
			std::cout << click_boxes[i][j][1].x << " " << click_boxes[i][j][1].y << std::endl;
			std::cout << std::endl;
		}
	}

	// print starting board
	std::cout << "Starting board:" << std::endl;
	print_board(grid);

	// initialize a SFML window
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tic Tac Toe");

	// initialize grid lines for board
	sf::RectangleShape vertical_line1 = make_line(sf::Vector2f(WINDOW_WIDTH / 100, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH / BOARD_SIZE, 0));
	sf::RectangleShape vertical_line2 = make_line(sf::Vector2f(WINDOW_WIDTH / 100, WINDOW_HEIGHT), sf::Vector2f(WINDOW_WIDTH - WINDOW_WIDTH / BOARD_SIZE, 0));
	sf::RectangleShape horizontal_line1 = make_line(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 100), sf::Vector2f(0, WINDOW_HEIGHT / BOARD_SIZE));
	sf::RectangleShape horizontal_line2 = make_line(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 100), sf::Vector2f(0, WINDOW_HEIGHT - WINDOW_HEIGHT / BOARD_SIZE));

	// boolean value to keep track of whether or not the user has released the left mouse button
	bool ready_to_click = true;

	bool box_turn = true;

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

		// draw calls for any circles and boxes that are present in the game
		for (int index = 0; index < boxes.size(); index++) {
			window.draw(boxes.at(index));
		}

		for (int index = 0; index < circles.size(); index++) {
			window.draw(circles.at(index));
		}

		// check if button just pressed, call check_click to check the click location
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && ready_to_click) {
			std::array<sf::Vector2i, 2> cell_and_mods = check_click(click_boxes, &window);

			double mod_x = cell_and_mods[1].x;
			double mod_y = cell_and_mods[1].y;

			sf::Vector2i clicked_cell = cell_and_mods[0];

			if (is_empty_cell(grid, clicked_cell)) {
				sf::Vector2f position = sf::Vector2f(WINDOW_WIDTH * (mod_x / 6.0) - BOX_SIDE_LENGTH / 2.0, WINDOW_WIDTH * (mod_y / 6.0) - BOX_SIDE_LENGTH / 2.0);

				if (box_turn) {
					place_box(boxes, grid, position, clicked_cell);
				}

				else {
					place_circle(circles, grid, position, clicked_cell);
				}

				char result = check_win(grid);
				
				if (result == 'X') {
					std::cout << "Player 1 wins!";
					return 0;
				}
				else if (result == 'O') {
					std::cout << "Player 2 wins!";
					return 0;
				}
				else if (result == 'N') {
					std::cout << "No possible moves! No winner.";
					return 0;
				}

				box_turn = !box_turn;
			}

			ready_to_click = false;
		}

		else if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && !ready_to_click) {
			ready_to_click = true;
		}

		window.display();
	}

	return 0;
}