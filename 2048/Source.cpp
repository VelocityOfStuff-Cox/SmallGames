#include <iostream>
#include <random>
#include <array>
#include <string>

/*
* Task
*  Implement a 2D sliding block puzzle game where blocks with numbers are combined to add their values.
*
*  Rules of the game
*
*          The rules are that on each turn the player must choose a direction   (up, down, left or right).
*          All tiles move as far as possible in that direction, some move more than others.
*          Two adjacent tiles (in that direction only) with matching numbers combine into one bearing the sum of those numbers.
*          A move is valid when at least one tile can be moved, including by combination.
*     -      A new tile is spawned at the end of each turn at a randomly chosen empty square   (if there is one).
*     -      Most of the time, a new 2 is to be added, but occasionally (10% of the time), a 4.
*          To win, the player must create a tile with the number 2048.
*          The player loses if no valid moves are possible.
*/

const int boardSize{ 8 };

struct Tile
{
	std::string shape{ "" };
};
struct IntPair
{
	int x{ 0 };
	int y{ 0 };
};
enum class direction{up, down, left, right, null};

void shapeGenerator(Tile& tile);
void possitionPicker(std::array <std::array <Tile, boardSize>, boardSize> &gameBoard);
direction move(char input);

int main() {
	
	std::array<std::array<Tile, boardSize>, boardSize> gameBoard;

	bool gameEnd{ false };

	while (!gameEnd) {
		for (const auto row : gameBoard) {
			for (const auto cell : row) {
				std::cout << cell.shape;
			}
		}
		
		std::cout << "W/w: up, S/s: down, A/a: left, D/d: right" << std::endl;
		std::string input{ "" };
		std::cin >> input;

		move(input.at(0));
		possitionPicker(gameBoard);
	}
	
}

void shapeGenerator(Tile& tile) {
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::bernoulli_distribution bd(0.9);

	if (bd(dre)) {
		tile.shape = "[2]";
	} else {
		tile.shape = "[4]";
	}
}

void possitionPicker(std::array<std::array<Tile, boardSize>, boardSize>& gameBoard)
{
	std::array<IntPair, boardSize ^ 2> freeCells;
	int freeIndex{ 0 };

	for (int i{ 0 }; i < boardSize; i++) {
		for (int k{ 0 }; k < boardSize; k++) {
			if (gameBoard.at(i).at(k).shape == "") {
				freeCells.at(freeIndex).y = i;
				freeCells.at(freeIndex).x = k;
				freeIndex++;
			}
		}
	}
	
	std::random_device rd;
	std::default_random_engine dre(rd);
	std::uniform_int_distribution<int> uid(1, freeIndex);
	
	IntPair choice{ freeCells.at(freeIndex) };
	shapeGenerator(gameBoard.at(choice.x).at(choice.y));
	
}

direction move(char input)
{
	switch (input)
	{
	case 'w': case 'W':
		return direction::up;
	case 's': case 'S':
		return direction::down;
	case 'a': case 'A':
		return direction::left;
	case 'd': case 'D':
		return direction::right;
	default:
		return direction::null;
	}

	return direction();
}
