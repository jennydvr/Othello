//
//  negascout.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//
#include "negascout.h"
using namespace std;
int negascout(state_t node, int depth, int alpha, int beta, bool color){
	   if (node.terminal() || depth==0)
	        return node.value();
	   
	    int b = beta ;  // initial window (-beta,-alpha)
	    for( int pos = 0; pos < DIM; ++pos ) {
	    	state_t child;
           if(color && node.is_black_move(pos)){
        	   child = node.black_move(pos);
           }
           else if (!color && node.is_white_move(pos)){
        	   child = node.white_move(pos);
           }
           else{
        	   continue;
           }
//           cout << "child " << endl << child;
//           cout << endl;
    	   int a = -negascout (child, depth-1, -b, -alpha, !color);
  //  	   cout << "a, b, alpha " << a << " " << b <<" " <<alpha << endl;
   	       if (a>alpha) 
   	    	   alpha = a;
   	       if (alpha>=beta)
   	           return alpha; //Beta pruning
   	       if (alpha>=b){
   	          alpha = -negascout(child, depth-1, -beta, -alpha, !color); 
   	          if (alpha>=beta)
   	             return alpha; 
   	       }
   	       b = alpha+1;   
   	//       cout << "alpha " << alpha << endl;
	    }
	   return alpha;
}
