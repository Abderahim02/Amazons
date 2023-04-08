#include <stdio.h>
#include "moteur.h"
#include "grid.h"

#ifndef LENGHT
  #define LENGHT 8
#endif

// struct move_t {
//   unsigned int queen_src;
//   unsigned int queen_dst;
//   unsigned int arrow_dst;
// };

void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens){
    int queen_number = 4*(LENGHT/10 + 1 );
    for(int  i =0; i < queen_number ; ++i ){
        if ( queens[i] == move.queen_src ){
            printf("found");
            queens[i] = move.queen_dst;
            break;
        }
    }
    unsigned int pos_i = move.arrow_dst / LENGHT ;
    unsigned int pos_j = move.arrow_dst %LENGHT ;
    gsl_spmatrix_uint_set(graph->t,  pos_i ,pos_j, -1 );
    gsl_spmatrix_uint_set(graph->t, pos_j, pos_i, -1 );

}



