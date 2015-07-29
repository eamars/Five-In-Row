#include <iostream>
#include "ChessBoard.h"
#include "Player.h"
#include <string>
#include <limits> // max integer
#include "optimization.h"

#include <ctime>

#define in :

using std::cout;
using std::endl;

int main(void){
	
	ChessBoard board(15);
	Player playerA(board, 0);
	Player playerB(board, 1);

	

	playerA.setPiece(6, 6);
	playerB.setPiece(6, 7);
	playerA.setPiece(5, 5);
	cout << board;
	
	
	cout << "START" << endl;
	const clock_t begin_time = clock();

	for (int it = 0; it < 10; it++)
	{
		playerB.suggestNextMove();
		playerB.useSuggestedMove();
		cout << board << endl;
		if (playerB.isWin())
		{
			break;
		}
		playerA.suggestNextMove();
		playerA.useSuggestedMove();
		cout << board << endl;
		if (playerA.isWin())
		{
			break;
		}
	}
	cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
	cout << "\nEND" << endl;

	/*
	Benchmark
	std::srand(std::time(0));
	
	string s;
	int r = 0;
	


	for (int i = 0; i < 10000; i++)
	{
		s.clear();
		for (int j = 0; j < 15; j++)
		{
			r = std::rand() % 2;
			if (r == 0)
			{
				s += 'E';
			}
			else
			{
				s += 'A';
			}
		}
		get_pattern_rank(s, 'A');

	}
	std::cout << float(clock() - begin_time) / CLOCKS_PER_SEC;
	cout << "\nEND\n";
	*/


	return 0;
}