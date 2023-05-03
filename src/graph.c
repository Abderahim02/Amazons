#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h> 

#include "graph.h"
#include "dir.h"
#include "hole.h"

/*this function fill an empty graph with relachionships, it means we puts the right
values in the matrix representing the graph (la matrice d'adjacence)we consider that 
every sommit of the graph has a maximum of 8 neighbors*/
void initialize_graph_positions_classic(struct graph_t* g){ 
    size_t graph_size = sqrt(g->t->size1); 
    for (size_t i = 0; i < graph_size*graph_size-graph_size-1  ; i++) { 
        //beginning with corners
        if(i==0){
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size+1, DIR_SE);
        }
        else if(i==graph_size-1){
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size-1, DIR_SW);
        }
        else if(i%graph_size==0){
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size+1, DIR_SE);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size+1, DIR_NE);
        }
        else if(i%graph_size==graph_size-1){
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size-1, DIR_SW);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size-1, DIR_NW);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
        }

        else if(i<graph_size && i>0){
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size+1, DIR_SE);
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size-1, DIR_SW);
        }
        else{
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size, DIR_SOUTH);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size+1, DIR_SE);
            gsl_spmatrix_uint_set(g->t, i, i+graph_size-1, DIR_SW);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size+1, DIR_NE);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size-1, DIR_NW);
        }

    }
    
    for(size_t i=graph_size*graph_size-graph_size-1; i<graph_size*graph_size; i++){

        if(i==graph_size*graph_size-1){
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size-1, DIR_NW);
        }
        else if(i==graph_size*graph_size-graph_size-1){
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size+1, DIR_NE);
        }
        else{
            gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size+1, DIR_NE);
            gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
            gsl_spmatrix_uint_set(g->t, i, i-graph_size-1, DIR_NW);
        }
    }                   
}

/*this function create an empty graph  with the size length*length, a matrix of size length*length
is needed to store a graph of size length */
struct graph_t * initialize_graph(unsigned int length){  
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(length* length, length*length);
    for (int i = 0; i < length*length; i++) {
        for (int j = 0; j < length* length; j++) {
            gsl_spmatrix_uint_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid=(struct graph_t *)malloc(sizeof(struct graph_t)); 
    grid->num_vertices = length*length;
    grid->t=mat;
    initialize_graph_positions_classic(grid);
    gsl_spmatrix_uint* csr = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
    gsl_spmatrix_uint_free(mat);
    grid->t = csr;
    return grid;
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

// struct graph_t *graph_cpy(const struct graph_t *graph, int size){
//   struct graph_t *graph_dst = malloc(sizeof(struct graph_t));
//   gsl_spmatrix_uint *tmp=initialize_graph(size);
//   graph_dst->t=gsl_spmatrix_uint_compress(tmp, GSL_SPMATRIX_CSR);
//   gsl_spmatrix_uint_free(tmp);
//   gsl_spmatrix_uint_memcpy(graph_dst->t, graph->t); 
//   graph_dst->num_vertices = graph->num_vertices;
//   return graph_dst;
// }


// void initialize_donut_graph(struct graph_t* graph){
//     initialize_graph_positions_classic(graph);
//     unsigned int length=graph->t->size1;
//     make_hole(graph, (length/3)*length + length/3 , length/3);
//     graph->num_vertices = 8*length*length/9;
// }

// void initialize_trefle_graph(struct graph_t* graph){
//     initialize_graph_positions_classic(graph);
//     unsigned int length=graph->t->size1;
//     make_hole(graph, length/5*length + length/5, length/5 );
//     make_hole(graph, length/5*length + 3*length/5 , length/5 );
//     make_hole(graph, 3*length/5*length + length/5, length/5 );
//     make_hole(graph, 3*length/5*length + 3*length/5, length/5 );
//     graph->num_vertices = 21*length*length / 25 ;
// }

// void initialize_eight_graph(struct graph_t* graph){
//     initialize_graph_positions_classic(graph);
//     unsigned int length=graph->t->size1;
//     make_hole(graph, 2*(length/4) * length + length/4, length/4 );
//     make_hole(graph, (length/4) * length + 2*length/4 , length/4 );
//     graph->num_vertices = 21*length*length / 25 ;
// }

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
