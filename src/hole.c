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
            gsl_spmatrix_uint_set(mat, i,n,NO_DIR);
        }
    }
}
//removes a list "t" of nodes from the graph the shape of the hole depends on the elements of the list
void hollow_matrix(gsl_spmatrix_uint *mat,int t[], int len ){
    for (int i = 0; i < len; i++) {
    remove_node(t[i],mat);
    }
}
gsl_spmatrix_uint * donut_mat(gsl_spmatrix_uint *mat,int len ){
    int t[(len*len)/9];
    int c = 0 ;
    for (int k = (len/ 3)*len;k < (len/ 3)*len ; k+=len){
    for (int i = 0 ; i<len/3 ; i++){
        t[c] = k + i; 
        c++;
    }
    }
    hollow_matrix(mat,t,mat->size1);
return mat;
}
//for testing
int main(){
    //initialize_graph();
    return 0;
}