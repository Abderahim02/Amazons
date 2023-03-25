#ifndef _GRID_H_
#define _GRID_H_

#include "graph.h"
#include "dir.h"




struct graph_t * initialize_graph(int n);

void free_graph(struct graph_t* g);

void print_sparse_matrix(gsl_spmatrix_uint *mat);

//this function fill n epty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g);

#endif // _AMAZON_GRAPH_H_