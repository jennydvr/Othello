// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 10/23/12
// Modified by:

//#include "othello_cut.h" // won't work correctly until .h is fixed!
//#include "minmax.h"
#include "negascout.h"
#include <fstream>
using namespace std;

/* En la variacion principal hay 33 profundidades
 * incluyendo -1
 */

int mains(int argc, const char **argv) {
    state_t state;
//    cout << "Principal variation:" << endl;
   if( argc > 1 ) {
      int d = atoi(argv[1]); //depth

      for (int i = 0; i != (33-d); ++i){
        bool player = i % 2 == 0; // black moves first!
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
        << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
        << endl;
        cout << "VALUE " << state.value() << endl;
        state = state.move(player, pos);

       cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }

   // Ahora tenemos en state el ultimo tablero
   // hasta la altura d
   
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
    
   		cout << "value initital state : " << state.value() << endl;
   		
   		bool blacks;
   		if (d < 3){ 
   			 blacks = d % 2 != 0; 
   		}
   		else{ //Tengo un rollo despues de 3 porque los negros pasan! (pos 36)
   			blacks = d % 2 == 0;
   		}
   		clock_t tStart = clock();   
        int nega = negascout(state, d, -1000, 1000, blacks);
        double tEnd = (clock() - tStart)/(double)CLOCKS_PER_SEC;
//        
        cout << "Negascout :" <<  endl;
        cout << "   value : " << -nega << endl; // No se pero sale al reves el signo, tengo que revisar
        printf("    tiempo: %.20lf \n\n", tEnd);
        cout << endl << state;
    //}
   }
    return 0;
}

