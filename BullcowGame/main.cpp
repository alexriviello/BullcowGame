/* This is the console executable that makes use of the BullCow class.
This acts as the view in an MVC pattern and is responsible for all user interaction. 
For game logic see the FBullCowGame class.
*/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

//making syntax Unreal friendly
using FText = std::string;
using int32 = int;

// function prototypes as outside a class
void PrintIntro();
void PrintGameSummary();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();

FBullCowGame BCGame; //instantiate a new game, which is reused across plays

//the entry point for our application
int main()
{
	do {
		PrintIntro();
		PlayGame();
	} 
	while (AskToPlayAgain());
	
	return 0; // exit the application
}

void PrintIntro()
{
	std::cout << "\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "   ,/         \\,  "  << std::endl;
	std::cout << "  ((__,-\"\"\"-,__))         ,-\"\"\"-," << std::endl;
	std::cout << "  .-'(       )`-,     .-'(       )`-," << std::endl;
	std::cout << "  `~~`d\\   /b`~~`     `~~`d\\   /b`~~`" << std::endl;
	std::cout << "      |     |             |     |  " << std::endl;
	std::cout << "      (6___6)             (6___6)  " << std::endl;
	std::cout << "       `---`               `---` " << std::endl;
	std::cout << "       BULLS                COWS " << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	return;
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon() == true)
	{
		std::cout << "You won the game!\n";
	}
	else 
	{
		std::cout << "You lost. Better luck next time!\n";
	}
	return;
}

//plays a single game to completion
void PlayGame()
{
	BCGame.Reset();
	int MaxTries = BCGame.GetMaxTries();

	//loop asking for guesses while the game is NOT won
	//and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess();

		//submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}
	PrintGameSummary();
	return;
}

// TODO choose difficulty method

//loop continually until user gives valid guess
FText GetValidGuess()
{
	FText Guess = "";

	EGuessStatus Status = EGuessStatus::Invalid_Status;
	do {
		//get a guess from the player
		int32 CurrentTry = BCGame.GetCurrentTry();
		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries() << ". Enter your guess: ";
	
		std::getline(std::cin, Guess);

			//check status and give feedback
			Status = BCGame.CheckGuessValidity(Guess);
			switch (Status) {
			case EGuessStatus::Wrong_Length:
				std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n\n";
				break;
			case EGuessStatus::Not_Isogram:
				std::cout << "Please enter a word without repeating letters.\n\n";
				break;
			case EGuessStatus::Not_Lowercase:
				std::cout << "Please enter all lowercase letters.\n\n";
				break;
			default:
				//assume the guess is valid
				break;
			}
	} while (Status != EGuessStatus::OK); // keep looping until we get no errors
	return Guess;
}

bool AskToPlayAgain()
{
	FText Response = "";
	std::cout << "Do you want to play again? (y/n)";
	std::getline(std::cin, Response);
	if(Response[0] == 'y' || Response[0] == 'Y')
	{
		BCGame.Reset();
		return true;
	}
	else
	{
		return false;
	}

}
