#pragma once

#include <tuple>
#include <vector>
#include <iostream>

#include "ChessBoard.h"


using std::vector;
using std::tuple;
using std::pair;


typedef pair<int, int> player_step;

const static vector<char> player_pool = { 'A', 'B' };

class Player
{
private:
	int player_id; // player piece marker
	ChessBoard &board; // reference to current board

	player_step suggestStep;
	int local_max_rank;
	int init_counter;
	bool alreadyWin;

	/* Private function */
	int alphabeta(int i, int j, int depth, int turn, int alpha, int beta);

public:
	Player(ChessBoard &_board, int player_id);
	~Player();

	// set piece on board and push to stack if successed
	bool setPiece(int i, int j);

	bool isWin();

	void suggestNextMove();

	void useSuggestedMove();

	friend std::ostream& operator<<(std::ostream &os, const Player &p);
};

