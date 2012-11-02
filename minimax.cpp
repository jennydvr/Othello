//
//  minimax.cpp
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#include "algorithms.h"

int minimax(state_t node, int depth, bool color) {
    if (depth == 0 || node.terminal())
        return node.value();
    
    int alpha = INT_MIN;
    std::vector<state_t> children = node.getChildren(color);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MAX(alpha, -minimax(children[i], depth -1, !color));
    
    return alpha;
}
