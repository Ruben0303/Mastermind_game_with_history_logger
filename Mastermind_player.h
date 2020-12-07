#pragma once
#ifndef mstmnd_player_incld
#define mstmnd_player_incld
#include<iostream>
#include<cstdlib>
#include<set>
#include<list>
#include<vector>
#include<string>
#include<algorithm>
#include<exception>
#include<stdexcept>
#include<utility>
#include"Logger_class.h"
#include"HTMLLoger_class.h"
namespace mtmd
{
	class IPlayer
	{
	public:
		virtual void PrepareForANewGame() = 0;
		virtual void MakeAGuess(std::pair<int, int> opponent_hints) = 0;
		virtual void first_guessing() = 0;
		virtual const std::pair<int, int> RespondToGuess() const = 0;		
		virtual void checking(const std::string& opon_guess) = 0;
		virtual void set_Name(const std::string&  n) = 0;
		virtual const std::string& guess_try() = 0;
		virtual const std::string& name() = 0;
		virtual const std::string& num() = 0;
		virtual my_logger::Logger* get_loger(){ return p_Loger;}

		~IPlayer() {}
	protected:
		my_logger::Logger* p_Loger;
		std::string Name;
		std::string Num;
		std::string Guessed_Num;
		std::pair<int, int> Hints;
	};
	//////
	//////
	class CPUPlayer :public IPlayer
	{
	public:
		CPUPlayer(my_logger::Logger* loger, std::string Name) 
		{
			p_Loger = loger;
			this->Name = Name;
		}
		
		virtual void PrepareForANewGame() override
		{

			for (int i = 0; i <= 999; ++i)
			{
				std::string s;
				s += std::to_string(i);
				while (s.size() < 4)
					s.push_back('0');
				std::reverse(s.begin(), s.end());
				ALLNUMBS.push_back(s);
			}
			for (int i = 1000; i <= 9999; ++i)
			{
				std::string s;
				s = std::to_string(i);
				ALLNUMBS.push_back(s);
			}
			time_t seconds;
			time(&seconds);
			srand((unsigned int) seconds);
			Num.push_back((rand() % 10) + '0');
			Num.push_back((rand() % 10) + '0');
			Num.push_back((rand() % 10) + '0');
			Num.push_back((rand() % 10) + '0');
		}
		virtual const std::string& guess_try() override 	{ return Guessed_Num;}
		virtual const std::string& name() override { return Name; }
		virtual const std::string& num()  override { return Num; };

		virtual const std::pair<int, int> RespondToGuess() const { return Hints; }
		virtual void set_Name(const std::string&  n) override{ Name = n;}
		virtual void checking(const std::string& user_guess) override
		{
			int intersection = intersection_count(user_guess, Num);
			Hints.first = intersection;
			int pos = same_position(user_guess, Num);
			Hints.second = pos;
			std::string s = "Responds hints for oponent :";
			s += std::to_string(Hints.first) + ":" + std::to_string(Hints.second);
			p_Loger->LogMessage(Name, s);
		}
		virtual void first_guessing()
		{
			Guessed_Num = "0011";
			std::string s = " guessing is : " + Guessed_Num;
			p_Loger->LogMessage(Name, s);

		}

		virtual void MakeAGuess(std::pair<int, int> hints_from_user) override
		{
	

			std::set<std::string> helper;
			auto it = ALLNUMBS.begin();
			while (it != ALLNUMBS.end())
			{
				if (!my_check(hints_from_user, Guessed_Num, *it))
					it = ALLNUMBS.erase(it);
				else
					++it;
			}
			try
			{
				if (ALLNUMBS.size() == 0)
				{
					throw std::invalid_argument("THE GAME IS ENDED , BECAUSE YOU HAVE GIVEN ME FALSE HINTS \n");
				}
			}
			catch(std::invalid_argument & ex)
			{
				std::cout << ex.what() << "\n";
			}
			if (hints_from_user.first == 0 && hints_from_user.second == 0)
				Guessed_Num = *(ALLNUMBS.rbegin());
			else
				Guessed_Num = *ALLNUMBS.begin();
			std::string s = " guessing is : " + Guessed_Num;
			p_Loger->LogMessage(Name, s);

		}
	protected:
		std::list<std::string> ALLNUMBS;
		int same_position(std::string first, std::string second)
		{

			int pos_count = 0;
			for (int i = 0; i < first.size(); ++i)
			{
				if (first[i] == second[i])
					++pos_count;
			}
			return pos_count;
		}
		int intersection_count(std::string first, std::string second)
		{
			std::sort(first.begin(), first.end());
			std::sort(second.begin(), second.end());
			std::vector<char> helper;
			std::set_intersection(first.begin(), first.end(), second.begin(), second.end(), std::back_inserter(helper));
			return helper.size();
		}
		bool my_check(std::pair<int, int> & p, const std::string& comp_try, const std::string& it)
		{
			std::pair<int, int> for_check;
			for_check.first = intersection_count(comp_try, it);
			for_check.second = same_position(comp_try, it);
			return p == for_check;
		}

	};
	/////////////////////////
	/////////////////////
	//////////////////
	///////////////////
	////////////////////////
	/////////////////// HUMAN PLAYER ///////////////
	class HumanPlayer :public IPlayer
	{
	public:
		virtual const std::string& guess_try()  override 
		{ 
			return Guessed_Num; 
		}
		virtual const std::string& name() override { return Name; }
		virtual  std::string& num() override
		{ 
			std::cout << "WHAT WAS YOUR NUMBER " << Name << " ?";
			std::string s;
			std::cin >> Num;
			return Num; 
		};
		HumanPlayer(my_logger::Logger* loger, std::string Name = "player")
		{
			p_Loger = loger;
			this->Name = Name;
		}
		virtual void set_Name(const std::string&  n) override
		{
			Name = n;
		}
		virtual void first_guessing()
		{

			bool helper = true;
			while (helper)
			{
				try
				{
					std::cin >> Guessed_Num;
					if (Guessed_Num.size() != 4)
						throw std::invalid_argument(" you must enter 4 digits and from 0 to 9..Try again");
					helper = false;
				}
				catch (std::invalid_argument&  ex)
				{
					std::cout << Name << ex.what() << "\n";
				}
			}
			std::string s = " guessing is : " + Guessed_Num;
			p_Loger->LogMessage(Name, s);

		}
		
