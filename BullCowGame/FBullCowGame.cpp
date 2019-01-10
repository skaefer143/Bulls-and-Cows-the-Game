#include "FBullCowGame.h"
#include <map>
#define TMap std::map

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

bool FBullCowGame::IsIsogram(FString Word) const {
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
