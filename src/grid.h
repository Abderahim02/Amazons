#ifndef _GRID_H_
#define _GRID_H_

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

#include "graph.h"
#include "dir.h"




#ifndef LENGHT
  #define LENGHT 8
#endif




struct graph_t * initialize_graph();

void free_graph(struct graph_t* g);

void print_sparse_matrix(gsl_spmatrix_uint *mat);

//this function fill n epty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g);

#endif // _AMAZON_GRAPH_H_