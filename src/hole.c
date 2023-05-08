
#include "hole.h"



void  make_zero_i_j(struct graph_t *g, int i, int j){
    size_t row_start = g->t->p[i];
    size_t row_end = g->t->p[i + 1];
    for( size_t pos = row_start; pos < row_end; ++pos){
        if(g->t->i[pos] == j){
            for( size_t k = pos ; k < g->t->nz - 1 ; ++k){
                g->t->data[k] = g->t->data[k+1];
                g->t->i[k] = g->t->i[k+1];
        }
        g->t->nz--;
        for( size_t k = i+1; k <= g->t->size1; ++k) g->t->p[k] --;
        return ;
        }
    }
}

void  make_hole(struct graph_t *g, int id, int size){
  int vertices = g->num_vertices;
  int n=(int)sqrt(vertices);
  for(int i=0; i<vertices; i++){
    for(int j=0;j<vertices ;j++){
       if( (j % n >= id % n && j % n < (id + size) % n) && (j / n >= id / n && j / n < id / n + size)){//ligne de j appartient au trou
              make_zero_i_j(g, i, j);
              make_zero_i_j(g, j, i);
      }
    }
  }
}