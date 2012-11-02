//
//  negascout.cpp
//  Othello
//
//  Created by Grace Gimon on 28/10/12.
//
//

#include "algorithms.h"

int negascout(state_t node, int depth, int alpha, int beta, bool color){
    if (node.terminal() || depth == 0) {
	//	   cout << node;
        return node.value();
    }
	   
    int b = beta;  // initial window (-beta,-alpha)
    
    std::vector<state_t> children = node.getChildren(color);
    
    for (int i = 0; i != children.size(); ++i) {
//           cout << "child " << endl << child;
//           cout << endl;
        
        int a = -negascout(children[i], depth-1, -b, -alpha, !color);
  //  	   cout << "a, b, alpha " << a << " " << b <<" " <<alpha << endl;
        if (a > alpha)
            alpha = a;
        if (alpha >= beta)
            return alpha; //Beta pruning
        if (alpha >= b) {
            alpha = -negascout(children[i], depth-1, -beta, -alpha, !color);
            if (alpha >= beta)
                return alpha;
        }
        b = alpha + 1;
   	//       cout << "alpha " << alpha << endl;
    }
    
    return alpha;
}
