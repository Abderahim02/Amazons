#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"

struct graph_t * initialize_graph(int n){
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, n);
    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            gsl_spmatrix_uint_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid;
    grid->num_vertices = n*n;
    grid->t = mat;
    return grid;
}

void print_sparse_matrix(gsl_spmatrix_uint *mat) {
    printf("Sparse matrix:\n");
    printf("size1 = %zu, size2 = %zu\n", mat->size1, mat->size2);

// Loop over all gti pairs of vertices (n*n iterations)
for (unsigned int i = 0; i < mat->size1; i++) {
    for (unsigned int j = 0; j < mat->size2; j++) {
      printf("(%u)\n",gsl_spmatrix_uint_get(mat, i, j));  
    }
  }
    }


int main(){
struct graph_t * g = initialize_graph(4);
print_sparse_matrix(g->t);   
}
