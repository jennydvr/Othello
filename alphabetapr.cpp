#define MAXPLAYER true
#include <climits>
#include "alphabetapr.h"

int alphabeta(state_t state, int d, int alpha, int beta, bool color){
	if (d == 0 || state.terminal())
		return state.value();
	
	if (color == MAXPLAYER){
		 for( int pos = 0; pos < DIM; ++pos ) {
			 if (state.is_black_move(pos)){
				 alpha = MAX(alpha, alphabeta(state.black_move(pos), d-1, alpha, beta, !color));
			 }
			 else{
				 continue;
			 }
		 if (beta <= alpha)
			 break;
		 return alpha;
		 }
	}
	else{
		for( int pos = 0; pos < DIM; ++pos ) {
			if (state.is_white_move(pos)){
				beta = MIN(beta, alphabeta(state.white_move(pos), d-1, alpha, beta, !color));
			}
			else{
				continue;
			}
		 if (beta <= alpha)
			 break;
		 return beta;	 
		}
	}
}
	
	