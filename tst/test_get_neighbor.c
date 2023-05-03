#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/moteur.h"

extern struct graph_t * initialize_graph(unsigned int length);
// extern void initialize_graph_positions_classic(struct graph_t* g);
// extern void print_sparse_matrix(gsl_spmatrix_uint *mat);
extern void free_graph(struct graph_t* g);

void test__get_neighbor_gen(){
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);

    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    struct player player;
    player.num_queens=0;
    //Positions in the corners
    //position 0, 3 neighbors
    unsigned int position=0;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==-1);
    
    //position 15(size*size-1)
    position=size*size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==position-size-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==-1);

    //position 11
    position=size*size-size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==-1);

    //position 3(size-1)
    position=size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==position+size-1);

    //position in the left of the board
    position=size;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==-1);


    //position in the upper of the board
    position=2;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==position+size-1); 

    //In the center of the board
    position=size+1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==position-size-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==position+size-1);

    free_graph(graph);
    printf("OK\n");
}



void test_make_i_j(){
    // Create a graph
    int length = 3;
    struct graph_t* graph = (struct graph_t*) malloc(sizeof(struct graph_t));
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(length, length);
    gsl_spmatrix_uint* g = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
    unsigned int size=8;
    g->size1 = 3;
    g->size2 = 3;
    g->nz = 4;
    g->p = (size_t*) malloc((g->size1 + 1) * sizeof(size_t));
    g->i = (int*) malloc(g->nz * sizeof(int));
    g->data = (double*) malloc(g->nz * sizeof(double));
    g->p[0] = 0;
    g->p[1] = 1;
    g->p[2] = 2;
    g->p[3] = 3;
    g->i[0] = 1;
    g->i[1] = 2;
    g->i[2] = 0;
    g->data[0] = 1;
    g->data[1] = 2;
    g->data[2] = 3;
    graph->t = g;

    // Print the initial graph
    printf("Initial graph:\n");
    for (size_t i = 0; i < g->size1; ++i) {
        for (size_t j = 0; j < g->size2; ++j) {
            size_t row_start = g->p[i];
            size_t row_end = g->p[i + 1];
            int found = 0;
            for (size_t pos = row_start; pos < row_end; ++pos) {
                if (g->i[pos] == j) {
                    printf("%g ", g->data[pos]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");

    // Make the element at (1, 2) zero
    printf("After making (0, 1) zero:\n");
    make_zero_i_j(graph, 0, 1);
    for (size_t i = 0; i < g->size1; ++i) {
        for (size_t j = 0; j < g->size2; ++j) {
            size_t row_start = g->p[i];
            size_t row_end = g->p[i + 1];
            int found = 0;
            for (size_t pos = row_start; pos < row_end; ++pos) {
                if (g->i[pos] == j) {
                    printf("%g ", g->data[pos]);
                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n");

    // Free memory
    // free(g->p);
    // free(g->i);
    // free(g->data);
    // free(g);
}


void test_make_hole

(){
    // Create a graph
    int length = 3;
    struct graph_t* graph = (struct graph_t*) malloc(sizeof(struct graph_t));
    gsl_spmatrix_uint *mat = gsl_spmatrix_uint_alloc(length, length);
    gsl_spmatrix_uint* g = gsl_spmatrix_uint_compress(mat, GSL_SPMATRIX_CSR);
    unsigned int size=8;
    g->size1 = 3;
    g->size2 = 3;
    g->nz = 4;
    g->p = (size_t*) malloc((g->size1 + 1) * sizeof(size_t));
    g->i = (int*) malloc(g->nz * sizeof(int));
    g->data = (double*) malloc(g->nz * sizeof(double));
    g->p[0] = 0;
    g->p[1] = 1;
    g->p[2] = 2;
    g->p[3] = 3;
    g->i[0] = 1;
    g->i[1] = 2;
    g->i[2] = 0;
    g->data[0] = 1;
    g->data[1] = 2;
    g->data[2] = 3;
    graph->t = g;
    // Free memory
    // free(g->p);
    // free(g->i);
    // free(g->data);
    // free(g);
}

 int main(){
    //  test__get_neighbor_gen();
     test_make_i_j();
     return 0;
 }
