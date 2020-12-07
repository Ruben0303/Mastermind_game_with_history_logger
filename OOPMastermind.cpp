#include "Mastermind_Game.h"
#include"HTMLLoger_class.h"
#include<iostream>

int main()
{
	std::cout << "\t\t\tGAME RULES :\nPLAYER1 and PLAYER2 will   remember 4 any digits from 0 to 9 \n";
	std::cout << "PLAYER1 and PLAYER2 must guess the digits in their right positions that was remembered by oponent  \n";
	std::cout << "After PLAYER oponent false guess PLAYER must give him hints in this format X Y, \n";
	std::cout << "which means that  PLAYER oponent's guessed number has X digit(s),\n";
	std::cout << "that also has the number PLAYER has remembered and Y digits from X is/are in right position\n";
	std::cout << "\t\tTHE FIRST GUESSER IS WINNER.\n";
	char for_start = ' ';
	std::cout << "IF YOU UNDERSTAND ALL RULES PUSH ANY (ONLY ONE)  KEY AND ENTER";
	std::cin >> for_start;
	std::ofstream fout;
	my_logger::HTMLLogger myLogger(fout, "a.html");
	my_logger::Logger * logger = &myLogger;
	std::cout << "types of players \n 1: CPUPlayer \n 2: HumanPlayer\n 3: CPURandomPlayer \n";
	int pl1_type , pl2_type;
	std::cout << "ENTER Player 1 type";
	std::cin >> pl1_type;
	std::cout << "ENTER Player 2 type";
	std::cin >> pl2_type;
	std::string p1name;
	std::cout << "Enter player1 name";
	std::cin >> p1name;
	std::string p2name;
	std::cout << "Enter player2 name";
	std::cin >> p2name;
	mtmd::IPlayer * player1 = nullptr;
	mtmd::IPlayer * player2 = nullptr;

	switch (pl1_type)
	{
	case 1:
		player1 = new mtmd::CPUPlayer(logger, p1name);
		break;
	case 2:
		player1 = new mtmd::HumanPlayer(logger, p1name);
		break;
	case 3:
		player1 = new mtmd::CPURandomPlayer(logger, p1name);
		break;
	}
	switch (pl2_type)
	{
	case 1:
		player2 = new mtmd::CPUPlayer(logger, p2name);
		break;
	case 2:
		player2 = new mtmd::HumanPlayer(logger, p2name);
		break;
	case 3:
		player2 = new mtmd::CPURandomPlayer(logger, p2name);
		break;
	}
	Mastermind mastermind(player1, player2);
	mastermind.Game_start();
	delete player2;
	delete player1;

}