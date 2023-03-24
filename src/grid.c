#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

#include "dir.h"

struct graph_t * initialize_graph(int n){
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, n);
    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < n; j++) {
            gsl_matrix_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid;
    grid->num_vertices = n*n;
    grid->t = mat;
    return grid;
}