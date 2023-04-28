#ifndef _GRID_H_
#define _GRID_H_


#include <stddef.h>

#include "graph.h"
#include "dir.h"

/** The height (number of rows or columns) of the world */


/** The number of possible places in the world */
#define WHITE 1
#define BLACK 0
#define CASE -1

#ifndef NUM_PLAYERS
    #define NUM_PLAYERS 2
#endif
// #ifndef N
//     #define N 8
// #endif




/*this function create an empty graph  with the size LENGHT*LENGHT, a matrix of size LENGHT*LENGHT
is needed to store a graph of size LENGHT */
struct graph_t * initialize_graph(unsigned int length);

//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g);

void print_sparse_matrix(gsl_spmatrix_uint *mat);

void print_board(struct graph_t* graph);

/*this function fill an empty graph with relachionships, it means we puts the right
values in the matrix representing the graph (la matrice d'adjacence)we consider that 
every sommit of the graph has a maximum of 8 neighbors*/
void initialize_graph_positions_classic(struct graph_t* g);


int empty_cell(struct graph_t *graph, int x, unsigned int size);

#endif // _AMAZON_GRAPH_H_