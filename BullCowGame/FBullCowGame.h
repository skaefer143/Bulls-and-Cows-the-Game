#pragma once
#include <string>

class FBullCowGame {
public:
	FBullCowGame(); // constructor

	int GetMaxTries() const;
	int GetCurrentTry() const;
	bool IsGameWon() const;

	bool CheckGuessValidity(std::string); // TODO make a more rich return value.
	void Reset(); // TODO make a more rich return value.
	// provide a method for counting bulls & cows, and increasing turn #

private:
	// see constructor for initialization 
	int MyCurrentTry;
	int MyMaxTries;
};