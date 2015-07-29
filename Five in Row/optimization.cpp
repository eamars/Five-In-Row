#include "optimization.h"
#include <iostream>
#include <regex>
#include <algorithm>
#include <string>
#include <boost/regex.hpp>

#include "Player.h"

#ifndef in
#define in :
#endif

using std::vector;
using std::string;
using std::pair;
using boost::regex; // use boost library for a better performence

regex Al5(".*AAAAA.*");
regex Al4(".*EAAAAE.*");
regex Ad4a("(.*AAAAE.*)|(.*EAAAA.*)");
regex Ad4b("(.*AAAEA.*)|(.*AEAAA.*)");
regex Ad4c(".*AAEAA.*");
regex Al3(".*EEAAAEE.*");
regex Ad3a("(.*AAAEE.*)|(.*EEAAA.*)");
regex Ad3b("(.*EAEAAE.*)|(.*EAAEAE.*)");
regex Ad3c("(.*AEEAA.*)|(.*AAEEA.*)");
regex Ad3d(".*AEAEA.*");
regex Al2(".*EEEAAEEE.*");
regex Ad2a("(.*AAEEE.*)|(.*EEEAA.*)");
regex Ad2b(".*EEAEAEE.*");
regex Ad2c(".*EAEEAE.*");
regex Al1(".*EAE.*");
regex Ad1("(.*AE.*)|(.*EA.*)");
regex As(".*A.*");

regex Bl5(".*BBBBB.*");
regex Bl4(".*EBBBBE.*");
regex Bd4a("(.*BBBBE.*)|(.*EBBBB.*)");
regex Bd4b("(.*BBBEB.*)|(.*BEBBB.*)");
regex Bd4c(".*BBEBB.*");
regex Bl3(".*EEBBBEE.*");
regex Bd3a("(.*BBBEE.*)|(.*EEBBB.*)");
regex Bd3b("(.*EBEBBE.*)|(.*EBBEBE.*)");
regex Bd3c("(.*BEEBB.*)|(.*BBEEB.*)");
regex Bd3d(".*BEBEB.*");
regex Bl2(".*EEEBBEEE.*");
regex Bd2a("(.*BBEEE.*)|(.*EEEBB.*)");
regex Bd2b(".*EEBEBEE.*");
regex Bd2c(".*EBEEBE.*");
regex Bl1(".*EBE.*");
regex Bd1("(.*BE.*)|(.*EB.*)");
regex Bs(".*B.*");


int get_pattern_rank(string s, char player)
{
	if (player == 'A')
	{
		if (boost::regex_match(s, Al5))
		{
			return 30000000;
		}
		if (boost::regex_match(s, Al4))
		{
			return 300000;
		}
		if (boost::regex_match(s, Ad4a))
		{
			return 2500;
		}
		if (boost::regex_match(s, Ad4b))
		{
			return 3000;
		}
		if (boost::regex_match(s, Ad4c))
		{
			return 2600;
		}
		if (boost::regex_match(s, Al3))
		{
			return 3000;
		}
		if (boost::regex_match(s, Ad3a))
		{
			return 500;
		}
		if (boost::regex_match(s, Ad3b))
		{
			return 800;
		}
		if (boost::regex_match(s, Ad3c))
		{
			return 600;
		}
		if (boost::regex_match(s, Ad3d))
		{
			return 550;
		}
		if (boost::regex_match(s, Al2))
		{
			return 650;
		}
		if (boost::regex_match(s, Ad2a))
		{
			return 150;
		}
		if (boost::regex_match(s, Ad2b))
		{
			return 250;
		}
		if (boost::regex_match(s, Ad2c))
		{
			return 200;
		}
		if (boost::regex_match(s, Al1))
		{
			return 100;
		}
		if (boost::regex_match(s, Ad1))
		{
			return 10;
		}
		if (boost::regex_match(s, As))
		{
			return 1;
		}
		return 0;
	}
	else
	{
		if (boost::regex_match(s, Bl5))
		{
			return 30000000;
		}
		if (boost::regex_match(s, Bl4))
		{
			return 300000;
		}
		if (boost::regex_match(s, Bd4a))
		{
			return 2500;
		}
		if (boost::regex_match(s, Bd4b))
		{
			return 3000;
		}
		if (boost::regex_match(s, Bd4c))
		{
			return 2600;
		}
		if (boost::regex_match(s, Bl3))
		{
			return 3000;
		}
		if (boost::regex_match(s, Bd3a))
		{
			return 500;
		}
		if (boost::regex_match(s, Bd3b))
		{
			return 800;
		}
		if (boost::regex_match(s, Bd3c))
		{
			return 600;
		}
		if (boost::regex_match(s, Bd3d))
		{
			return 550;
		}
		if (boost::regex_match(s, Bl2))
		{
			return 650;
		}
		if (boost::regex_match(s, Bd2a))
		{
			return 150;
		}
		if (boost::regex_match(s, Bd2b))
		{
			return 250;
		}
		if (boost::regex_match(s, Bd2c))
		{
			return 200;
		}
		if (boost::regex_match(s, Bl1))
		{
			return 100;
		}
		if (boost::regex_match(s, Bd1))
		{
			return 10;
		}
		if (boost::regex_match(s, Bs))
		{
			return 1;
		}
		return 0;
	}
}


int evaluate_at(ChessBoard &board, char player, int i, int j)
{
	int value = 0;

	// get sum of values from all four directions
	value = get_pattern_rank(board.getRow(i, j), player) +
		get_pattern_rank(board.getCol(i, j), player) +
		get_pattern_rank(board.getDiag1(i, j), player) +
		get_pattern_rank(board.getDiag2(i, j), player);

	return value;
}


vector<pair<int, int>> nextPossibleMovement(ChessBoard &board, int player_id)
{
	vector<pair<int, int>> possible_attack;
	vector<pair<int, int>> possible_defence;
	int greatest = 0;
	int greatest_opponent = 0;
	int value;

	for (int a = 0; a < board.getSize(); a++)
	{
		for (int b = 0; b < board.getSize(); b++)
		{
			if (board.isValidMovement(a, b))
			{
				// attack
				board.setNode(a, b, player_pool[player_id]);
				value = evaluate_at(board, player_pool[player_id], a, b);
				if (value > greatest)
				{
					//std::cout << player_pool[player_id] << ": NEW ATTACK POINT: " << a << " " << b << " " << value << "\n";
					greatest = value;
					possible_attack.clear();
					possible_attack.push_back(std::make_pair(a, b));
				}
				else if (value == greatest)
				{
					possible_attack.push_back(std::make_pair(a, b));
				}
				board.rollBack();

				// defence
				board.setNode(a, b, player_pool[!player_id]);
				value = evaluate_at(board, player_pool[!player_id], a, b);
				if (value > greatest_opponent)
				{
					//std::cout << player_pool[player_id] << ": NEW DEFENCE POINT: " << a << " " << b << " " << value << "\n";
					greatest_opponent = value;
					possible_defence.clear();
					possible_defence.push_back(std::make_pair(a, b));
				}
				else if (value == greatest_opponent)
				{
					possible_defence.push_back(std::make_pair(a, b));
				}
				board.rollBack();
			}
		}
	}

	possible_attack.insert(possible_attack.end(), possible_defence.begin(), possible_defence.end());
	return possible_attack;
}

