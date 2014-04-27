

#pragma once
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

#ifndef MOVEGEN_H
#define MOVEGEN_H

#include "board.h"


class Movegen
{
public:
	void AttachBoard(Board *board);
	void GenerateAllValidMoves(Board *board);
	void MovePiece(Piece *piece);
private:
	bool isEmptySquare(Piece *p, int pos);
	bool isOwn(Piece *p, int pos);
	bool isEnemy(Piece *p, int pos);
	void validMovesBishop(Piece *p);
	void validMovesRook(Piece *p);
	Board *board;
	Square Squares[64];
};

#endif