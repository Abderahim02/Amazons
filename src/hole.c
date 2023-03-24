#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"
//removes a node from the graph 
void remove_node(int n,gsl_spmatrix_uint *mat){
    for (int i = 0 ; i<mat->size1;i++){
        if (gsl_spmatrix_uint_get(mat, n, i)!=NO_DIR){
            gsl_spmatrix_uint_set(mat, n, i,NO_DIR);
        }
    }
}
//removes a list of nodes from the graph
void hollow_matrix(gsl_spmatrix_uint *mat,int *t, int len ){
    for (int i = 0; i < len; i++) {
    remove_node(t[i],mat);
    }
}
//for testing
int main(){
    initialize_graph();
    return 0;
}