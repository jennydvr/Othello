//
//  minmax.cpp
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#include "minmax.h"

using namespace std;

vector<state_t> getChildren(state_t node, bool color) {
    vector<state_t> children;
    
    // Calculate all possible plies
    for (int pos = 0; pos < DIM; ++pos)
        if (color && node.is_black_move(pos))
            children.push_back(node.black_move(pos));
        else if (!color && node.is_white_move(pos))
            children.push_back(node.white_move(pos));
    
    // If there are none, pass
    if (children.empty())
        children.push_back(node);
    
    return children;
}

int minmax(state_t node, int depth, bool color) {
    if (depth == 0 || node.terminal())
        return node.value();
    
    int alpha = INT_MIN;
    vector<state_t> children = getChildren(node, color);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MAX(alpha, -minmax(children[i], depth -1, !color));
    
    return alpha;
}