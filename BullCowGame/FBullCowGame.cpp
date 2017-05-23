/*
 * Game controller cass
 */
#pragma once
#include "FBullCowGame.h"
#include <iostream>
#include <map>

//unreal friendly substitutes
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(int32 DefaultValue) {
	Reset(DefaultValue);
}

int32 FBullCowGame::GetMaxTries() const {
	TMap <int32, int32> WordLengthToMaxTries {
		{3, 5},
		{4, 7},
		{5, 10},
		{6, 12},
		{7, 15},
		{8, 17}
	};
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const {
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const {
	return MyHiddenWord.length();
}

bool FBullCowGame::IsGameWon() const { 
	return  bIsGameWon;
}

void FBullCowGame::Reset(int32 SelectedWordLenght) {
	constexpr int32 MAX_TRIES = 8;
	constexpr int32 MAX_WORD_LENGTH = 8;
	constexpr int32 MIN_WORD_LENGTH = 3;

	MyMaxTries = MAX_TRIES;
	MyCurrentTry = 1;
	MyHiddenWord = SelectWord(SelectedWordLenght);
	bIsGameWon = false;
	MaxWordLength = MAX_WORD_LENGTH;
	MinWordLength = MIN_WORD_LENGTH;
	return;
}
/*
 * receives a valid guess
 * returns count
 * incriments turn
 */
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess) {
	//setup return var
	FBullCowCount BullCowCount;
	int32 HiddenWordLength = MyHiddenWord.length();
	int32 GuessLength= Guess.length();
	for (int32 i = 0; i < HiddenWordLength; i++) {
		for (int32 j = 0; j < GuessLength; j++) {
			if (Guess[j] == MyHiddenWord[i]) {
				if (i == j) {
					BullCowCount.bulls++;
				} else {
					BullCowCount.cows++;
				}
			}
		}
	}
	if (BullCowCount.bulls == GetHiddenWordLength()) {
		bIsGameWon = true;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram() {
	return false;
}

bool FBullCowGame::IsLowerCase() {
	return false;
}


void FBullCowGame::HasGuessed() {
	MyCurrentTry++;
	return;
}

EGuessStatus FBullCowGame::IsGuessValid(FString Guess) const {
	if (Guess.length() != GetHiddenWordLength()) {
		return EGuessStatus::Wrong_Length;
	} else if (!IsIsogram(Guess)) {
		return EGuessStatus::Not_Isogram;
	} else if (!IsLowercase(Guess)) {
		return EGuessStatus::Case_Mismatch;
	} else {
		return EGuessStatus::Okay;
	}
}

bool FBullCowGame::IsIsogram(FString Guess) const {
	if (Guess.length() <= 1) {
		return true;
	}
	TMap <char, bool> LettersSeen;
	//for each item
	for (auto Letter : Guess) {
		Letter = tolower(Letter);
		//add to array
		if (LettersSeen[Letter]) {
			return false;
		}
		LettersSeen[Letter] = true;
	}
	return true;
}

bool FBullCowGame::IsLowercase(FString Guess) const {
	for (auto Letter : Guess) {
		if (isupper(Letter)) {
			return false;
		}
	}
	return true;
}

bool FBullCowGame::CheckWordLength(int32 SelectedLength) {
	if (SelectedLength >= MinWordLength && SelectedLength <= MaxWordLength) {
		return true;
	}
	return false;
}

FString FBullCowGame::SelectWord(int Length) const {
	TMap <int32, FString> WordLengths {
		{3, "ant"},	
		{4, "dogs"},
		{5, "horse"},
		{6, "string"},
		{7, "squated"},
		{8, "squinted"}
	};
	return WordLengths[Length];
}