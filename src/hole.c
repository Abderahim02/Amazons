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

// void  make_hole(struct graph_t *g, int id, int size){
//   int vertices=g->num_vertices;
//   int n=(int)sqrt(vertices);
//   for(int i=0; i<vertices; i++){
//     for(int j=0;j<vertices ;j++){
//       if( ((j%n>=id%n && j%n<(id+size)%n) &&//colonnes de j appartient au trou
// 	   (j/n>=id/n && j/n<id/n+size))){//ligne de j appartient au trou
	 
//           gsl_spmatrix_uint_set(g->t, i, j,0);
//           gsl_spmatrix_uint_set(g->t, j, i,0);
//       }
//     }
//   }
// }


void  make_zero_i_j(struct graph_t *g, int i, int j){
    size_t row_start = g->t->p[i];
    size_t row_end = g->t->p[i + 1];
    for( size_t pos = row_start; pos < row_end; ++pos){
        if(g->t->i[pos] == j){
            for( size_t k = pos ; k < g->t->nz ; ++k){
                g->t->data[k] = g->t->data[k+1];
                g->t->i[k] = g->t->i[k+1];
        }
        g->t->nz--;
        for( size_t k = i+1; k <= g->t->size1; ++k) g->t->p[k] --;
        return ;
        }
    }
}

// // id la position dans le tableau unidimentionnel en supposant que la matrice est non compressé, size
// void make_hole(struct graph_t *g, int id, int size){
//     size_t id_i =  id/g->num_vertices;
//     size_t id_j =  id%g->num_vertices; 
//     size_t row_start = g->t->p[id_i];
//     size_t row_end = g->t->p[id_i + 1];
//     for (size_t pos = row_start; pos < row_end; pos++) {
//         if (g->t->i[pos] >= 0 || g->t->i[pos] <= id_j ) {
//             make_zero_i_j(g, pos, id_j);
//         }
//     }
// }


void  make_hole(struct graph_t *g, int id, int size){
  int vertices=g->num_vertices;
  int n=(int)sqrt(vertices);
  for(int i=0; i<vertices; i++){
    for(int j=0;j<vertices ;j++){
      if( ((j%n>=id%n && j%n<(id+size)%n) &&//colonnes de j appartient au trou
	                (j/n>=id/n && j/n<id/n+size))){//ligne de j appartient au trou
	            size_t row_start = g->t->p[i];
              size_t row_end = g->t->p[i + 1];
              for (size_t pos = row_start; pos < row_end; ++pos) {
                  if (g->t->i[pos] == j) {
                      make_zero_i_j(g, i, j);
                      break;
                  }
              }
      }
    }
  }
}