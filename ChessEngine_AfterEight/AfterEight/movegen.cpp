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


#include "movegen.h"




void Movegen::AttachBoard(Board *board)
{
	this->board = board;
}

void Movegen::GenerateAllValidMoves(Board *board)
{        
    for (short i = 0; i < 64; i++)
    {
		if(board->Squares[i].piece->PieceType!=piece_type::none)
            MovePiece(board->Squares[i].piece);
    }
}

void Movegen::MovePiece(Piece *piece)
{
	switch (piece->PieceType)
    {
		case piece_type::bishop:
            validMovesBishop(piece);
            break;
		case piece_type::rook:
            validMovesRook(piece);
            break;
        default:
            break;
    }
}

bool Movegen::isEmptySquare(Piece *p, int pos)
{
    return true;
    if (pos < 0 || pos > 63) return false;
}

bool Movegen::isOwn(Piece *p, int pos)
{
	return this->board->Squares[pos].piece->PieceColor == p->PieceColor;
}

bool Movegen::isEnemy(Piece *p, int pos)
{
	return this->board->Squares[pos].piece->PieceColor != p->PieceColor && this->board->Squares[pos].piece->PieceColor != piece_color::empty;
}

void Movegen::validMovesBishop(Piece *p)
{

}

void Movegen::validMovesRook(Piece *p)
{
	int pos = p->Position;

	// north
	while (pos - 8 > -1)
	{
		pos -= 8;
		if(isOwn(p,pos)) break;
		p->ValidMoves.push(pos);
		if (isEnemy(p, pos)) break;
	}

	pos = p->Position; //restart from originalpos

	// south
	while (pos + 8 < 64)
	{
		pos += 8;
		if (isOwn(p, pos)) break;
		p->ValidMoves.push(pos);
		if (isEnemy(p, pos)) break;
	}
	pos = p->Position;
	// west
	while ((pos % 8) > 0)
	{
		pos--;
		if (isOwn(p, pos)) break;
		p->ValidMoves.push(pos);
		if (isEnemy(p, pos)) break;
	}
	pos = p->Position;
	// east
	while ((7 - (pos % 8)) > 0)
	{
		pos++;
		if (isOwn(p, pos)) break;
		p->ValidMoves.push(pos);
		if (isEnemy(p, pos)) break;
	}

}
/*
        void ValidMovesBishop(Piece p)
        {
            int pos = p.CurrentPos;
            /*
            //southwest
            if (pos + 7 < 64 && pos % 8 > 0 && empty_op(p,pos+7)) p.ValidMoves.Push(pos + 7);

            //southeast
            if (pos + 9 < 64 && pos % 8 < 7 && empty_op(p,pos+9)) p.ValidMoves.Push(pos + 9);

            //northeast
            if (pos - 7 > -1 && pos % 8 < 7 && empty_op(p,pos-7)) p.ValidMoves.Push(pos - 7);

            //northwest
            if (pos - 9 > -1 && pos % 8 > 0 && empty_op(p,pos-9)) p.ValidMoves.Push(pos - 9);
            */
/*
            // kulku northeast
            while(
        }

        void ValidMovesRook(Piece p)
        {
            int pos = p.CurrentPos;

            // north
            while (pos - 8 > -1)
            {
                pos -= 8;
                if(isOwn(p,pos)) break;
                p.ValidMoves.Push(pos);
                if (isEnemy(p, pos)) break;
            }
            pos = p.CurrentPos;
            // south
            while (pos + 8 < 64)
            {
                pos += 8;
                if (isOwn(p, pos)) break;
                p.ValidMoves.Push(pos);
                if (isEnemy(p, pos)) break;
            }
            pos = p.CurrentPos;
            // west
            while ((pos % 8) > 0)
            {
                pos--;
                if (isOwn(p, pos)) break;
                p.ValidMoves.Push(pos);
                if (isEnemy(p, pos)) break;
            }
            pos = p.CurrentPos;
            // east
            while ((7 - (pos % 8)) > 0)
            {
                pos++;
                if (isOwn(p, pos)) break;
                p.ValidMoves.Push(pos);
                if (isEnemy(p, pos)) break;
            }
        }
*/
