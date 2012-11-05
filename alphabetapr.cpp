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
    int value, type, d;
   if (it != alphabeta_table.end()){
	value = (it->second).val;
	type = (it->second).type;
        d = (it->second).depth;

	if (d >= depth){
	  if (type == 1)
		return value;
	else if (type == 0)
	  alpha = MAX(value,alpha);
	else if (type == 2)
		beta = MIN(beta,value);		
	if (alpha >= beta)
		return value;     	
	}
    }

    if (depth == 0 || state.terminal()) {
	if (state.value() <= alpha)
		type = 0;
	else if (state.value() >= beta)
		type = 2;
	else 
		type = 1;
	alphabeta_table.insert(make_pair(state, stored_info_t(state.value(),depth,type)));

	return state.value();
	}
	
    std::vector<state_t> children = state.getChildren(player);
    
	if (player == MAXPLAYER) {
        for (int i = 0; i != children.size(); ++i) {
            alpha = MAX(alpha, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha) //  beta <= valor uppper bound
                break;
	  alphabeta_table.insert(make_pair(state, stored_info_t(alpha,depth,0)));
        }
        
        alphabeta_table.insert(make_pair(state, stored_info_t(alpha,depth,2)));
        return alpha;
        
	} else {
        for (int i = 0; i != children.size(); ++i) {
            beta = MIN(beta, alphabeta(children[i], depth-1, alpha, beta, !player));
            
            if (beta <= alpha)
                break;
	alphabeta_table.insert(make_pair(state, stored_info_t(alpha,depth,0)));
        }
        
        alphabeta_table.insert(make_pair(state, stored_info_t(beta,depth,2)));
        return beta;
	}
   
}

int alphabeta(state_t state, int depth, bool player) {
    return alphabeta(state, depth, INT_MIN, INT_MAX, player);
}
