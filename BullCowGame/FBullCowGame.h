#pragma once
#include <string>

using FString = std::string;
using int32 = int;

struct FBullCowCount {
	int32 Bulls = 0;
	int32 Cows = 0;
};

enum class EGuessStatus {
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	EGuessStatus CheckGuessValidity(FString) const;
	bool IsGameWon() const;

	void Reset(); // TODO make a more rich return value.
	FBullCowCount SubmitGuess(FString);

private:
	// see constructor for initialization 
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
};