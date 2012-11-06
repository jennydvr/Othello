//
//  minimax.cpp
//  Othello
//
//  Created by Jenny Valdez on 27/10/12.
//
//

#include "algorithms.h"

hash_table_t minimax_table;
int minimax_expanded;

int minValue(state_t state, int depth, bool player);

int maxValue(state_t state, int depth, bool player) {
    ++minimax_expanded;
    
    hash_table_t::iterator it = minimax_table.find(state);
    
    if (it != minimax_table.end())
        return (it->second).val;
    
    if (depth == 0 || state.terminal()) {
        minimax_table.insert(make_pair(state, stored_info_t(state.value())));
        return state.value();
    }
    
    int alpha = INT_MIN;
    std::vector<state_t> children = state.getChildren(player);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MAX(alpha, minValue(children[i], depth - 1, !player));
    
    minimax_table.insert(make_pair(state, stored_info_t(alpha)));
    return alpha;
}

int minValue(state_t state, int depth, bool player) {
    ++minimax_expanded;
    
    hash_table_t::iterator it = minimax_table.find(state);
    
    if (it != minimax_table.end())
        return (it->second).val;
    
    if (depth == 0 || state.terminal()) {
        minimax_table.insert(make_pair(state, stored_info_t(state.value())));
        return state.value();
    }
    
    int alpha = INT_MAX;
    std::vector<state_t> children = state.getChildren(player);
    
    for (int i = 0; i != children.size(); ++i)
        alpha = MIN(alpha, maxValue(children[i], depth - 1, !player));
    
    minimax_table.insert(make_pair(state, stored_info_t(alpha)));
    return alpha;
}

int minimax(state_t state, int depth, bool player) {
    minimax_expanded = 0;
    if (player == MAXPLAYER)
        return maxValue(state, depth, player);
    else
        return minValue(state, depth, player);
}
