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
    
    // Check table
    hash_table_t::iterator it = negascout_table.find(state);
    if (it != negascout_table.end() && (it->second).depth >= depth) {
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
    if (state.terminal() || depth == 0)
        return state.value();
    
    std::vector<state_t> children = state.getChildren(player);
    int score = MAX(INT_MIN, negaMin(children[0], depth - 1, alpha, beta, !player));
    
    if (score < beta)
        for (int i = 1; i != children.size(); ++i) {
            int value = negaMin(children[i], depth - 1, score, score + 1, !player);
        
            if (value > score)
                score = (value >= beta) ? value : negaMin(children[i], depth - 1, value, beta, !player);
        
            if (score >= beta)
                break;
        }
    
    // Before returning, check if can add something to the table
    if (score <= alpha) //fail-low, score <= alpha, gives us an upper bound
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 2)));
    
    if (score > alpha && score < beta) //exact min max value
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 1)));
    
    if (score >= beta) //fail-high, gives us a lower bound to the exact minmax value
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 0)));
    
    return score;
}

int negaMin(state_t state, int depth, int alpha, int beta, bool player) {
    
    // Check table
    hash_table_t::iterator it = negascout_table.find(state);
    if (it != negascout_table.end() && (it->second).depth >= depth) {
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
    if (state.terminal() || depth == 0)
        return state.value();
	
    std::vector<state_t> children = state.getChildren(player);
    int score = MIN(INT_MAX, negaMax(children[0], depth - 1, alpha, beta, !player));
    
    if (score > alpha)
        for (int i = 1; i != children.size(); ++i) {
            int value = negaMax(children[i], depth - 1, score, score + 1, !player);
        
            if (value <= score)
                score = (value <= alpha) ? value : negaMax(children[i], depth - 1, alpha, value, !player);
        
            if (score <= alpha)
                break;
        }
    
    // Before returning, check if can add something to the table
    if (score <= alpha) //fail-low, score <= alpha, gives us an upper bound
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 2)));
    
    if (score > alpha && score < beta) //exact min max value
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 1)));
    
    if (score >= beta) //fail-high, gives us a lower bound to the exact minmax value
        negascout_table.insert(make_pair(state, stored_info_t(score, depth, 0)));
    
    return score;
}

int negascout(state_t state, int depth, bool player) {
    if (player == MAXPLAYER)
        return negaMax(state, depth, INT_MIN, INT_MAX, player);
    else
        return negaMin(state, depth, INT_MIN, INT_MAX, player);
}