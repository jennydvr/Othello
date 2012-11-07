//
//  alphabetapr.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

hash_table_t alphabeta_table;
unsigned long int alphabeta_expanded;

int alphabeta(state_t state, int depth, int alpha, int beta, bool player) {
    ++alphabeta_expanded;
    
    // Check table
    hash_table_t::iterator it = alphabeta_table.find(state);
    if (it != alphabeta_table.end() && (it->second).depth >= depth) {
        int value = (it->second).val;
        int type = (it->second).type;

        if (type == 1)
            return value;
        else if (type == 0)
            alpha = MAX(value,alpha);
        else if (type == 2)
            beta = MIN(beta,value);
        if (alpha >= beta)
            return value;
    }

    // Execute algorithm
    if (depth == 0 || state.terminal())
        return state.value();
    
    std::vector<state_t> children = state.getChildren(player);
    int score, a, b;
    if (player == MAXPLAYER) {
        score = INT_MIN;
        a = alpha;	// storing the original
        
        for (int i = 0; i != children.size() && score < beta; ++i) { //score inside limits
            score = MAX(score, alphabeta(children[i], depth-1, a, beta, !player));
            a = max(a, score);
        }
    }
    else {
        score = INT_MAX;
        b = beta;
         
        for (int i = 0; i != children.size() && score > alpha; ++i) { // score inside limits
            score = MIN(score, alphabeta(children[i], depth-1, alpha, b, !player));
            b = MIN(score, b);
        }

	}
    
    // Before returning, check if can add something to the table
    if (score <= alpha) //fail-low, score <= alpha, gives us an upper bound
        alphabeta_table.insert(make_pair(state, stored_info_t(score, depth, 2)));
    
    if (score > alpha && score < beta) //exact min max value
        alphabeta_table.insert(make_pair(state, stored_info_t(score, depth, 1)));
    
    if (score >= beta) //fail-high, gives us a lower bound to the exact minmax value
        alphabeta_table.insert(make_pair(state, stored_info_t(score, depth, 0)));
    
	return score;
}

int alphabeta(state_t state, int depth, bool player) {
    alphabeta_expanded = 0;
    return alphabeta(state, depth, INT_MIN, INT_MAX, player);
}
