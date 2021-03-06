//
//  algorithms.h
//  Othello
//
//  Created by Jenny Valdez on 01/11/12.
//
//

#ifndef __Othello__algorithms__
#define __Othello__algorithms__

#define MAXPLAYER true

#include <algorithm>
#include <climits>
#include "othello_cut.h"
#include <tr1/unordered_map>

using namespace std;

struct stored_info_t {
    int val;
    int depth;
    int type; // 0 lower, 1 exact, 2 upper
    
    stored_info_t() { };
    stored_info_t(int v, int d = 0, int t = 1) : val(v), depth(d), type(t) { }
};

struct hash_function_t : public tr1::hash<state_t> {
    size_t operator()(const state_t &state) const {
        return state.hash();
    }
};

class hash_table_t : public tr1::unordered_map<state_t, stored_info_t, hash_function_t> {
};

// Hash tables
extern hash_table_t alphabeta_table;
extern hash_table_t negascout_table;
extern hash_table_t minimax_table;

// Expanded nodes
extern unsigned long int alphabeta_expanded;
extern unsigned long int negascout_expanded;
extern unsigned long int minimax_expanded;

// Nodes in the principal variation
extern vector<state_t> states;

// Minimax (Negamax) algorithm
int minimax(state_t state, int depth, bool player);

// Alpha-beta pruning algorithm
int alphabeta(state_t state, int depth, bool player);

// Negascout algorithm
int negascout(state_t state, int depth, bool player);

#endif /* defined(__Othello__algorithms__) */
