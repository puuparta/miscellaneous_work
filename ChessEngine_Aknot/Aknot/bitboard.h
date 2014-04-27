#ifndef _BITBOARD_H
#define _BITBOARD_H

#include <string>


//-----------------------------------------------------------------------------------

typedef unsigned long long BITBOARD;

// bitboards
extern BITBOARD king[64];
extern BITBOARD queen[64];
extern BITBOARD knight[64];
extern BITBOARD bishop[64];
extern BITBOARD rook[64];
extern BITBOARD white_pawn[64];
extern BITBOARD white_pawn_attack[64];
extern BITBOARD black_pawn[64];
extern BITBOARD black_pawn_attack[64];

// compass for sliding moves
extern BITBOARD NorthWest(BITBOARD sq, BITBOARD bb);
extern BITBOARD NorthEast(BITBOARD sq, BITBOARD bb);
extern BITBOARD SouthWest(BITBOARD sq, BITBOARD bb);
extern BITBOARD SouthEast(BITBOARD sq, BITBOARD bb);
extern BITBOARD North(BITBOARD sq, BITBOARD bb);
extern BITBOARD South(BITBOARD sq, BITBOARD bb);
extern BITBOARD West(BITBOARD sq, BITBOARD bb);
extern BITBOARD East(BITBOARD sq, BITBOARD bb);

//-----------------------------------------------------------------------------------


/*
class Bitboard
{
public:
	BITBOARD enemy_and_emptybits(int square);
	BITBOARD empty_bits(int square);
	BITBOARD enemy_and_emptybits(BITBOARD square);
	BITBOARD empty_bits(BITBOARD square);
};

//do some bloat, is this better to be macro?
inline int get_rank(int square) {
	return square >> 3;
}

inline int get_file(int square) {
	return square & 7; //speedup square % 8;
}
*/
#endif //end define