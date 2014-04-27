#ifndef _PIECE_H
#define _PIECE_H

#include "bitboard.h"

enum Color
{
	white=1,
	black=256
};

enum Type
{
	p = 1,
	b = 2,
	n = 4,
	r = 8,
	q = 16,
	k = 32
};

class Piece
{
public:
	double value;
	BITBOARD *moveBB;
	BITBOARD attackBB;
	Type type;
	Color color;
	int t_hash() { return this->type | this->color;}
};


#endif