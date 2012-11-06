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
    int value, d, type;
    
    if (it != negascout_table.end()) {
        value = (it->second).val; 
        d = (it->second).depth;
        type = (it->second).type;
        if (d >= depth) {
            if (type == 1)
                return value;
            else if (type == 0)  // Reducing windows
                alpha = MAX(alpha,value);
            else if(type == 2)
                beta = MIN(beta,value);
            if (alpha >= beta) // Null window
                return alpha;	
        }
    }
    
    if (state.terminal() || depth == 0) {
        if (state.value() <= alpha)
            type = 0;
        else if (state.value() >= beta)
            type = 2;
        else
            type = 1;
        negascout_table.insert(make_pair(state, stored_info_t(state.value(),depth,type)));
        return state.value();
    }
    
    std::vector<state_t> children = state.getChildren(player);
    int m = MAX(INT_MIN, negaMin(children[0], depth - 1, alpha, beta, !player));
    
    if (m >= beta) {
        //has the best value
        negascout_table.insert(make_pair(state, stored_info_t(m,depth)));
        return m;
    }
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMin(children[i], depth - 1, m, m + 1, !player);
        
        if (score > m) {
            // min is greater than current value, so its a lower bound
            negascout_table.insert(make_pair(state, stored_info_t(m,depth,0)));        
            if (score >= beta) {
                m = score;
            } else
                negaMin(children[i], depth - 1, score, beta, !player);
        }
        
        if (m >= beta) {
            // Has the best value
            negascout_table.insert(make_pair(state, stored_info_t(m,depth)));
            return m;
        }

        negascout_table.insert(make_pair(state, stored_info_t(score,depth,0)));
    }
    
    negascout_table.insert(make_pair(state, stored_info_t(m,depth,2)));
    return m;
}



int negaMin(state_t state, int depth, int alpha, int beta, bool player) {
    hash_table_t::iterator it = negascout_table.find(state);
    int value, d, type;
    
    if (it != negascout_table.end()) {
        value = (it->second).val; 
        d = (it->second).depth;
        type = (it->second).type;
        if (d >= depth) {
            if (type == 1)
                return value;
            else if (type == 0)
                alpha = MAX(alpha,value);
            else if(type == 2)
                beta = MIN(beta,value);
            if (alpha >= beta)
                return alpha;	
        }
    }
    
    if (state.terminal() || depth == 0) {
        if (state.value() <= alpha)
            type = 0;
        else if (state.value() >= beta)
            type = 2;
        else
            type = 1;
        negascout_table.insert(make_pair(state, stored_info_t(state.value(),depth,type)));
        return state.value();
    }
	
    std::vector<state_t> children = state.getChildren(player);
    int m = MIN(INT_MAX, negaMax(children[0], depth - 1, alpha, beta, !player));
    
    if (m <= alpha) {
       negascout_table.insert(make_pair(state, stored_info_t(m,depth)));
        return m;
    }
    
    for (int i = 1; i != children.size(); ++i) {
        int score = negaMax(children[i], depth - 1, m, m + 1, !player);
        
        if (score <= m) {
            if (score <= alpha) {
                m = score;
                //	negascout_table.insert(make_pair(state, stored_info_t(m,depth,0)));
            } else
                negaMax(children[i], depth - 1, alpha, score, !player);
            }
            if (m <= alpha) {
                negascout_table.insert(make_pair(state, stored_info_t(m,depth)));
                return m;
            }
        negascout_table.insert(make_pair(state, stored_info_t(score,depth,0)));
        }
    
    negascout_table.insert(make_pair(state, stored_info_t(m,depth,0)));
    return m;
}

int negascout(state_t state, int depth, bool player) {
    if (player == MAXPLAYER)
        return negaMax(state, depth, INT_MIN, INT_MAX, player);
    else
        return negaMin(state, depth, INT_MIN, INT_MAX, player);
}
