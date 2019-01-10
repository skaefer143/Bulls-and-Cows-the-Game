/* FBullCowGame is a class that contains all game logic.
Each instance of the class is a new game. Reset() can be called 
to reset the game. 
*/

#pragma once
#include "FBullCowGame.h"
#include <map>

// To make syntax Unreal Engine friendly
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	/* Depending on the length of the hidden word, return the amount of maximum tries. */

	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset() {
	/* Reset the game, each time it is run. */

	const FString HIDDEN_WORD = "plane"; // This MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;

	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	/* Using a valid guess, count the amount of Bulls and Cows. Check if game is won or not. */

	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess

	// loop through all letters in hidden word
	for (int32 i = 0; i < WordLength; i++) {
		// loop through all letters in guess
		for (int32 j = 0; j < WordLength; j++) {
			if (Guess[i] == MyHiddenWord[j]) {
				if (i == j) {
					BullCowCount.Bulls++;
				}
				else {
					BullCowCount.Cows++;
				}
			}
		}
	}
	if (BullCowCount.Bulls == WordLength) {
		bGameWon = true;
	} 
	else {
		bGameWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const {
	/* Return if Word is an isogram. */

	// treat 0 and 1 letter words as isograms
	if (Word.length() <= 1) { return true; }
	
	TMap<char, bool> LetterSeen; // setup map

	// loop through guess
	for (auto Letter : Word) { // for all letters of the word
		Letter = tolower(Letter); // handle mixed case
		if (LetterSeen[Letter]) {
			return false;
		}
		else {
			LetterSeen[Letter] = true;
		}
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const {
	/* Return if Word is lowercase. */

	// treat 0 letter words as lowercase
	if (Word.length() < 1) { return true; }

	// loop through guess
	for (auto Letter : Word) { // for all letters of the word
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}


EGuessStatus FBullCowGame::CheckGuessValidity(FString guess) const {
	/* Check if guess is valid or not. */

	if (!IsIsogram(guess)) {
		// if the guess isn't an isogram, return an error,
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(guess)) {
		// if the guess isn't lowercase, return an error
		return EGuessStatus::Not_Lowercase;
	}
	else if (guess.length() != GetHiddenWordLength()) {
		//if the guess length is wrong, return an error
		return EGuessStatus::Wrong_Length;
	}
	else {
		// otherwise return OK 
		return EGuessStatus::OK;
	}
}
