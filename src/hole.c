#include <stdlib.h>
#include <stdio.h>
#include "hole.h"

#include <stddef.h>
#include <math.h>
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
