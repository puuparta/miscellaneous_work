#include "engine.h"

void Engine::make_move_with_fen(std::string fen)
{
	board.set_fen(fen);
}

void Engine::make_move(std::string move)
{

}

void Engine::init()
{
	board.set_fen();
}