#pragma once
#include <string>
#include "FBullCowGame.h"

//unreal friendly substitutes
using FText = std::string;

void PrintIntro();
void PlayGame();
bool AskToPlayAgain();
FText GetValidGuess();
void PrintBullsAndCows(FBullCowCount);
void PrintGameSummary();
int32 SelectWordLength();