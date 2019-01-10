/* This is the console executable, that makes use of the BullCow class.
This acts as the view in a MVC pattern, and is responsible for all 
user interaction. For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include "FBullCowGame.h"

// To make syntax Unreal Engine friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintAsciiArtFromFile();
void PrintIntro();
void PlayGame();
void PrintGameSummary();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; // instantiate a new game, which we re-use across plays

int main() {
	bool bPlayAgain = false;
	do {
		PrintIntro();
		PlayGame();
		bPlayAgain = AskToPlayAgain();
	} while (bPlayAgain);

	std::cout << std::endl;
	return 0;
}

void PrintIntro() {
	std::cout << "\nWelcome to Bulls and Cows: The Game, a word game made by Storm as a C++ "
		"tutorial/refresher.\n";
	PrintAsciiArtFromFile();
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking "
		"of?\n\n";

	return;
}

void PlayGame() {
	/* Plays a single game to completion. */

	BCGame.Reset();
 
	// loop asking for guesses while the game is NOT won
	// and there are still tries remaining.
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= BCGame.GetMaxTries()){
		FText guess = GetValidGuess();

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(guess);

		std::cout << "Bulls =  " << BullCowCount.Bulls;
		std::cout << " and Cows =  " << BullCowCount.Cows << "\n\n";
	}

	PrintGameSummary();

	return;
}

FText GetValidGuess() {
	/* loop continually until the user gives a valid guess. */

	FText guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		// get a guess from the player
		int32 TryNum = BCGame.GetCurrentTry();
		std::cout << "Try " << TryNum << " of " << BCGame.GetMaxTries();
		std::cout << ". Please enter in your guess: ";
		std::getline(std::cin, guess);

		Status = BCGame.CheckGuessValidity(guess);
		switch (Status) {
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word. \n\n";
			break;
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter in an isogram. An Isogram has no repeating characters. \n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter in a fully lowercase word. \n\n";
			break;
		default:
			// assume the guess is valid.
			break;
		}
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

void PrintAsciiArtFromFile() {
	std::string line;
	std::ifstream ArtFile("art.txt");
	if (ArtFile.is_open()) {
		while (getline(ArtFile, line)) {
			std::cout << line << '\n';
		}
		ArtFile.close();
	}

	else std::cout << "Unable to open file";
}
