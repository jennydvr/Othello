//
//  alphabetapr.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

bool MAXPLAYER = true;

int alphabeta(state_t state, int d, int alpha, int beta, bool color){
	if (d == 0 || state.terminal())
		return state.value();
	
    std::vector<state_t> children = state.getChildren(color);
    
	if (color == MAXPLAYER) {
        for (int i = 0; i != children.size(); ++i) {
            alpha = MAX(alpha, alphabeta(children[i], d-1, alpha, beta, !color));
            
            if (beta <= alpha)
                break;
        }
        
        return alpha;
        
	} else {
        for (int i = 0; i != children.size(); ++i) {
            beta = MIN(beta, alphabeta(children[i], d-1, alpha, beta, !color));
            
            if (beta <= alpha)
                break;
        }
        
        return beta;
	}
}	
	