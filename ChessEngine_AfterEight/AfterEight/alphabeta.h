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

#ifndef ALPHABETA_H
#define ALPHABETA_H

#include "transposition.h"

//TODO: move implementation to alphabeta.cpp
int AlphaBeta(int depth, int alpha, int beta)
{
    int hashf = hashfALPHA;
 
    if ((val = ProbeHash(depth, alpha, beta)) != valUNKNOWN)
        return val;
    if (depth == 0) {
        val = Evaluate();
        RecordHash(depth, val, hashfEXACT);
        return val;
    }
    GenerateLegalMoves();
    while (MovesLeft()) {
        MakeNextMove();
        val = -AlphaBeta(depth - 1, -beta, -alpha);
        UnmakeMove();
        if (val >= beta) {
            RecordHash(depth, beta, hashfBETA);
            return beta;
        }
        if (val > alpha) {
            hashf = hashfEXACT;
            alpha = val;
        }
    }
    RecordHash(depth, alpha, hashf);
    return alpha;
}

int ProbeHash(int depth, int alpha, int beta)
{
    HASHE * phashe = &hash_table[ZobristKey() % TableSize()];
 
    if (phashe->key == ZobristKey()) {
        if (phashe->depth >= depth) {
            if (phashe->flags == hashfEXACT)
                return phashe->val;
            if ((phashe->flags == hashfALPHA) &&
                (phashe->val <= alpha))
                return alpha;
            if ((phashe->flags == hashfBETA) &&
                (phashe->val >= beta))
                return beta;
        }
        RememberBestMove();
    }
    return valUNKNOWN;
}
 
void RecordHash(int depth, int val, int hashf)
{
    HASHE * phashe = &hash_table[ZobristKey() % TableSize()];
 
    phashe->key = ZobristKey();
    phashe->best = BestMove();
    phashe->val = val;
    phashe->hashf = hashf;
    phashe->depth = depth;
}

#endif

