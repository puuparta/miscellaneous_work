#ifndef _ENGINE_H
#define _ENGINE_H

#include <string>
#include "board.h"
#include "move.h"

class Engine
{
public:
	Board board;
	Move movetable;
	void make_move_with_fen(std::string fen);
	void make_move(std::string move);
	void init();
};


#endif