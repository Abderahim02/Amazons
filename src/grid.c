#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct graph_t * initialize_graph(){
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, n);
    struct graph_t * grid = gsl_spmatrix_uint; 
    for (size_t i = 0; i < nrows; i++) {
        for (size_t j = 0; j < ncols; j++) {
            gsl_matrix_set(mat, i, j, NO_DIR);
        }
    }
    return grid;
}
