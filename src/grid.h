#ifndef _GRID_H_
#define _GRID_H_

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

#include "graph.h"
#include "dir.h"
struct graph_t * initialize_graph(int n);
void free_graph(struct graph_t* g);
void print_sparse_matrix(gsl_spmatrix_uint *mat);
#endif // _AMAZON_GRAPH_H_