		////////////////
		///////////
		/////////
		///////////
		virtual void MakeAGuess(std::pair<int, int> hints_from_oppon) override
		{
			first_guessing();
		}
		virtual void checking(const std::string& opponent_guess) override
		{
			std::string s = "Responds hints for oponent :";
			s += std::to_string(Hints.first) + ":" + std::to_string(Hints.second);
			p_Loger->LogMessage(Name, s);
			while (true)
			{
				try
				{

					std::cin >> Hints.first >> Hints.second;
					if (!valid_hinting(Hints))
						throw std::invalid_argument(" has given wrong format hints try again");
					break;
				}
				catch (std::invalid_argument & ex)
				{
					std::cout << Name << ex.what() << "\n";
				}
			}
		}
		virtual void PrepareForANewGame() override { return; }
		virtual const std::pair<int, int> RespondToGuess()const override
		{

			return Hints;
		}
	private:
		bool valid_hinting(std::pair<int, int> hints)
		{
			if (hints.first < 0 || hints.first > 4
				|| hints.second < 0 || hints.second > 4
				|| hints.second > hints.first)
				return false;
			return true;
		}
	};

	/////
	////
	class CPURandomPlayer : public CPUPlayer
	{


	public:
		CPURandomPlayer(my_logger::Logger* loger, std::string Name) : CPUPlayer(loger, Name){}
		virtual void first_guessing()
		{
			Guessed_Num = "0011";
			std::string s = " guessing is :" + Guessed_Num;
			p_Loger->LogMessage(Name, s);
		}
		virtual const std::string& guess_try() override { return Guessed_Num; }
		virtual const std::string& name() override { return Name; }
		virtual const std::string& num()  override { return Num; };

		virtual const std::pair<int, int> RespondToGuess() const { return Hints; }
		virtual void set_Name(const std::string&  n) override { Name = n; }
		virtual void checking(const std::string& user_guess) override
		{
			int intersection = intersection_count(user_guess, Num);
			Hints.first = intersection;
			int pos = same_position(user_guess, Num);
			Hints.second = pos;
			std::string s = "Responds hints for oponent :";
			s += std::to_string(Hints.first) + ":" + std::to_string(Hints.second);
			p_Loger->LogMessage(Name, s);
		}
		virtual void MakeAGuess(std::pair<int, int> hints_from_user) override
		{



			std::set<std::string> helper;
			auto it = ALLNUMBS.begin();
			try
			{
				if (ALLNUMBS.size() == 0)
				{
					throw std::invalid_argument("THE GAME IS ENDED , BECAUSE YOU HAVE GIVEN ME FALSE HINTS \n");
				}
			}
			catch (std::invalid_argument & ex)
			{
				std::cout << ex.what() << "\n";
			}
			if (hints_from_user.second != 4)
			{

				auto it = ALLNUMBS.begin();
				time_t seconds;
				time(&seconds);
				srand((unsigned int)seconds);
				for (int i = 0; i < rand() % ALLNUMBS.size(); ++i)
					++it;
				Guessed_Num = *it;
				ALLNUMBS.erase(it);
			}
			std::string s = " guessing is :" + Guessed_Num;
			p_Loger->LogMessage(Name, s);
		}

	};
}
#endif