//
//  minmax.cpp
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#include "minmax.h"

int minmax(state_t node, int depth, bool color) {
    if (depth == 0 || node.terminal())
        return node.value();
    
    int alpha = INT_MIN;
    
    for (int pos = 0; pos < DIM; ++pos) {
        if (color && node.is_black_move(pos))
            alpha = MAX(alpha, -minmax(node.black_move(pos), depth - 1, !color));
        else if (!color && node.is_white_move(pos))
            alpha = MAX(alpha, -minmax(node.white_move(pos), depth - 1, !color));
    }
    return alpha;
}