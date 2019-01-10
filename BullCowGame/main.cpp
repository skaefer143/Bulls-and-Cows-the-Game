/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#include <iostream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game

int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	// end line, end of game
	std::cout << std::endl;
	return 0;
}

void PrintIntro() {
	// introduce the game
	std::cout << "\nWelcome to Bulls and Cows, a word game made by Storm as a C++ "
		"tutorial/refresher.\n";
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking "
		"of?\n\n";

	return;
}

void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();
 
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries){
		FText guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << " and Cows =  " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

// loop continually until the user gives a valid guess
FText GetValidGuess() {
	FText guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 TryNum = BCGame.GetCurrentTry();
		std::cout << "Try " << TryNum << ". Please enter in your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter in an isogram. An Isogram has no repeating characters. \n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter in a fully lowercase word. \n";
			break;
		default:
			// assume the guess is valid.
			break;
		}
		std::cout << std::endl;
	} while (Status != EGuessStatus::OK);
	
	return guess;

}

bool AskToPlayAgain() {
	std::cout << "Do you want to play again with the same hidden word? (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);
	
	return (tolower(Response[0]) == 'y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "You won! Congratulations." << std::endl;
	}
	else {
		std::cout << "You lost. Better luck next time." << std::endl;
	}
}
