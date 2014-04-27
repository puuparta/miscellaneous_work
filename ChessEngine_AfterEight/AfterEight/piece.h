/*
  Copyright (c) 2011  Pasi Heinonen, AfterEight Team 
  All Rights Reserved.

  Use and copying of this software and preparation of derivative works
  based upon this software are permitted. Any copy of this software or
  of any derivative work must include the above copyright notice, this
  paragraph and the one after it.  Any distribution of this software or
  derivative works must comply with all aplicable laws.

  This software is made available AS IS, and COPYRIGHT OWNERS DISCLAIMS
  ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
  PURPOSE, AND NOTWITHSTANDING ANY OTHER PROVISION CONTAINED HEREIN, ANY
  LIABILITY FOR DAMAGES RESULTING FROM THE SOFTWARE OR ITS USE IS
  EXPRESSLY DISCLAIMED, WHETHER ARISING IN CONTRACT, TORT (INCLUDING
  NEGLIGENCE) OR STRICT LIABILITY, EVEN IF COPYRIGHT OWNERS ARE ADVISED
  OF THE POSSIBILITY OF SUCH DAMAGES.
  */

/* double quarder */
#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <stack>

typedef char* Byte;

/*
 * Public enums for chess piece
 * color and type
 */
enum piece_color {white,black,empty };
enum piece_type {king,queen,rook,bishop,knight,pawn,none};

/*
 * Represents chess piece and dependencies.
 */
class Piece {

public:
	/* constructor for chess pieces which initiates it to board */
	Piece(piece_type chessPiece, piece_color chessPieceColor);

	/* copy constructor, will be used when piece is moved */
	Piece(const Piece& copy);
	Piece& operator=(const Piece& copy);

	std::stack<int> ValidMoves;
	bool Moved;
	bool Selected;
	piece_color PieceColor;
	piece_type PieceType;

	int Position;
	/* for position evaluation purposes */
	short PieceValue;
	short ActionValue;
	short AttackedValue;
	short DefendedValue;
private:
	static short calculate_value(piece_type pieceType);
	static short calculate_action_value(piece_type pieceType);
};
#endif