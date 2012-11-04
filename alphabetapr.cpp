//
//  alphabetapr.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

hash_table_t alphabeta_table;

int alphabeta(state_t state, int depth, int alpha, int beta, bool player) {
    hash_table_t::iterator it = alphabeta_table.find(state);
    
    if (it != alphabeta_table.end())
        return (it->second).val;
    
	if (depth == 0 || state.terminal()) {
        alphabeta_table.insert(make_pair(state, stored_info_t(state.value())));
		return state.value();
    }
	
    std::vector<state_t> children = state.getChildren(player);
    
	if (player == MAXPLAYER) {
        for (int i = 0; i != children.size(); ++i) {
            alpha = MAX(alpha, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha)
                break;
        }
        
        alphabeta_table.insert(make_pair(state, stored_info_t(alpha)));
        return alpha;
        
	} else {
        for (int i = 0; i != children.size(); ++i) {
            beta = MIN(beta, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha)
                break;
        }
        
        alphabeta_table.insert(make_pair(state, stored_info_t(beta)));
        return beta;
	}
}

int alphabeta(state_t state, int depth, bool player) {
    return alphabeta(state, depth, INT_MIN, INT_MAX, player);
}
