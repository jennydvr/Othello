//
//  negascout.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

hash_table_t negascout_table;

int negaMin(state_t state, int depth, int alpha, int beta, bool player);

int negaMax(state_t state, int depth, int alpha, int beta, bool player) {
    hash_table_t::iterator it = negascout_table.find(state);
    
    if (it != negascout_table.end())
        return (it->second).val;
    
    if (state.terminal() || depth == 0) {
        negascout_table.insert(make_pair(state, stored_info_t(state.value())));
        return state.value();
    }
    
    std::vector<state_t> children = state.getChildren(player);
    int m = MAX(INT_MIN, negaMin(children[0], depth - 1, alpha, beta, !player));
    
    if (m >= beta) {
        negascout_table.insert(make_pair(state, stored_info_t(m)));
        return m;
    }
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMin(children[i], depth - 1, m, m + 1, !player);
        
        if (score > m)
            m = (score >= beta) ? score : negaMin(children[i], depth - 1, score, beta, !player);
        
        if (m >= beta) {
            negascout_table.insert(make_pair(state, stored_info_t(m)));
            return m;
        }
    }
    
    negascout_table.insert(make_pair(state, stored_info_t(m)));
    return m;
}

int negaMin(state_t state, int depth, int alpha, int beta, bool player) {
    hash_table_t::iterator it = negascout_table.find(state);
    
    if (it != negascout_table.end())
        return (it->second).val;
    
    if (state.terminal() || depth == 0) {
        negascout_table.insert(make_pair(state, stored_info_t(state.value())));
        return state.value();
    }
	
    std::vector<state_t> children = state.getChildren(player);
    int m = MIN(INT_MAX, negaMax(children[0], depth - 1, alpha, beta, !player));
    
    if (m <= alpha) {
        negascout_table.insert(make_pair(state, stored_info_t(m)));
        return m;
    }
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMax(children[i], depth - 1, m, m + 1, !player);
        
        if (score <= m)
            m = (score <= alpha) ? score : negaMax(children[i], depth - 1, alpha, score, !player);
        
        if (m <= alpha) {
            negascout_table.insert(make_pair(state, stored_info_t(m)));
            return m;
        }
    }
    
    negascout_table.insert(make_pair(state, stored_info_t(m)));
    return m;
}

int negascout(state_t state, int depth, bool player) {
    if (player == MAXPLAYER)
        return negaMax(state, depth, INT_MIN, INT_MAX, player);
    else
        return negaMin(state, depth, INT_MIN, INT_MAX, player);
}
