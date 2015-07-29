#pragma once

#include <iostream>
#include <vector>
#include <tuple>
#include <regex>


using std::string;
using std::vector;
using std::tuple;

#define DEFAULT_BOARD_SIZE 15



/*
	Inspired by 
	http://wenku.baidu.com/view/28f9b1f5f61fb7360b4c653a.html

	Rank the current pattern of chess of certain row or col
*/

typedef vector<vector<char>> matrix;
typedef tuple<int, int, char, char> board_movement; // i, j, old, new

class ChessBoard
{
private:
	matrix board;
	int board_size = DEFAULT_BOARD_SIZE;
	int step_counter;
	vector<board_movement> history; // player movement history
	
public:
	/* Constructor */

	// ChessBoard constructor, default to size 15
	ChessBoard();

	// Custom constructor
	ChessBoard(int size);

	// Copy from others
	ChessBoard(ChessBoard &other);

	// De-reference
	~ChessBoard();

	/* some handful function */

	// get the player at certain node
	char getNode(int i, int j);
	// set the player at certain node
	void setNode(int i, int j, char player);

	void rollBack();

	// get size of board
	int getSize();

	int getCounter();

	board_movement getQueueAtIndex(int index);
	int getLengthOfQueue();

	// get the whole row or col in board
	string getRow(int i, int j);
	string getCol(int i, int j);
	string getDiag1(int i, int j); // bottom left to upper right
	string getDiag2(int i, int j); // upper left to bottom right

	bool isValidMovement(int i, int j);

	/* overload function */

	// overload << operator
	friend std::ostream& operator<<(std::ostream &os, const ChessBoard &cb);

};
