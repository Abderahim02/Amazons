#include <stdio.h>
#include "moteur.h"
#include "grid.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx){
    for(int i=0; i < LENGHT*LENGHT; ++i){
        if(gsl_spmatrix_uint_get(graph->t, idx, i) != NO_DIR ){
            gsl_spmatrix_uint_set(graph->t, idx, i, NO_DIR );
            gsl_spmatrix_uint_set(graph->t, i, idx, NO_DIR);
        }
    }
}

/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens){
    int queen_number = 4*(LENGHT/10 + 1 );
    for(int  i =0; i < queen_number ; ++i ){
        if ( queens[i] == move.queen_src ){ //we look for the ex_position and then we put the new position
            queens[i] = move.queen_dst;
            break;
        }
    }
    // print_sparse_matrix(graph->t);
    put_arrow(graph, move.arrow_dst); //here we updates the graph, we make the position arrow_dst isolated
    // print_sparse_matrix(graph->t);
}



