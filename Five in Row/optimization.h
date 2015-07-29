#pragma once

#include <vector>
#include "ChessBoard.h"


/* Misc function */


int get_pattern_rank(std::string s, char player);

int evaluate_at(ChessBoard &board, char player , int i, int j);

std::vector<std::pair<int, int>> nextPossibleMovement(ChessBoard &board, int player_id);
