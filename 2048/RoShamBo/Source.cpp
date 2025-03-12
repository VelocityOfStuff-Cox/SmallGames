#include <iostream>
#include <string>
#include <random>
/*Ro-Sham-Bo : Rock Paper Scissors
* PC will pick randomely between Ro(Rock), Sham(Scissors), and Bo(paper).
* Player will be able to choose from any of the options.
* Paper beats Rock, Rock beats Scissors, and Scissors beats rock.
* An array keeps the score
*/

struct Player
{

public:
	enum class Options { ro, sham, bo, q, index };

	bool compareChoice(Player& player);
	void takeTextInput();
	void pickRandom();

private:
	Options choice{ Player::Options::index };

};

int score[3]{ 0, 0, 0 };

int main() {
	Player player;
	Player pc;

	std::cout << "Ro! Sham! Bo! \n\t [q to quit]" << std::endl;

	bool quit{ false };
	while (player.compareChoice(pc))
	{
		std::cout << "Ro! Sham! Bo! \n  [q to quit]" 
			<< "\nWin: " << score[0] << "  Loss: " << score[1] << "  Draw: " << score[2] << std::endl;
		player.takeTextInput();
		pc.pickRandom();
	}

}

bool Player::compareChoice(Player& player)
{
	if (choice == Options::q) {
		std::cout << "\033c" << std::endl;
		return false;
	}
	else
	{
		if (choice == Options::ro) {
			if (player.choice == Options::ro) {
				std::cout << "Draw!\n";
				score[2]++;
			}
			else if (player.choice == Options::sham) {
				std::cout << "You Win!\n";
				score[0]++;
			}
			else if (player.choice == Options::bo) {
				std::cout << "You Lose!\n";
				score[1]++;
			}
		}
		else if (choice == Options::sham) {
			if (player.choice == Options::ro) {
				std::cout << "You Lose!\n";
				score[1]++;
			}
			else if (player.choice == Options::sham) {
				std::cout << "Draw!\n";
				score[2]++;
			}
			else if (player.choice == Options::bo) {
				std::cout << "You Win!\n";
				score[0]++;

			}
		}
		else if (choice == Options::bo) {
			if (player.choice == Options::ro) {
				std::cout << "You Win!\n";
				score[0]++;
			}
			else if (player.choice == Options::sham) {
				std::cout << "You Lose!\n";
				score[1]++;
			}
			else if (player.choice == Options::bo) {
				std::cout << "Draw!\n";
				score[2]++;
			}
		}
		std::cin.get();
		std::cin.get();
		std::cout << "\033c" << std::endl;
		return true;
	}
}

void Player::takeTextInput()
{
	std::string input{ "" };
	std::cin >> input;

	if ((input == "Ro") || (input == "ro") || (input == "Rock") || (input == "rock")) {
		choice = Options::ro;
	}
	else if ((input == "Sham") || (input == "sham") || (input == "Scissors") || (input == "scissors")) {
		choice = Options::sham;
	}
	else if ((input == "Bo") || (input == "bo") || (input == "Paper") || (input == "paper")) {
		choice = Options::bo;
	}
	else if ((input == "Q") || (input == "q")) {
		choice = Options::q;
	}
	else {
		// Handle invalid input
		std::cout << "Invalid input! Please enter Rock, Paper, or Scissors." << std::endl;
		this->takeTextInput();
	}

}

void Player::pickRandom()
{
	std::random_device seed;
	std::default_random_engine eng(seed());
	std::uniform_int_distribution<int> randomChoice(0, 2);

	choice = static_cast<Options>(randomChoice(eng));
}
