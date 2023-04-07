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



struct graph_t * initialize_graph();

void free_graph(struct graph_t* g);

void print_sparse_matrix(gsl_spmatrix_uint *mat);

//this function fill n epty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g);

#endif // _AMAZON_GRAPH_H_