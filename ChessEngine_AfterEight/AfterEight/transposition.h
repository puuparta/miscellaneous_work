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

#ifndef TRANSPOSITION_H
#define TRANSPOSITION_H

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
 * Zobrist table
 */
U64 zobrist[25][3][64];

//You take the key for the position, modulo it by the number of elements in your table, and that's the hash element that corresponds to this position.  Since many positions are apt to map to the same element in the hash table, the table elements contain a verification value, which can be used to make sure that the element in the table is the one that you are trying to find.  An obvious verification value is the full 64-bit key, so that is the first field in the example above.

#endif