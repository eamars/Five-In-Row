#include "Player.h"
#include "optimization.h"
#include <limits> // max integer
#include "ChessBoard.h"

// prevent duplicated definition
#ifndef in
#define in :
#endif

#define MAX(X, Y) X > Y ? X : Y
#define MIN(X, Y) X < Y ? X : Y


Player::Player(ChessBoard &_board, int _player_id)
	: board(_board) // initilize board immediately
{
	player_id = _player_id;
	alreadyWin = false;
}


Player::~Player()
{
}



bool Player::setPiece(int i, int j)
{
	if (board.getNode(i, j) != 'E')
	{
		return false;
	}

	board.setNode(i, j, player_pool[player_id]);
	if (evaluate_at(board, player_pool[player_id], i, j) >= 30000000)
	{
		alreadyWin = true;
	}
	return true;
}


std::ostream& operator<<(std::ostream &os, const Player &p)
{
	os << "Player: " << player_pool[p.player_id] << "\n";
	return os;
}



int Player::alphabeta(int i, int j, int depth, int turn, int alpha, int beta)
{
	int value;
	
	
	
	/*
		If reached the maximum depth, then evaluate the current cell and exit
	*/
	if (depth == 0)
	{
		// If the current step has the highest rank, then the intersection is seen as next
		// suggested move position
		board.setNode(i, j, player_pool[turn]);
		value = evaluate_at(board, player_pool[turn], i, j);
		std::cout << value << " " << local_max_rank << "\n";
		if (local_max_rank < value)
		{
			local_max_rank = value;
			board_movement move = board.getQueueAtIndex(init_counter); 
			suggestStep = std::make_pair(std::get<0>(move), std::get<1>(move)); // record the coordinates
		}
		
		board.rollBack();
		return value;
	}
	
	// test if win. then stop simulating
	board.setNode(i, j, player_pool[turn]);
	value = evaluate_at(board, player_pool[turn], i, j);
	if (value >= 30000000)
	{
		/*
		TODO: Strange behavior when reaching winning!*/
		local_max_rank = value;
		board_movement move = board.getQueueAtIndex(init_counter);
		suggestStep = std::make_pair(std::get<0>(move), std::get<1>(move)); // record the coordinates

		board.rollBack();
		return value;
	}
	board.rollBack();


	board.setNode(i, j, player_pool[turn]);
	// alpha-beta iteration
	for (auto move in nextPossibleMovement(board, turn))
	{
		// play as opponent
		value = -alphabeta(move.first, move.second, depth - 1, !turn, -beta, -alpha);

		if (value >= beta)
		{
			board.rollBack(); // rollback everytime when moving
			return beta;
		}
		if (value > alpha)
		{
			alpha = value;
		}
	}

	board.rollBack();
	return alpha;

}


bool Player::isWin()
{
	return alreadyWin;
}



void Player::suggestNextMove()
{
	local_max_rank = 0;

	// make suggestions for first iteration
	for (auto move in nextPossibleMovement(board, player_id))
	{
		std::cout << "Minimum suggested move: [" << move.first << " " << move.second << "]\n";
		// count for how many steps we have already made
		init_counter = board.getCounter();
		alphabeta(move.first, move.second, 2, player_id, -std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
		
	}
	std::cout << "Selected: [" << suggestStep.first << " " << suggestStep.second << "]\n";
}

void Player::useSuggestedMove()
{
	setPiece(suggestStep.first, suggestStep.second);
}