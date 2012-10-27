//
//  minmax.h
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#ifndef __Othello__minmax__
#define __Othello__minmax__

#include <limits>
#include "othello_cut.h"

// Minmax (Negamax) algorithm
int minmax(state_t node, int depth, bool color);

#endif /* defined(__Othello__minmax__) */
