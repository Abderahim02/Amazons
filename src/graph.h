#ifndef _AMAZON_GRAPH_H_
#define _AMAZON_GRAPH_H_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spblas.h>
#include <gsl/gsl_spmatrix_uint.h>


struct graph_t {
  unsigned int num_vertices; // Number of vertices in the graph
  gsl_spmatrix_uint* t;      // Sparse matrix of size n*n,
                      // t[i][j] > 0 means there is an edge from i to j
                      // t[i][j] == DIR_NORTH means that j is NORTH of i
                      // t[i][j] == DIR_SOUTH means that j is SOUTH of i
                      // and so on
};

#endif // _AMAZON_GRAPH_H_
