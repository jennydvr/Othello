//
//  algorithms.h
//  Othello
//
//  Created by Jenny Valdez on 01/11/12.
//
//

#ifndef __Othello__algorithms__
#define __Othello__algorithms__

#include <climits>
#include "othello_cut.h"

extern bool MAXPLAYER;

// Minimax (Negamax) algorithm
int minimax(state_t node, int depth, bool color);

// Alpha-beta pruning algorithm
int alphabeta(state_t state, int d, int alpha, int beta, bool color);

// Negascout algorithm
int negascout(state_t node, int depth, int alpha, int beta, bool color);

#endif /* defined(__Othello__algorithms__) */
