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
*     ~     The rules are that on each turn the player must choose a direction   (up, down, left or right).
*     ~     All tiles move as far as possible in that direction, some move more than others.
*     ~     Two adjacent tiles (in that direction only) with matching numbers combine into one bearing the sum of those numbers.
*     ~     A move is valid when at least one tile can be moved, including by combination.
*     -      A new tile is spawned at the end of each turn at a randomly chosen empty square   (if there is one).
*     -      Most of the time, a new 2 is to be added, but occasionally (10% of the time), a 4.
*          To win, the player must create a tile with the number 2048.
*          The player loses if no valid moves are possible.
*/

const int boardSize{ 8 };

struct Tile
{
	std::string shape{ "" };
	int value{ 0 };
	bool merged{ false };
};
struct IntPair
{
	int x{ 0 };
	int y{ 0 };
};
enum class direction{up, down, left, right, null};

void shapeGenerator(Tile& tile);
void possitionPicker(std::array<std::array<Tile, boardSize>, boardSize> &gameBoard);
direction move(std::string input);
bool moveChecker(direction move, std::array <std::array <Tile, boardSize>, boardSize>& gameBoard);

int main() {
	
	std::array<std::array<Tile, boardSize>, boardSize> gameBoard;

	for (int i{ 0 }; i < boardSize; i++) {
		for (int k{ 0 }; k < boardSize; k++) {
			gameBoard.at(i).at(k) = { "[ ]", 0, false };
		}
	}

	bool gameEnd{ false };

	while (!gameEnd) {
		for (const auto row : gameBoard) {
			for (const auto cell : row) {
				std::cout << cell.shape;
			}
			std::cout << "\n";
		}
		
		std::cout << "W/w: up, S/s: down, A/a: left, D/d: right" << std::endl;
		std::string input{ "" };
		std::getline(std::cin, input);

		moveChecker(move(input), gameBoard);
	//	possitionPicker(gameBoard);

		std::array<IntPair, boardSize * boardSize> freeCells;
		int freeIndex{ 0 };

		for (int i{ 0 }; i < freeCells.size(); i++) {
			freeCells.at(i) = {0, 0};
		}

		for (int i{ 0 }; i < boardSize; i++) {
			for (int k{ 0 }; k < boardSize; k++) {
				if (gameBoard.at(i).at(k).value == 0) {
					freeCells.at(freeIndex).y = i;
					freeCells.at(freeIndex).x = k;
					freeIndex++;
				}
			}
		}

		std::random_device rd;
		std::default_random_engine dre(rd());
		std::uniform_int_distribution<int> uid(1, freeIndex);

		IntPair choice{ freeCells.at(freeIndex) };
		shapeGenerator(gameBoard.at(choice.x).at(choice.y));
	}	
}

void shapeGenerator(Tile& tile) {
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::bernoulli_distribution bd(0.9);

	if (bd(dre)) {
		tile = { "[2]", 2, false };
	} else {
		tile = { "[4]", 4, false };
	}
}

void possitionPicker(std::array<std::array<Tile, boardSize>, boardSize>& gameBoard)
{
	std::array<IntPair, boardSize ^ 2> freeCells;
	int freeIndex{ 0 };
	
	for (auto freeCell : freeCells) {
		freeCell = { 0, 0 };
	}

	for (int i{ 0 }; i < boardSize; i++) {
		for (int k{ 0 }; k < boardSize; k++) {
			if (gameBoard.at(i).at(k).value == 0) {
				freeCells.at(freeIndex).y = i;
				freeCells.at(freeIndex).x = k;
				freeIndex++;
			}
		}
	}
	
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> uid(1, freeIndex);
	
	IntPair choice{ freeCells.at(freeIndex) };
	shapeGenerator(gameBoard.at(choice.x).at(choice.y));
	
}

direction move(std::string input)
{
	if ("w" || "W") {
		return direction::up;
	}
	else if("s" || "S") {
		return direction::down;
	}	
	else if ("a" || "A") {
		return direction::left;
	}
	else if ("d" || "D") {
		return direction::right;
	}
	else {
		return direction::null;
	}

}

