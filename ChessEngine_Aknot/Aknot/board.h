#ifndef _BOARD_H
#define _BOARD_H

#include <string>
#include "piece.h"
#include "square.h"

	class Board
	{
	public:
		Board();
		Square square[64];
		BITBOARD black_pawns;
		BITBOARD black_king;
		BITBOARD black_queens;
		BITBOARD black_bishops;
		BITBOARD black_knights;
		BITBOARD black_rooks;
		BITBOARD white_pawns;
		BITBOARD white_king;
		BITBOARD white_queens;
		BITBOARD white_bishops;
		BITBOARD white_knights;
		BITBOARD white_rooks;
		void set_to_board(Piece p, BITBOARD sq);
		int get_t_hash(Type t, Color c);
		void set_fen(std::string fen);
		void set_fen();
	private:
		Piece piece_from_token(char token);
	};

	

#endif