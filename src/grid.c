#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include <math.h> 


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
    grid->t = mat;
    return grid;
}

void print_sparse_matrix(gsl_spmatrix_uint *mat) {
    printf("Sparse matrix:\n");
    printf("size1 = %zu, size2 = %zu\n", mat->size1, mat->size2);
    // Loop over all gti pairs of vertices (n*n iterations)
    for ( unsigned int i = 0; i < mat->size1; i++) {
        for ( unsigned int j = 0; j < mat->size2; j++) {
            printf("(%u) ",gsl_spmatrix_uint_get(mat, i, j)); 
            }
        printf("\n");
    }
    }
//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g){
    gsl_spmatrix_uint_free(g->t);
    free(g);
}


//this function fill n epty graph with relachionships
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

int empty_cell(struct graph_t *graph, int x, unsigned int size){
    for(int i=0;i<size;i++){
        if(gsl_spmatrix_uint_get(graph->t, x, i)!=NO_DIR) return 0;
    }
    return 1;
}

void print_board(struct graph_t* graph){
    unsigned int length=graph->t->size1;
    int *t=malloc(sizeof(int)*length*length);
    for(int i=0;i<length*length;i++){
        if(empty_cell(graph,i,length*length))   
            t[i]=-1;
        else t[i]=0;
    }
    for(int i=0; i<length*length; i++){
        if(i!=0 && i%length==0){
            printf("\n");
        }
        if(t[i]==-1){
            printf(" 1 ");
        }
        else{
            printf("%d ", t[i]);
        }
    }
    free(t);
    printf("\n");
}
