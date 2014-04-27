
#ifndef _MOVE_H
#define _MOVE_H

#include <map>

#include "bitboard.h"
#include "piece.h"
#include "board.h"

class Move
{
private:
	std::map<int,BITBOARD> move_table;
	std::map<int,BITBOARD>::iterator move_iterator;
	void update_positions(BITBOARD position, Piece* p, Board *board);
	double calculate();
public:
	double make_move(BITBOARD position, Piece* p);
	double eval_position(BITBOARD position, Piece* p, Board *board);


};

#endif



