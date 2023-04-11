#ifndef _GRID_H_
#define _GRID_H_

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

#include "graph.h"
#include "dir.h"

/** The height (number of rows or columns) of the world */
#ifndef LENGHT
  #define LENGHT 8
#endif

/** The number of possible places in the world */
#define GRID_SIZE (LENGHT*LENGHT)
#define WHITE 1
#define BLACK 0
#define CASE -1

/*this function create an empty graph  with the size LENGHT*LENGHT, a matrix of size LENGHT*LENGHT
is needed to store a graph of size LENGHT */
struct graph_t * initialize_graph();

//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g);

void print_sparse_matrix(gsl_spmatrix_uint *mat);

/*this function fill an empty graph with relachionships, it means we puts the right
values in the matrix representing the graph (la matrice d'adjacence)we consider that 
every sommit of the graph has a maximum of 8 neighbors*/
void initialize_graph_positions_classic(struct graph_t* g);

#endif // _AMAZON_GRAPH_H_