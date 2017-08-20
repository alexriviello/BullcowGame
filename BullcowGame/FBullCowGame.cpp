#pragma once

#include "FBullCowGame.h"
#include <map>

//making syntax Unreal friendly
#define TMap std::map
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame(){Reset();}// default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry;}
int32 FBullCowGame::GetHiddenWordLength() const {return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const{ return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ { 3,4 },{ 4,7 },{ 5,10 },{ 6,15 },{7,20} };
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

//resets the game to initial values
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet"; // this MUST be an isogram
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

// receives a VALID guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	//setup return variable
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	//loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++) {
		//compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++) {
			// if they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar]) {
				if (MHWChar == GChar) { // if they're in the same place
					BullCowCount.Bulls++; //increment bulls
				}
				else {
					BullCowCount.Cows++; //increment cows if not
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}
	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	//treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; //set up map
	for (auto Letter : Word)// for all letters of the word
	{
		Letter = tolower(Letter); // so it can handle mixed case

		if (LetterSeen[Letter])//if letter is found
		{
			return false;//not an isogram
		}
		else
		{
			LetterSeen[Letter] = true;//otherwise add letter to the map 
		}
	}
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word)// for all letters of the word
	{
		if (!islower(Letter))//if uppercase letter is found
		{
			return false;//not lowercase
		}
		else
		{
			return true;//otherwise add letter to the map 
		}
	}
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{	
	if (!IsIsogram(Guess))// if the guess isn't an isogram
	{
		return EGuessStatus::Not_Isogram;//return an error 
	}
	else if (!IsLowercase(Guess))// if the guess isn't all lowercase TODO write function
	{
		return EGuessStatus::Not_Lowercase;//return an error
	}
	else if (Guess.length() != GetHiddenWordLength())//if the guess isn't the right length
	{
		return EGuessStatus::Wrong_Length;//return an error
	}
	else
	{
		return EGuessStatus::OK;//otherwise return ok
	}
}
