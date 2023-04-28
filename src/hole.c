#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"
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


// void make_graph(struct graph_t * g, char s){ 
//   switch(s){
//     size_t l = g->t->size1;
//     case 'c' :
//       g->num_vertices = sqrt(l);
//       // return g;
//       break;
//     case 'd':
//       g->num_vertices = 8*l/9;
//       make_hole(g, sqrt(l)*l + sqrt(l) , l*l/9 );
//       break;
//     case 't':
//       g->num_vertices = 21*l / 25 ;
//       make_hole(g, l/5*l + l, l/25 );
//       make_hole(g, 2*l/5*l + l, l/25 );
//       make_hole(g, 3*l/5*l + l, l/25 );
//       break;
//   }
//   // return g;
// }