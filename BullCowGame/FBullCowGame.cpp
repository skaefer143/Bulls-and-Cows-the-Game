#include "FBullCowGame.h"

using int32 = int;

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	return;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
	// receives a valid guess, increments turn, and returns count

	// increment the turn counter
	MyCurrentTry++;

	// setup a return var
	FBullCowCount BullCowCount;

	// loop through all letters in guess
	int32 MyHiddenWordLength = MyHiddenWord.length();
	for (int32 i = 0; i < MyHiddenWordLength; i++) {
		for (int32 j = 0; j < MyHiddenWordLength; j++) {
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

	return BullCowCount;
}

FBullCowGame::FBullCowGame() {
	Reset();
}

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }

int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }

bool FBullCowGame::IsGameWon() const {
	return false;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
	if (false) {
		// if the guess isn't an isogram, return an error,
		return EGuessStatus::Not_Isogram;
	}
	else if (false) {
		// if the guess isn't lowercase, return an error
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) {
		//if the guess length is wrong, return an error
		return EGuessStatus::Wrong_Length;
	}
	else {
		// otherwise return OK 
		return EGuessStatus::OK;
	}
}
