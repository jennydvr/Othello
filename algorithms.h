//
//  algorithms.h
//  Othello
//
//  Created by Jenny Valdez on 01/11/12.
//
//

#ifndef __Othello__algorithms__
#define __Othello__algorithms__

#define MAXPLAYER true

#include <climits>
#include "othello_cut.h"

int negaMax(state_t state, int depth, int alpha, int beta, bool player);
int negaMin(state_t state, int depth, int alpha, int beta, bool player);

int maxValue(state_t state, int depth, bool player);
int minValue(state_t state, int depth, bool player);

// Minimax (Negamax) algorithm
int minimax(state_t state, int depth, bool player);

// Alpha-beta pruning algorithm
int alphabeta(state_t state, int depth, bool player);

// Negascout algorithm
int negascout(state_t state, int depth, bool player);

#endif /* defined(__Othello__algorithms__) */
