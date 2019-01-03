#include <iostream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

void PrintIntro();
void PlayGame();
std::string GetGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main() {
	PrintIntro();

	bool bPlayAgain = false;
	do {
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	// end line, end of game
	std::cout << std::endl;
	return 0;
}

void PrintIntro() {
	constexpr int WORD_LENGTH = 6;

	// introduce the game
	std::cout << "Welcome to Bulls and Cows, a word game made by storm as a C++ "
		"tutorial/refresher.\n";
	std::cout << "Can you guess the " << WORD_LENGTH << " letter isogram I'm thinking "
		"of?\n";

	return;
}

void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	// TODO change from FOR to WHILE loop once we are validating tries
	for (int count = 0; count < MaxTries; count++) {
		std::string guess = GetGuess(); // TODO make check for valid guesses

		// Submit valid guess to the game
		// Print number of bulls and cows

		std::cout << "Your guess was " << guess << std::endl;
		std::cout << std::endl;
	}

	// TODO summarize game
}

std::string GetGuess() {
	// get a guess from the player
	int TryNum = BCGame.GetCurrentTry();
	std::cout << "Try " << TryNum << ". Please enter in your guess: ";
	std::string guess = "";
	std::getline(std::cin, guess);
	
	return guess;
}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again (y/n)? ";
	std::string Response = "";
	std::getline(std::cin, Response);
	
	return (tolower(Response[0]) == 'y');
}
