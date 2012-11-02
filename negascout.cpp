//
//  negascout.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

int negaMax(state_t state, int depth, int alpha, int beta, bool player) {
    if (state.terminal() || depth == 0)
        return state.value();
    
    std::vector<state_t> children = state.getChildren(player);
    int m = MAX(INT_MIN, negaMin(children[0], depth - 1, alpha, beta, !player));
    
    if (m >= beta)
        return m;
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMin(children[i], depth - 1, m, m + 1, !player);
        
        if (score > m)
            m = (score >= beta) ? score : negaMin(children[i], depth - 1, score, beta, !player);
        
        if (m >= beta)
            return m;
    }
    
    return m;
}

int negaMin(state_t state, int depth, int alpha, int beta, bool player) {
    if (state.terminal() || depth == 0)
        return state.value();
	
    std::vector<state_t> children = state.getChildren(player);
    int m = MIN(INT_MAX, negaMax(children[0], depth - 1, alpha, beta, !player));
    
    if (m <= alpha)
        return m;
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMax(children[i], depth - 1, m, m + 1, !player);
        
        if (score <= m)
            m = (score <= alpha) ? score : negaMax(children[i], depth - 1, alpha, score, !player);
        
        if (m <= alpha)
            return m;
    }
    
    return m;
}

int negascout(state_t state, int depth, bool player) {
    if (player == MAXPLAYER)
        return negaMax(state, depth, INT_MIN, INT_MAX, player);
    else
        return negaMin(state, depth, INT_MIN, INT_MAX, player);
}
