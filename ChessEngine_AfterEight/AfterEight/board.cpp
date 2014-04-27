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
#include "board.h"
#include "utils.h"

Board::Board()
{
	for (short i = 0; i < 64; i++){
		//Squares[i].piece = PieceSelector.Select(' ');
		//Squares[i].piece->Position = i;
	}
}

Board::Board(std::string fen)
{
	Board::Board();
	this->SetBoard(fen);
}

void Board::SetBoard(std::string fen)
{
	std::vector<std::string> rows;
	Utils::split(fen,"/",&rows);

	/* 
	 * index7 is last block of fen after char '/' 
	 * take the tail of it at check castling, en-passant and moves
	 */ 
	std::string index7 = rows.at(7);
	std::string tail = index7;
	tail = tail.substr(tail.find_first_of(" "),tail.length()-tail.find_first_of(" "));
	index7 = index7.replace(index7.find_first_of(" "),index7.length(),"");
	
	/* parse each characters in tail and store params */
	std::vector<std::string> tail_items;
	Utils::split(tail, " ", &tail_items);
	WhiteMove = tail_items.at(1).compare("w") ? true : false;
    BlackMove = !WhiteMove;
	int pos = tail_items.at(2).find_first_of("K");
	WhiteKingSideCastle = pos > -1 ? true : false;
    
	pos = tail_items.at(2).find_first_of("Q");
	WhiteQueenSideCastle = pos > -1 ? true : false;
    
	pos = tail_items.at(2).find_first_of("k");
	BlackKingSideCastle = pos > -1 ? true : false;
    
	pos = tail_items.at(2).find_first_of("q");
	BlackQueenSideCastle = pos > -1 ? true : false;

	/*
	string[] rows = fen.Split('/');
    string tail = rows[7].Substring(rows[7].IndexOf(" "), rows[7].Length - rows[7].IndexOf(" "));
    rows[7] = rows[7].Replace(tail, "");
    string[] tail_array = tail.Split(' ');
    WhiteMove = tail_array[1].ToLower().Equals("w") ? true : false;
    BlackMove = !WhiteMove;
    WhiteKingSideCastle = tail_array[2].IndexOf("K") > -1 ? true : false;
    WhiteQueenSideCastle = tail_array[2].IndexOf("Q") > -1 ? true : false;
    BlackKingSideCastle = tail_array[2].IndexOf("k") > -1 ? true : false;
    BlackQueenSideCastle = tail_array[2].IndexOf("q") > -1 ? true : false;
    EnPassantSquareIndex = tail_array[3] != "-" 
        ? "abcdefgh".IndexOf(tail_array[3][0]) 
        + 8*(8-Convert.ToInt32(tail_array[3][1].ToString())) 
        : -1;

    FiftyMoveDrawCount = Convert.ToInt32(tail_array[4]);
    FullMoveCount = Convert.ToInt32(tail_array[5]);
    int k = 0;
    for (int i = 0; i < rows.Length; i++)
    {
        k = 0;
        for (int j = 0; j < rows[i].Length; j++)
        {
            if ((int)rows[i][j] < 57)
            {
                k += Convert.ToInt32(rows[i][j].ToString())-1;
                continue;
            }
            
            Squares[i * 8 + j+k].Piece = PieceSelector.Select(rows[i][j]);
            Squares[i * 8 + j+k].Piece.CurrentPos = i * 8 + j+k;
        }
    }
	*/

}