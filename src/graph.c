#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h> 

#include "graph.h"
#include "hole.h"





void initialize_donut_graph(struct graph_t* g, unsigned int m){
    make_hole(g, (m/3)*m + m/3 , m/3);
    g->num_vertices = 8*m*m/9;
}

void initialize_trefle_graph(struct graph_t* g, unsigned int m){
    make_hole(g, m/5*m + m/5, m/5 );
    make_hole(g, m/5*m + 3*m/5 , m/5 );
    make_hole(g, 3*m/5*m + m/5, m/5 );
    make_hole(g, 3*m/5*m + 3*m/5, m/5 );
    g->num_vertices = 21*m*m / 25 ;
}

void initialize_eight_graph(struct graph_t* g , unsigned int m){
    make_hole(g, 2*(m/4) * m + m/4, m/4 );
    make_hole(g, (m/4) * m + 2*m/4 , m/4 );
    g->num_vertices = 7*m*m / 8 ;
}




gsl_spmatrix_uint* copy_matrix(struct graph_t *graph,int size) {
  gsl_spmatrix_uint *graph_copy=gsl_spmatrix_uint_alloc(graph->t->size1,graph->t->size2);
  for (unsigned int i = 0; i <size*size ; i++) {
    for (unsigned int k = 0; k < size*size; k++) {
      if (gsl_spmatrix_uint_get(graph->t,i,k) == 1){
	      gsl_spmatrix_uint_set(graph_copy, i, k, 1);
      }
    }
  }
  return graph_copy;
}



//this function can be useful for checking if a vertex can be occupied by a queen in a game
int empty_cell(struct graph_t *graph, int x, unsigned int size){
    unsigned int row_start=graph->t->p[x];
    unsigned int row_end=graph->t->p[x+1];
    for(size_t j=row_start; j<row_end; j++){
        unsigned int neighbor=graph->t->i[j];
        if(neighbor==x){
            return 0;
        }
    }
    return 1;
}


//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g){
    gsl_spmatrix_uint_free(g->t);
    free(g);
}
