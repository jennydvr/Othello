// Game of Othello -- Example of main
// Universidad Simon Bolivar, 2012.
// Author: Blai Bonet
// Last Revision: 10/23/12
// Modified by:


#include "algorithms.h"
#include <fstream>

using namespace std;

vector<state_t> states;

void test(int alg) {
    int depth = 1;
    bool player = false;
    
    clock_t tStart;
    int ans;
    double tEnd;
    
    cout << "FORMAT" << endl;
    cout << "    <algorithm> = <value>  -  <hash.size>  -  <expanded nodes>  -  <time>\n\n";
    
    
    while (!states.empty()) {
        //cout << "ply = " << states.size() - 1 << endl;
        cout << states.size() - 1 << " ";
        
        if (alg == 0)
        {
            // Calculate alphabeta
            tStart = clock();
            ans = alphabeta(states.back(), depth, player);
            tEnd = (clock() - tStart)/(double)CLOCKS_PER_SEC;
            
            /*
            cout << "    a = " << ans << "  -  ";
            cout << alphabeta_table.size() << "  -  ";
            cout << alphabeta_expanded << "  -  ";
            printf("%.5lf\n", tEnd);
            */
            
            cout << ans << " ";
            cout << alphabeta_table.size() << " ";
            cout << alphabeta_expanded << " ";
            printf("%.5lf\n", tEnd);
            
        }
        else if (alg == 1) // Calculate negascout
        {        
            tStart = clock();
            ans = negascout(states.back(), depth, player);
            tEnd = (clock() - tStart)/(double)CLOCKS_PER_SEC;
            
            /*
            cout << "    n = " << ans << "  -  ";
            cout << negascout_table.size() << "  -  ";
            cout << negascout_expanded << "  -  ";
            printf("%.5lf\n", tEnd);
             */
            cout << ans << " ";
            cout << negascout_table.size() << " ";
            cout << negascout_expanded << " ";
            printf("%.5lf\n", tEnd);
            
        }
        else if (alg == 2) // Calculate minimax
        {
            tStart = clock();
            ans = minimax(states.back(), depth, player);
            tEnd = (clock() - tStart)/(double)CLOCKS_PER_SEC;
            
            /*
            cout << "    m = " << ans << "  -  ";
            cout << minimax_table.size() << "  -  ";
            cout << minimax_expanded << "  -  ";
            printf("%.5lf\n", tEnd);
             */
            cout << ans << " ";
            cout << minimax_table.size() << " ";
            cout << minimax_expanded << " ";
            printf("%.5lf\n", tEnd);
        }

        ++depth;
        states.pop_back();
        player = !player;
    }
}

int main(int argc, const char **argv) {
    state_t state;
    
    //cout << "Principal variation:" << endl;
    for (int i = 0; PV[i] != -1; ++i) {
        bool player = i % 2 == 0; // black moves first!
        
        int pos = PV[i];
        /*
        cout << state;
        cout << (player ? "Black" : "White")
        << " moves at pos = " << pos << (pos == 36 ? " (pass)" : "")
        << endl;
        */
        state = state.move(player, pos);
        /*
        cout << "Board after " << i+1 << (i == 0 ? " ply:" : " plies:") << endl;
         */
        states.push_back(state);
    }
    
    /*
    cout << state;
    cout << "Value of the game = " << state.value() << endl;
    cout << "#bits per state = " << sizeof(state) * 8 << endl;
    */
    
    int algoritmo = -1;
    if( argc > 1 )
    {
        algoritmo = atoi(argv[1]);
        //0: Alpha-Beta | 1: NegaScout | 2: MinMax 
        /*if (algoritmo != 0 && algoritmo != 1 && algoritmo != 2)
            return 0;*/
        if (algoritmo == 0)
            cout << "[Se esta usando el algoritmo Alpha-Beta Pruning]" << endl;
        else if (algoritmo == 1)
            cout << "[Se esta usando el algoritmo NegaScout]" << endl;
        else if (algoritmo == 2)
            cout << "[Se esta usando el algoritmo MinMax]" << endl;
        else
        {
            cout << "0: Alpha-Beta | 1: NegaScout | 2: MinMax" << endl;
            return -1;
        }
        cout << endl;
    }
    else
    {
        cout << "Faltan argumentos!" << endl;
        return 0;
    }

    test(algoritmo);
    
    /*if( argc > 1 ) {
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
    }*/
    
    return 0;
}

