/* Main.cpp
 * App enrty point!
 */
#pragma once
#include <iostream>
#include <string>
#include "main.h"
#include "FBullCowGame.h"

//unreal friendly substitutes
using FText = std::string;
using int32 = int;

FBullCowGame BCGame(5);
/*
 * Main entry point for game
 */
int main() {
	PrintIntro();
	do {
		PlayGame();
	} while (AskToPlayAgain());
	//Exit application
	return 0;
}

/*
*Prints games intro
*/
void PrintIntro() {
	int32 WordLength = BCGame.GetHiddenWordLength();
	std::cout << "\n\nWelcome to this; my first cpp app, guessing word game\n"
		<< "Can you guess the " << WordLength << " letter isogram I'm thinking of?\n"
		<< "     |___|                  ___\n"
		<< "     (x x)                 (o o)\n"
		<< "      \\_/                   \\_/\n";
	return;
}

/*
 * Game main logic
 */
void PlayGame() {
	int32 WordLength = SelectWordLength();
	BCGame.Reset(WordLength);
	int32 MaxTries = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries) {
		FText Guess = GetValidGuess();
		BCGame.HasGuessed();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		PrintBullsAndCows(BullCowCount);
		std::cout << std::endl;
	}
	PrintGameSummary();
	return;
}

/*
 * Get a guess from player & check validity
 */
FText GetValidGuess() {
	std::cout << "Guess #" << BCGame.GetCurrentTry()
		<< " of " << BCGame.GetMaxTries()
		<< "; enter your guess:\n";
	FText Guess = "";
	std::getline(std::cin, Guess);
	EGuessStatus Status = BCGame.IsGuessValid(Guess);
	switch (Status) {
	case EGuessStatus::Wrong_Length:
		std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n";
		return GetValidGuess();
	case EGuessStatus::Case_Mismatch:
		std::cout << "Please enter your guess in lowercase!\n";
		return GetValidGuess();
	case EGuessStatus::Not_Isogram:
		std::cout << "Please enter an isogram!\nn.b.that's a word with no repeating letters!\n";
		return GetValidGuess();
	default:
		return Guess;
	}
}

/*
 * Print guess
 */
void PrintBullsAndCows(FBullCowCount BullCowCount) {
	std::cout << "Your guess had: " << BullCowCount.bulls
		<< " Bulls and " << BullCowCount.cows << " Cows "<< std::endl;
	return;
}

bool AskToPlayAgain() {
	std::cout << "Play again? (y)es/(n)o\n";
	FText Response = "";
	std::getline(std::cin, Response);
	return (Response[0] == 'y') || (Response[0] == 'Y');
}

void PrintGameSummary() {
	if (BCGame.IsGameWon()) {
		std::cout << "Well done matey; you win at this time!\n\n";
		return;
	} else {
		std::cout << "Bad luck matey; not a win this time!\n\n";
	}
}
int32 SelectWordLength() {
	int32 Length;
	std::cout << "Select the length of your word: (3-8 Characters):\n";
	std::cin >> Length;
	if (!BCGame.CheckWordLength(Length)) {
		std::cout << "Please select a number between 3 and 8!";
		return SelectWordLength();
	}
	std::cout << "You have selected a " << Length << " letter long word, good luck!\n";
	return Length;
}