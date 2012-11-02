//
//  minimax.cpp
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#include "algorithms.h"

int factor = -1;

int maxValue(state_t state, int depth, bool player) {
    if (depth == 0 || state.terminal())
        return state.value();
    
    int alpha = INT_MIN;
    std::vector<state_t> children = state.getChildren(player);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MAX(alpha, minValue(children[i], depth - 1, !player));
    
    return alpha;
}

int minValue(state_t state, int depth, bool player) {
    if (depth == 0 || state.terminal())
        return state.value();
    
    int alpha = INT_MAX;
    std::vector<state_t> children = state.getChildren(player);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MIN(alpha, maxValue(children[i], depth - 1, !player));
    
    return alpha;
}

int negamax(state_t state, int depth, bool player) {
    if (depth == 0 || state.terminal())
        return state.value();
    
    int alpha = INT_MIN;
    std::vector<state_t> children = state.getChildren(player);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MAX(alpha, -negamax(children[i], depth - 1, !player));
    
    return alpha;
}

int minimax(state_t state, int depth, bool player) {
    if (player == MAXPLAYER)
        return maxValue(state, depth, player);
    else
        return minValue(state, depth, player);
}