bool moveChecker(direction move, std::array<std::array<Tile, boardSize>, boardSize>& gameBoard)
{
	switch (move)
	{
	case direction::up:
		for (int i{ 0 }; i < boardSize; i++) {
			for (int k{ 0 }; k < boardSize; k++) {
				if (i > 0 && gameBoard.at(i).at(k).value != 0) {

					int moveEdge{ 0 };

					for (int j{ i }; j >= 0; j--) {
						if (gameBoard.at(j).at(k).value == 0) {
							continue;
						}
						else if (j == 0 || gameBoard.at(i).at(k).value == gameBoard.at(j).at(k).value) {
							moveEdge = j;
							goto moveCombineA;
						}
					}

					moveCombineA:
					if (gameBoard.at(i).at(k).value == gameBoard.at(moveEdge).at(k).value && !gameBoard.at(moveEdge).at(k).merged) {

						gameBoard.at(moveEdge).at(k).value += gameBoard.at(i).at(k).value;

						gameBoard.at(moveEdge).at(k).shape = "[" + std::to_string(gameBoard.at(moveEdge).at(k).value) + "]";

						gameBoard.at(i).at(k).value = 0; 
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false; 
						
						gameBoard.at(moveEdge).at(k).merged = true;
					}
					else if (gameBoard.at(moveEdge).at(k).value = 0) {
						
						gameBoard.at(moveEdge).at(k) = gameBoard.at(i).at(k);

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;
					}
					else {
						continue;
					}
				}
			}
		}
		return true;
		break;
	case direction::down:
		for (int i{ boardSize }; i >= 0; i--) {
			for (int k{ 0 }; k < boardSize; k++) {
				if (i < boardSize && gameBoard.at(i).at(k).value != 0) {

					int moveEdge{ 0 };

					for (int j{ i }; j < boardSize; j++) {
						if (gameBoard.at(j).at(k).value == 0) {
							continue;
						}
						else if (j == 0 || gameBoard.at(i).at(k).value == gameBoard.at(j).at(k).value) {
							moveEdge = j;
							goto moveCombineB;
						}
					}

				moveCombineB:
					if (gameBoard.at(i).at(k).value == gameBoard.at(moveEdge).at(k).value && !gameBoard.at(moveEdge).at(k).merged) {

						gameBoard.at(moveEdge).at(k).value += gameBoard.at(i).at(k).value;

						gameBoard.at(moveEdge).at(k).shape = "[" + std::to_string(gameBoard.at(moveEdge).at(k).value) + "]";

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;

						gameBoard.at(moveEdge).at(k).merged = true;
					}
					else if (gameBoard.at(moveEdge).at(k).value = 0) {

						gameBoard.at(moveEdge).at(k) = gameBoard.at(i).at(k);

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;
					}
					else {
						continue;
					}
				}
			}
		}
		return true;
		break;
	case direction::left:
		for (int i{ 0 }; i < boardSize; i++) {
			for (int k{ 0 }; k < boardSize; k++) {
				if (i > 0 && gameBoard.at(i).at(k).value != 0) {

					int moveEdge{ 0 };

					for (int j{ k }; j >= 0; j--) {
						if (gameBoard.at(j).at(k).value == 0) {
							continue;
						}
						else if (j == 0 || gameBoard.at(i).at(k).value == gameBoard.at(j).at(k).value) {
							moveEdge = j;
							goto moveCombineC;
						}
					}

				moveCombineC:
					if (gameBoard.at(i).at(k).value == gameBoard.at(moveEdge).at(k).value && !gameBoard.at(moveEdge).at(k).merged) {

						gameBoard.at(moveEdge).at(k).value += gameBoard.at(i).at(k).value;

						gameBoard.at(moveEdge).at(k).shape = "[" + std::to_string(gameBoard.at(moveEdge).at(k).value) + "]";

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;

						gameBoard.at(moveEdge).at(k).merged = true;
					}
					else if (gameBoard.at(moveEdge).at(k).value = 0) {

						gameBoard.at(moveEdge).at(k) = gameBoard.at(i).at(k);

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;
					}
					else {
						continue;
					}
				}
			}
		}
		return true;
		break;
	case direction::right:
		for (int i{ 0 }; i < boardSize; i++) {
			for (int k{ boardSize }; k >= 0; k--) {
				if (i > 0 && gameBoard.at(i).at(k).value != 0) {

					int moveEdge{ 0 };

					for (int j{ k }; j < boardSize; j++) {
						if (gameBoard.at(j).at(k).value == 0) {
							continue;
						}
						else if (j == 0 || gameBoard.at(i).at(k).value == gameBoard.at(j).at(k).value) {
							moveEdge = j;
							goto moveCombineD;
						}
					}

				moveCombineD:
					if (gameBoard.at(i).at(k).value == gameBoard.at(moveEdge).at(k).value && !gameBoard.at(moveEdge).at(k).merged) {

						gameBoard.at(moveEdge).at(k).value += gameBoard.at(i).at(k).value;

						gameBoard.at(moveEdge).at(k).shape = "[" + std::to_string(gameBoard.at(moveEdge).at(k).value) + "]";

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;

						gameBoard.at(moveEdge).at(k).merged = true;
					}
					else if (gameBoard.at(moveEdge).at(k).value = 0) {

						gameBoard.at(moveEdge).at(k) = gameBoard.at(i).at(k);

						gameBoard.at(i).at(k).value = 0;
						gameBoard.at(i).at(k).shape = "";
						gameBoard.at(i).at(k).merged = false;
					}
					else {
						continue;
					}
				}
			}
		}
		return true;
		break;
	case direction::null: default:
		return false;
	}
	
}
