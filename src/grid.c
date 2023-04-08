#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"
#include <math.h> 
#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include "hole.h"
// /** The height (number of rows or columns) of the world */
// #ifndef LENGHT
//   #define LENGHT 8
// #endif

// /** The number of possible places in the world */
// #define GRID_SIZE (LENGHT*LENGHT)
// #define WHITE 1
// #define BLACK 0
// #define CASE -1

//this function create an empty graph 
struct graph_t * initialize_graph(){  
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(LENGHT* LENGHT, LENGHT*LENGHT);
    for (int i = 0; i < LENGHT*LENGHT; i++) {
        for (int j = 0; j < LENGHT* LENGHT; j++) {
            gsl_spmatrix_uint_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid=malloc(sizeof(struct graph_t)); 
    grid->num_vertices = LENGHT*LENGHT;
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
        if (((i%mat->size2) == 0)&&(i!=0)){
            printf("\n");
        }
        printf("\n");
    }
    }
//this function frees the momory blocks allocated for the graph
void free_graph(struct graph_t* g){
    free(g);
}





//this function fill n epty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g){ 
    size_t graph_size = sqrt(g->t->size1); 
    for (size_t i = 0; i < graph_size*graph_size - graph_size  ; i++) {           
             if( i % (graph_size) == 0){
                gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i+1, i, DIR_WEST);
                if( i == 0 ){ //la premiere case
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size , DIR_SOUTH);
                        gsl_spmatrix_uint_set(g->t, i+ graph_size, i , DIR_NORTH);
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
                        gsl_spmatrix_uint_set(g->t, i+ graph_size+1, i, DIR_NE);

                }
                else if (i == graph_size*graph_size - graph_size ){ //la case au coin gauche bas
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_NORTH);
                        gsl_spmatrix_uint_set(g->t,i+ graph_size, i, DIR_SOUTH);
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_NE);
                        gsl_spmatrix_uint_set(g->t, i+ graph_size+1, i , DIR_SE);
                }
                else { // les aures cases de la colonne
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t,i+ graph_size, i, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
                    gsl_spmatrix_uint_set(g->t, i+ graph_size+1, i, DIR_NE);
                    gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i-graph_size, i, DIR_SOUTH);
                    
                }
            }
            //si on est sur l'estremité droite
            else if(i%graph_size == graph_size - 1){
                gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
                gsl_spmatrix_uint_set(g->t, i-1, i , DIR_EAST);
                if (i == graph_size - 1){ // si on est sur le coin droit haut 
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t,  i + graph_size,i, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size - 1, DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i+ graph_size - 1,i, DIR_NW);
                }
                else if (i == graph_size*graph_size - 1 ){// si on est sur le coin droit bas
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i- graph_size,i,  DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t,i - graph_size -1 , i, DIR_SW);
                }
                else{ //les autres cases de le colonne droite
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t,  i- graph_size,i, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t,i - graph_size -1 , i, DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size , DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i + graph_size , i, DIR_NORTH);
                }
            }
            //si on est au milieu de la grille
            else{
                    gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                    gsl_spmatrix_uint_set(g->t, i - 1, i, DIR_EAST);
                    gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
                    gsl_spmatrix_uint_set(g->t,  i + 1 , i, DIR_WEST);
                if ( 0 < i && i< graph_size ){ // la premiere ligne 
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i+ graph_size,i, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i + graph_size - 1 ,i, DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
                    gsl_spmatrix_uint_set(g->t,  i + graph_size + 1 ,i, DIR_NE);
                }
                else if( graph_size*graph_size - graph_size < i  ){ //la derniere ligne
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i- graph_size, i,DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i - graph_size - 1 , i,DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
                    gsl_spmatrix_uint_set(g->t,  i - graph_size + 1 , i, DIR_SE);
                }
                else{ //les autres cases
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t,i+ graph_size,i, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t,  i- graph_size,i, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i - graph_size - 1 , i,DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
                    gsl_spmatrix_uint_set(g->t,  i - graph_size + 1 ,i, DIR_SE);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                    gsl_spmatrix_uint_set(g->t,  i + graph_size - 1 , i,DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
                    gsl_spmatrix_uint_set(g->t,  i + graph_size + 1 , i, DIR_NE);

                }
            }
    } 
    for(size_t i = graph_size*graph_size - graph_size; i<graph_size*graph_size - 1; ++i){
                    gsl_spmatrix_uint_set(g->t, i, i +1 , DIR_EAST);
                    gsl_spmatrix_uint_set(g->t,i +1 ,i, DIR_WEST);
    }
}

// struct graph_t * initialize_graph_middle_hole(){  
// struct graph_t * g = initialize_graph();
// make_hole()
// }

// void test_initializegraph_positions(){
//     struct graph_t* graph = initialize_graph();
//     initialize_graph_positions_classic(graph);
//     print_sparse_matrix(graph->t);
// }

