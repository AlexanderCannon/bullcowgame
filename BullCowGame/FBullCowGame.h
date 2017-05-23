#pragma once
#include <string>
#include <map>
#define TMap std::map

//unreal friendly substitutes
using int32 = int;
using FString = std::string;

//two ints; defaults to 0, 0
struct FBullCowCount {
	int32 bulls = 0;
	int32 cows = 0;	
};

enum class EGuessStatus {
	Invalid,
	Okay,
	Not_Isogram,
	Wrong_Length,
	Case_Mismatch
};

class FBullCowGame {
public:
	FBullCowGame(int32); //constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;

	bool IsGameWon() const;
	EGuessStatus IsGuessValid(FString) const;

	void HasGuessed();
	void Reset(int32);
	FBullCowCount SubmitValidGuess(FString);
	bool IsIsogram();
	bool IsLowerCase();
	bool CheckWordLength(int32);

private:
	int32 MyCurrentTry;
	int32 MyMaxTries;
	FString MyHiddenWord;
	int32 MinWordLength;
	int32 MaxWordLength;
	bool bIsIsogram;
	bool bIsGameWon;

	bool IsIsogram(FString) const;
	bool IsLowercase(FString) const;
	FString SelectWord(int) const;
};