//
//  alphabetapr.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

int alphabeta(state_t state, int depth, int alpha, int beta, bool player) {
	if (depth == 0 || state.terminal())
		return state.value();
	
    std::vector<state_t> children = state.getChildren(player);
    
	if (player == MAXPLAYER) {
        for (int i = 0; i != children.size(); ++i) {
            alpha = MAX(alpha, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha)
                break;
        }
        
        return alpha;
        
	} else {
        for (int i = 0; i != children.size(); ++i) {
            beta = MIN(beta, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha)
                break;
        }
        
        return beta;
	}
}

int alphabeta(state_t state, int depth, bool player) {
    return alphabeta(state, depth, -100000, 100000, player);
}
