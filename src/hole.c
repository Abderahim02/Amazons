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
// gsl_spmatrix_uint * donut_mat(gsl_spmatrix_uint *mat,int len ){
//     int t[(len*len)/9];
//     int c = 0 ;
//     for (int k = (len/ 3)*len;k < (len/ 3)*len ; k+=len){
//     for (int i = 0 ; i<len/3 ; i++){
//         t[c] = k + i; 
//         c++;
//     }
//     }
//     hollow_matrix(mat,t,mat->size1);
// return mat;
// }
void  make_hole(struct graph_t *g, int id, int size){
  int vertices=g->num_vertices;
  int n=(int)sqrt(vertices);
  for(int i=0; i<vertices; i++){
    for(int j=0;j<vertices ;j++){
      if( ((j%n>=id%n && j%n<(id+size)%n) &&//colonnes de j appartient au trou
	   (j/n>=id/n && j/n<id/n+size))){//ligne de j appartient au trou
	 
	  gsl_spmatrix_uint_set(g->t, i, j,0);
	  gsl_spmatrix_uint_set(g->t, j, i,0);
      }
    }
  }
}
//for testing
// int main(){
//     struct graph_t * g= initialize_graph(16);
//     initialize_graph_positions_classic(g);
//     printf("op %d\n",(int)sqrt(g->num_vertices));
//     make_hole(g,1,6);
//     print_sparse_matrix(g->t);
//     free_graph(g);
//     return 0;
// }