#include <stdlib.h>
#include <stdio.h>
#include "grid.h"
#include <stddef.h>
#include "dir.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>

//this function create an empty graph 
struct graph_t * initialize_graph(int n){  
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(n, n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            gsl_spmatrix_uint_set(mat, i, j, NO_DIR);
        }
    }
    struct graph_t * grid=malloc(sizeof(struct graph_t)); 
    grid->num_vertices = n*n;
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




int F(int n, int i, int j){
    return ( ((n+i)%n) * n + (n+j)%n );
}

//this function fill n epty graph with relachionships

void init_voisins(gsl_spmatrix_uint *matrice, int m, int i, int j, unsigned int val)
{
    if (i > 0) { // voisin haut
        gsl_spmatrix_uint_set(matrice, i-1, j, val);
    }
    if (i < m-1) { // voisin bas
        gsl_spmatrix_uint_set(matrice, i+1, j, val);
    }
    if (j > 0) { // voisin gauche
        gsl_spmatrix_uint_set(matrice, i, j-1, val);
    }
    if (j < m-1) { // voisin droit
        gsl_spmatrix_uint_set(matrice, i, j+1, val);
    }
    if (i > 0 && j > 0) { // voisin haut-gauche
        gsl_spmatrix_uint_set(matrice, i-1, j-1, val);
    }
    if (i > 0 && j < m-1) { // voisin haut-droit
        gsl_spmatrix_uint_set(matrice, i-1, j+1, val);
    }
    if (i < m-1 && j > 0) { // voisin bas-gauche
        gsl_spmatrix_uint_set(matrice, i+1, j-1, val);
    }
    if (i < m-1 && j < m-1) { // voisin bas-droit
        gsl_spmatrix_uint_set(matrice, i+1, j+1, val);
    }
}
// void initialize_graph_positions_classic(struct graph_t* g){ 
//     int graph_size = g->t->size1;
//     for (size_t m = 0; m < graph_size ; m++) { //On parcourt toute la liste des graph_size**2 
//         for (size_t n = 0; n < graph_size ; n++) {
//             printf("%d\n", F(graph_size, m, n));
//             gsl_spmatrix_uint_set(g->t, F(graph_size, m, n+1),F(graph_size, n+1,m), DIR_EAST);
//             // gsl_spmatrix_uint_set(g->t, F(graph_size,m, n+1), F(graph_size,n+1, m),DIR_EAST);
//             // gsl_spmatrix_uint_set(g->t, F(graph_size, m, n+1),F(graph_size,n+1, m ), DIR_EAST);
//             // gsl_spmatrix_uint_set(g->t, F(graph_size,  m, n-1), F(graph_size,  n-1, m), DIR_WEST);
//             // gsl_spmatrix_uint_set(g->t, F(graph_size,  m, n-1), F(graph_size,  n-1, m), DIR_WEST);
//             // gsl_spmatrix_uint_set(g->t, F(graph_size,  m, n-1), F(graph_size,  n-1, m), DIR_WEST);
//      }
//     }
// }





//this function fill n epty graph with relachionships
void initialize_graph_positions_classic(struct graph_t* g, int graph_size){ 
    for (size_t i = 0; i < graph_size ; i++) {           
             if( i % (graph_size) == 0){
                gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
                gsl_spmatrix_uint_set(g->t, i+1, i, DIR_WEST);
                if( i == 0 ){ //la premiere case
                        gsl_spmatrix_uint_set(g->t, i, + graph_size , DIR_SOUTH);
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
                }
                else if (i == graph_size*graph_size - graph_size ){ //la case au coin gauche bas
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_NORTH);
                        gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_NE);
                }
                else { // les aures cases de la colonne
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
                    gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);  
                }
            }
            //si on est sur l'estremité droite
            else if(i%graph_size == graph_size - 1){
                gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
                if (i == graph_size - 1){ // si on est sur le coin droit haut 
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size - 1, DIR_SW);
                }
                else if (i == graph_size*graph_size - 1 ){// si on est sur le coin droit bas
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
                }
                else{ //les autres cases de le colonne droite
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size , DIR_SOUTH);
                }
            }
            //si on est au milieu de la grille
            else{
                    gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
                    gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
                if ( 0 < i && i< graph_size ){ // la premiere ligne 
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
                }
                else if( graph_size*graph_size - graph_size < i ){ //la derniere ligne
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
                }
                else{ //les autres cases
                    gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
                    gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
                    gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
                    gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
                }
            }
    }  
}



// //this function fill n epty graph with relachionships
// void initialize_graph_positions_classic(struct graph_t* g){ 
//     int graph_size = g->t->size1;
//     for (size_t i = 0; i < graph_size*graph_size ; i++) { //On parcourt toute la liste des graph_size**2 
//         //si on est sur l'extremité gauche
//         if( i % graph_size == 0){
//            if( i == 0 ){ //la premiere case
//                 gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
//            }
//            else if (i == graph_size*graph_size - graph_size){ //la case au coin gauche bas
//                 gsl_spmatrix_uint_set(g->t, i,i+1, DIR_EAST);
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_NORTH);
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_NE);
//            }
//            else { // les aures cases de la colonne
//             gsl_spmatrix_uint_set(g->t, i, i+1, DIR_EAST);
//             gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
//             gsl_spmatrix_uint_set(g->t, i, i+ graph_size+1, DIR_SE);
//             gsl_spmatrix_uint_set(g->t, i, i-graph_size, DIR_NORTH);  
//            }
//         }
//         //si on est sur l'estremité droite
//         else if(i%graph_size == graph_size - 1){
//             if (i == graph_size - 1){ // si on est sur le coin droit haut
//                 gsl_spmatrix_uint_set(g->t, i, i-1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size, DIR_SOUTH);
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size - 1, DIR_SW);
//             }
//             else if (i == graph_size*graph_size - 1 ){// si on est sur le coin droit bas
//                 gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
//                 gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
//             }
//             else{ //les autres cases de le colonne droite
//                 gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
//                 gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size -1 , DIR_NW);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size , DIR_SOUTH);
//             }
//         }
//         //si on est au milieu de la grille
//         else{
//             if ( 0 < i && i< graph_size ){ // la premiere ligne 
//                 gsl_spmatrix_uint_set(g->t, i, i+ graph_size, DIR_SOUTH);
//                 gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
//             }
//             else if( graph_size*graph_size - graph_size < i ){ //la derniere ligne
//                 gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
//                 gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
//             }
//             else{ //les autres cases
//                 gsl_spmatrix_uint_set(g->t, i, i- graph_size, DIR_NORTH);
//                 gsl_spmatrix_uint_set(g->t, i, i - 1, DIR_WEST);
//                 gsl_spmatrix_uint_set(g->t, i, i + 1 , DIR_EAST);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size - 1 , DIR_NW);
//                 gsl_spmatrix_uint_set(g->t, i, i - graph_size + 1 , DIR_NE);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size - 1 , DIR_SW);
//                 gsl_spmatrix_uint_set(g->t, i, i + graph_size + 1 , DIR_SE);
//             }
//         }
//         // printf("%d", );
//     }  
// }

void test_initializegraph_positions(){
    struct graph_t* graph = initialize_graph(10);
    initialize_graph_positions_classic(graph, 4);
    print_sparse_matrix(graph->t);
}

int main(){
    test_initializegraph_positions();
    printf("okkkk");
    return 1;
}