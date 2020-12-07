#pragma once
#include<iostream>
#include<set>
#include<string>
#include<algorithm>
#include<exception>
#include<utility>
#include"Mastermind_player.h"
#include"HTMLLoger_class.h"

class Mastermind
{
private:
	mtmd::IPlayer * player1;
	mtmd::IPlayer * player2;
public:
	Mastermind(mtmd::IPlayer * player1, mtmd::IPlayer *player2) : player1(player1), player2(player2)
	{
	}
	void Game_start()
	{
		player1->PrepareForANewGame();
		player2->PrepareForANewGame();
		player1->get_loger()->LogMessage("Game", "is started");
		int count = 1;
		while (true)
		{

			std::cout << count << "-th try\n";
			std::cout << player1->name() << "  guessing turn :";
			if (count == 1)
				player1->first_guessing();
			else
				player1->MakeAGuess(player2->RespondToGuess());
			std::cout << player1->guess_try() << "\n";
			std::cout << player2->name() << " hints :";
			player2->checking(player1->guess_try());
			player2->RespondToGuess();
			std::cout << player2->RespondToGuess().first << " " << player2->RespondToGuess().second << " \n";
			std::cout << player2->name() << " guessing turn :";
			if (count == 1)
				player2->first_guessing();
			else
				player2->MakeAGuess(player1->RespondToGuess());
			std::cout << player2->guess_try() << "\n";
			std::cout << player1->name() << " hints :";
			player1->checking(player2->guess_try());
			player1->RespondToGuess();
			std::cout << player1->RespondToGuess().first << " " << player1->RespondToGuess().second << " \n";
			if (player1->RespondToGuess().second == 4 && player2->RespondToGuess().second != 4)
			{
				player2->get_loger()->LogMessage(player2->name(), "wins");
				std::cout << player2->name() << " wins \n";
				std::cout << player2->name() << " num was -" << player2->num() << " wins \n";
				break;
			}
			if (player2->RespondToGuess().second == 4 && player1->RespondToGuess().second != 4)
			{
				player1->get_loger()->LogMessage(player1->name(), " wins");
				std::cout << player1->name() << " wins \n";
				std::cout << player1->name() << " num was  " << player1->num() << "\n";
				break;
			}
			if (player2->RespondToGuess().second == 4 && player1->RespondToGuess().second == 4)
			{
				player2->get_loger()->LogMessage("GAME", "IS ENDED WITH DRAW");
				std::cout << "GAME ENDED WITH DRAW \n";
				break;
			}
			++count;
		}


	}
};



