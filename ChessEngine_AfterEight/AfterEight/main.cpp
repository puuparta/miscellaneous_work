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

/* TESTER */
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "piece.h"
#include "square.h"
#include "board.h"

#define    hashfEXACT   0
#define    hashfALPHA   1
#define    hashfBETA    2

typedef long long U64;



/*
 * Hash element for transposition table
 */
typedef struct tagHASHE {
    U64 key;
    int depth;
    int flags;
    int value;
    int best;
}   HASHE;

/*
 * Zobrist key random generator
 */
U64 rand64(void)
{
    return rand() ^ ((U64)rand() << 15) ^ ((U64)rand() << 30) ^
        ((U64)rand() << 45) ^ ((U64)rand() << 60);
}

/*
 * Zobrist random keytable
 */
U64 zobrist[25][3][64];

/*
You take the key for the position, 
modulo it by the number of elements in your table, 
and that's the hash element that corresponds to this position.  
Since many positions are apt to map to the same element in the hash table, 
the table elements contain a verification value, which can be used to make 
sure that the element in the table is the one that you are trying to find.  
An obvious verification value is the full 64-bit key, so that is the first 
field in the example above.
*/


  // generic template
  template <typename numT>
  struct float_traits { };

  template<>
  struct float_traits<float> {
    typedef float float_type;
    enum { max_exponent = 200 };
    static inline float_type epsilon() { return 100; }
  };
  
  template<>
  struct float_traits<double> {
    typedef double float_type;
    enum { max_exponent = 100 };
    static inline float_type epsilon() { return 50; }
  };

    template <typename numT>
  class matrix {
    public:
      typedef numT num_type;
      typedef float_traits<num_type> traits_type;
      inline num_type epsilon() { return traits_type::epsilon(); }
  };

/*
 * Main sis‰lt‰‰ toistaiseksi erilaisia kokeiluja. Ei viel‰ toimiva engine.
 */
int main(char* args[]) 
{

	matrix<double> a;
	matrix<float> b;
	std::cout << a.epsilon() << std::endl;
	std::cout << b.epsilon();

	// yksi l‰hetti ruudulla. Good start.
	Piece *bishop = new Piece(piece_type::bishop,piece_color::white);
	/*Square *square;
	square->piece = bishop;
*/
	Board *board = new Board();
	board->SetBoard("8/8/8/8/8/7k/8/1P1P1p1r w - Kk 1 39");


	system("pause");
	//std::vector<int koe;



	// generoidaan zobrist random keytable
	zobrist[1][1][1] = rand64();

	HASHE hash_table[64];
	int movetable[64];
	HASHE hash;
	hash.best = 38;
	hash.key= zobrist[1][1][1];
	hash_table[5] = hash;

	//HASHE *phashe = &hash_table[zobrist[1][1][1] % 64];

	long ZobristKey = hash.key; // zobristkey haetaan oikeasti positio indeksist‰ constant 64 array randomluvuilla
	int pos = ZobristKey % sizeof(movetable);

    //HASHE * phashe = &hash_table[ZobristKey() % TableSize()];
    /*int pos = (int)(key % (ulong)table.Length);
	
		public ulong ZobristKey
		{
			get
			{
				return myZobristKeys[myMemoryIndex];
			}
		}

	*/

	/*
	To create a zobrist key for a position, you set your key to zero, 
	then you go find every piece on the board, and 
	XOR (via the "^" operator) "zobrist[pc][co][sq]" into your key.
	*/


	//int index = -8;
	//if (!(index & 0x40))
}