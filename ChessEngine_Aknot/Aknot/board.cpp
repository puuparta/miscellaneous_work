#include "board.h"
#include <sstream>


Board::Board()
{
	black_pawns=0x0;
	black_king=0x0;
	black_queens=0x0;
	black_bishops=0x0;
	black_knights=0x0;
	black_rooks=0x0;
	white_pawns=0x0;
	white_king=0x0;
	white_queens=0x0;
	white_bishops=0x0;
	white_knights=0x0;
	white_rooks=0x0;
}

void Board::set_to_board(Piece p, BITBOARD sq)
{
	if(p.t_hash()==get_t_hash(Type::p,Color::black)) {black_pawns|=sq;}
	if(p.t_hash()==get_t_hash(Type::b,Color::black)) {black_bishops|=sq;}
	if(p.t_hash()==get_t_hash(Type::k,Color::black)) {black_king=sq;}
	if(p.t_hash()==get_t_hash(Type::n,Color::black)) {black_knights|=sq;}
	if(p.t_hash()==get_t_hash(Type::q,Color::black)) {black_queens|=sq;}
	if(p.t_hash()==get_t_hash(Type::r,Color::black)) {black_rooks|=sq;}
	if(p.t_hash()==get_t_hash(Type::p,Color::white)) {white_pawns|=sq;}
	if(p.t_hash()==get_t_hash(Type::b,Color::white)) {white_bishops|=sq;}
	if(p.t_hash()==get_t_hash(Type::k,Color::white)) {white_king=sq;}
	if(p.t_hash()==get_t_hash(Type::n,Color::white)) {white_knights|=sq;}
	if(p.t_hash()==get_t_hash(Type::q,Color::white)) {white_queens|=sq;}
	if(p.t_hash()==get_t_hash(Type::r,Color::white)) {white_rooks|=sq;}
}

int Board::get_t_hash(Type t, Color c)
{
	return t|c; 
}

Piece Board::piece_from_token(char token)
{
	Piece p;
	if(token=='p') {p.type=Type::p;p.color=Color::black;p.moveBB=black_pawn;}
	if(token=='b') {p.type=Type::b;p.color=Color::black;p.moveBB=bishop;}
	if(token=='n') {p.type=Type::n;p.color=Color::black;p.moveBB=knight;}
	if(token=='r') {p.type=Type::r;p.color=Color::black;}
	if(token=='q') {p.type=Type::q;p.color=Color::black;}
	if(token=='k') {p.type=Type::k;p.color=Color::black;}
	if(token=='P') {p.type=Type::p;p.color=Color::white;}
	if(token=='B') {p.type=Type::b;p.color=Color::white;}
	if(token=='N') {p.type=Type::n;p.color=Color::white;}
	if(token=='R') {p.type=Type::r;p.color=Color::white;}
	if(token=='Q') {p.type=Type::q;p.color=Color::white;}
	if(token=='K') {p.type=Type::k;p.color=Color::white;}
	return p;
}

void Board::set_fen(std::string fen)
{

	std::istringstream ss(fen);
	char token;
	BITBOARD sq=0x0080000000000000;

	// loop until FEN's position delimeter
	while(ss.get(token) && token!=' ')
	{
		if(isdigit(token))
		{
			sq=sq<<(token - '0');
			continue;
		}

		// rank move
		if(token=='/')
		{
			sq=(sq>>16);
			continue;
		}

		// shift to left only if not at uint64 max. We never should go to zero
		if(sq<0x8000000000000000)
			sq=sq<<1;
		
		// if at the zero due to second rank change then add one because cannot change 0 with bitmoves.
		if(sq==0x0) sq=0x1;
		
		set_to_board(piece_from_token(token),sq);
	}
}

void Board::set_fen()
{
	
	std::string InitialFEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
	set_fen(InitialFEN);
}

