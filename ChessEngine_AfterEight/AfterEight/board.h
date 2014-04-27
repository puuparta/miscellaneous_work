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

#pragma once
#ifndef BOARD_H
#define BOARD_H

#include <string>
#include "square.h"

class Board
{
public:
	Square Squares[64];
	double Score;
	bool StartGamePhase;
	bool MiddleGamePhase;
	bool EndGamePhase;
	bool BlackChecks;
	bool WhiteChecks;
	bool WhiteMove;
	bool BlackMove;
	bool WhiteKingSideCastle;
	bool WhiteQueenSideCastle;
	bool BlackKingSideCastle;
	bool BlackQueenSideCastle;
	int EnPassantSquareIndex;
	int FullMoveCount;
	int FiftyMoveDrawCount;

	Board();
	Board(std::string fen);
	void SetBoard(std::string fen);
};
  
#endif