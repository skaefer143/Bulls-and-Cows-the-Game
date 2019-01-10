#include "FBullCowGame.h"

using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

void FBullCowGame::Reset() {
	constexpr int32 MAX_TRIES = 8;
	const FString HIDDEN_WORD = "planet";

	MyMaxTries = MAX_TRIES;
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameWon = false;
	return;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	// receives a valid guess, increments turn, and returns count
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
