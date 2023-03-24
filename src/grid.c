#include "graph.h"
#include <stdlib.h>
#include <stdio.h>

struct graph_t * initialize_graph(int n , int m){
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, m);
    struct graph_t * grid = gsl_spmatrix_uint; 
    for (size_t i = 0; i < nrows; i++) {
        for (size_t j = 0; j < ncols; j++) {
            gsl_matrix_set(mat, i, j, NO_DIR);
        }
    }
    return grid;
}
void print_sparse_matrix(gsl_spmatrix_uint *mat) {
    printf("Sparse matrix:\n");
    printf("size1 = %zu, size2 = %zu\n", mat->size1, mat->size2);

    for (size_t i = 0; i < mat->size1; i++) {
        for (gsl_spmatrix_uint_const_iter row_iter = gsl_spmatrix_uint_const_row_iterator(mat, i);!gsl_spmatrix_uint_iter_end(row_iter);gsl_spmatrix_uint_const_iter_next(row_iter)) {
            size_t j = gsl_spmatrix_uint_iter_col(row_iter);
            unsigned int val = gsl_spmatrix_uint_iter_get(row_iter);
            printf("(%u)\n",val);
        }
    }
}
void print_graph(struct graph_t * graph);
int main(){
struct graph_t * g = initialize_graph(4,4);
print_graph(g->t)
    
}