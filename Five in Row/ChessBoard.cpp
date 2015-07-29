#include "ChessBoard.h"
#include "optimization.h"


// prevent duplicated definition
#ifndef in
#define in :
#endif


/*
	Create the object with default size
*/
ChessBoard::ChessBoard()
{
	board.resize(board_size);
	step_counter = 0;
	for (auto &row : board)
	{
		row.resize(board_size);
		std::fill(row.begin(), row.end(), 'E');
	}
}

/*
	Create the object with custom size
*/
ChessBoard::ChessBoard(int size)
{
	board_size = size;
	board.resize(board_size);
	step_counter = 0;
	for (auto &row : board)
	{
		row.resize(board_size);
		std::fill(row.begin(), row.end(), 'E');
	}
}

ChessBoard::ChessBoard(ChessBoard &other)
{
	board_size = other.board_size;
	board = other.board;
}


ChessBoard::~ChessBoard()
{
	// do nothing
}

/*
	Return the certain node at given row and col
*/
char ChessBoard::getNode(int i, int j)
{
	return board[i][j];
}


/*
	Set the node at certain row and col
*/
void ChessBoard::setNode(int i, int j, char player)
{
	// push to history
	history.push_back(std::make_tuple(i, j, getNode(i, j), player));
	board[i][j] = player;
	step_counter += 1;
}

void ChessBoard::rollBack()
{
	// get last movement
	board_movement lastStep = history.back();

	// set piece back to origonal one
	board[std::get<0>(lastStep)][std::get<1>(lastStep)] = std::get<2>(lastStep);

	// remove record in history
	history.pop_back();

	step_counter -= 1;
}


int ChessBoard::getSize()
{
	return board_size;
}

int ChessBoard::getCounter()
{
	return step_counter;
}

board_movement ChessBoard::getQueueAtIndex(int index)
{
	return history[index];
}

int ChessBoard::getLengthOfQueue()
{
	return history.size();
}

string ChessBoard::getRow(int i, int j)
{
	// create output string
	string out(1, board[i][j]);

	int col_num = j - 1;


	// left
	for (int it = 0; it < 4; it++)
	{
		if (col_num >= 0)
		{
			out = board[i][col_num] + out;
			col_num -= 1;
		}
		else
		{
			break;
		}
	}

	col_num = j + 1;

	// right
	for (int it = 0; it < 4; it++)
	{
		if (col_num < board_size)
		{
			out = out + board[i][col_num];
			col_num += 1;
		}
		else
		{
			break;
		}
	}

	return out;
}

string ChessBoard::getCol(int i, int j){
	string out(1, board[i][j]);

	vector<char> col;
	for (auto it in board)
	{
		col.push_back(it[j]);
	}

	int row_num = i - 1;


	// up
	for (int it = 0; it < 4; it++)
	{
		if (row_num >= 0)
		{
			out = col[row_num] + out;
			row_num -= 1;
		}
		else
		{
			break;
		}
	}

	row_num = i + 1;

	// down
	for (int it = 0; it < 4; it++)
	{
		if (row_num < board_size)
		{
			out = out + col[row_num];
			row_num += 1;
		}
		else
		{
			break;
		}
	}


	return out;
}


// bottom left to upper right
string ChessBoard::getDiag1(int i, int j)
{
	string out(1, board[i][j]);

	vector<char> diag;

	int row_num, col_num;

	// lower left to upper right
	row_num = i - 1;
	col_num = j + 1;
	for (int it = 0; it < 4; it++)
	{
		if (row_num >= 0 && col_num < board_size)
		{
		
			out = out + board[row_num][col_num];
			row_num--;
			col_num++;
		}
		else
		{
			break;
		}
	}

	// upper right to lower left
	row_num = i + 1;
	col_num = j - 1;
	for (int it = 0; it < 4; it++)
	{
		if (row_num <board_size && col_num >= 0)
		{
			out = board[row_num][col_num] + out;
			row_num++;
			col_num--;
		}
		else
		{
			break;
		}
	}

	return out;
}

string ChessBoard::getDiag2(int i, int j)
{
	string out(1, board[i][j]);

	vector<char> diag;

	int row_num, col_num;

	// upper left to lower right
	row_num = i + 1;
	col_num = j + 1;
	for (int it = 0; it < 4; it++)
	{
		if (row_num < board_size && col_num < board_size)
		{

			out = out + board[row_num][col_num];
			row_num++;
			col_num++;
		}
		else
		{
			break;
		}
	}

	// lower right to upper left
	row_num = i - 1;
	col_num = j - 1;
	for (int it = 0; it < 4; it++)
	{
		if (row_num >= 0 && col_num >= 0)
		{
			out = board[row_num][col_num] + out;
			row_num--;
			col_num--;
		}
		else
		{
			break;
		}
	}

	return out;
}

bool ChessBoard::isValidMovement(int i, int j)
{
	return board[i][j] == 'E';
}


// overload function
std::ostream& operator<<(std::ostream &os, const ChessBoard &cb)
{
	os << "ChessBoard with size " << cb.board_size << "\nQueue: ";
	for (auto t in cb.history)
	{
		os << "[(" << std::get<0>(t) << ", " << std::get<1>(t) << "), (" << std::get<2>(t) << ", " << std::get<3>(t) << ")] ";
	}
	os << "\n";
	/* show col number */
	os << "  ";

	for (int i = 0; i < cb.board_size; i++)
	{
		os << char(i + 'A') << " ";
	}

	// send to flush
	os << std::endl;

	int row_num = 'A';

	for (auto row in cb.board)
	{
		/* show row number */
		os << char(row_num) << " ";
		row_num++;

		for (auto col in row)
		{
			os << col << " ";
		}
		os << "\n";
	}
	return os;
}

