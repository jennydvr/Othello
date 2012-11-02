// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 10/23/12
// Modified by:

//#include "othello_cut.h" // won't work correctly until .h is fixed!
//#include "minmax.h"
#include "algorithms.h"

using namespace std;

int main(int argc, const char **argv) {
    state_t state;
    
    cout << "Principal variation:" << endl;
    for( int i = 0; PV[i] != -1; ++i ) {
        bool player = i % 2 == 0; // black moves first!
        
        // PRUEBA
        MAXPLAYER = player;
        
        cout << minimax(state, 4, player) << " ";
        cout << alphabeta(state, 4, -10000, 10000, player) << " ";
        cout << negascout(state, 4, -10000, 10000, player) << endl;
        int x;
        cin >> x;
        // ENDL
        
        int pos = PV[i];
        cout << state;
        cout << (player ? "Black" : "White")
        << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
        << endl;
        state = state.move(player, pos);
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
    }
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
    
    if( argc > 1 ) {
        int n = atoi(argv[1]);
        cout << endl << "Apply " << n << " random movements at empty board:";
        state = state_t();
        for( int i = 0; i < n; ++i ) {
            bool player = i % 2 == 0; // black moves first
            int pos = state.get_random_move(player);
            state = state.move(player, pos);
            cout << " " << pos;
        }
        cout << endl << state;
    }
    
    return 0;
}

