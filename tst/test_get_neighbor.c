#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/moteur.h"

extern struct graph_t * initialize_graph(unsigned int length);
extern void initialize_graph_positions_classic(struct graph_t* g);
extern void print_sparse_matrix(gsl_spmatrix_uint *mat);
extern void free_graph(struct graph_t* g);
void  make_hole(struct graph_t *g, int id, int size);

// extern graph_t* graph_copy(struct graph_t *);

extern void  make_zero_i_j(struct graph_t *g, int i, int j);
extern void make_hole(struct graph_t *g, int id, int size);



void display_matrix_of_graph(struct graph_t * g){
    for (size_t i = 0; i < g->t->size1; ++i) {
        for (size_t j = 0; j < g->t->size2; ++j) {
            size_t row_start = g->t->p[i];
            size_t row_end = g->t->p[i + 1];
            int found = 0;
            for (size_t pos = row_start; pos < row_end; ++pos) {
                if (g->t->i[pos] == j) {
                    printf("%d ", g->t->data[pos]);
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

}


void test__get_neighbor_gen(){
    printf("-----Started Testing get_neighbor_gen---------- \n");

    unsigned int size=5;
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
    printf("\033[32mTest 1/7 PASSED\033[0m\n");
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
    printf("\033[32mTest 2/7 PASSED\033[0m\n");

    //
    position=size*size-size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph, player)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph, player)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_WEST, graph, player)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph, player)==position-size-1);
    assert(get_neighbor_gen(position, DIR_SE, graph, player)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph, player)==position+size-1);
    printf("\033[32mTest 3/7 PASSED\033[0m\n");

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
    printf("\033[32mTest 4/7 PASSED\033[0m\n");

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
    printf("\033[32mTest 5/7 PASSED\033[0m\n");


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
    printf("\033[32mTest 6/7 PASSED\033[0m\n");

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
    printf("\033[32mTest 7/7 PASSED\033[0m\n");
    free_graph(graph);
    printf("-----Started Testing get_neighbor_gen---------- \n");
}





void test_initialize_graph_positions_classic(){
    printf("-----Started Testing initialize_graph_positions_classic---------- \n");
    unsigned int length = 5;
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
    //random tests
    assert(gsl_spmatrix_uint_get(grid->t, 0,0) == 0);
    assert(gsl_spmatrix_uint_get(grid->t, 0,1) == 7);
    assert(gsl_spmatrix_uint_get(grid->t, 1,2) == 7);
    assert(gsl_spmatrix_uint_get(grid->t, 0,5) == 5);
    assert(gsl_spmatrix_uint_get(grid->t, 0,6) == 4);
    assert(gsl_spmatrix_uint_get(grid->t, 10,16) == 4);
    printf("\033[32mTest 1/8 PASSED\033[0m\n");
    //a postion in the up line
    assert(gsl_spmatrix_uint_get(grid->t, 2,1) == 3);
    assert(gsl_spmatrix_uint_get(grid->t, 2,3) == 7);
    assert(gsl_spmatrix_uint_get(grid->t, 2,7) == 5);
    assert(gsl_spmatrix_uint_get(grid->t, 2,8) == 4);
    assert(gsl_spmatrix_uint_get(grid->t, 2,6) == DIR_SW);
    printf("\033[32mTest 2/8 PASSED\033[0m\n");


    //a position in the left edge
    assert(gsl_spmatrix_uint_get(grid->t, 14, 19) == DIR_SOUTH);
    assert(gsl_spmatrix_uint_get(grid->t, 14, 13) == DIR_WEST);
    assert(gsl_spmatrix_uint_get(grid->t, 14, 18) == DIR_SW);
    assert(gsl_spmatrix_uint_get(grid->t, 14, 8) == DIR_NW);
    assert(gsl_spmatrix_uint_get(grid->t, 14, 9) == DIR_NORTH);
    printf("\033[32mTest 3/8 PASSED\033[0m\n");

    //a position in the left edge
    assert(gsl_spmatrix_uint_get(grid->t, 19, 14) == DIR_NORTH);
    assert(gsl_spmatrix_uint_get(grid->t, 19, 18) == DIR_WEST);
    assert(gsl_spmatrix_uint_get(grid->t, 19, 13) == DIR_NW);
    assert(gsl_spmatrix_uint_get(grid->t, 19, 23) == DIR_SW);
    assert(gsl_spmatrix_uint_get(grid->t, 19, 24) == DIR_SOUTH);
    printf("\033[32mTest 4/8 PASSED\033[0m\n");

    //a position in the right edge
    assert(gsl_spmatrix_uint_get(grid->t, 10, 11) == 7);
    assert(gsl_spmatrix_uint_get(grid->t, 10, 16) == 4);
    assert(gsl_spmatrix_uint_get(grid->t, 10, 5) == 1);
    assert(gsl_spmatrix_uint_get(grid->t, 10, 6) == 2);
    assert(gsl_spmatrix_uint_get(grid->t, 10, 15) == 5);
    printf("\033[32mTest 5/8 PASSED\033[0m\n");

    //a position in down edge
    assert(gsl_spmatrix_uint_get(grid->t, 22, 23) == DIR_EAST);
    assert(gsl_spmatrix_uint_get(grid->t, 22, 21) == DIR_WEST);
    assert(gsl_spmatrix_uint_get(grid->t, 22, 16) == DIR_NW);
    assert(gsl_spmatrix_uint_get(grid->t, 22, 17) == DIR_NORTH);
    assert(gsl_spmatrix_uint_get(grid->t, 22, 18) == DIR_NE);
    printf("\033[32mTest 6/8 PASSED\033[0m\n");

    //a position in corner
    assert(gsl_spmatrix_uint_get(grid->t, 24, 19) == DIR_NORTH);
    assert(gsl_spmatrix_uint_get(grid->t, 24, 23) == DIR_WEST);
    assert(gsl_spmatrix_uint_get(grid->t, 24, 18) == DIR_NW);
    printf("\033[32mTest 7/8 PASSED\033[0m\n");

    //a position in corner
    assert(gsl_spmatrix_uint_get(grid->t, 4, 9) == DIR_SOUTH);
    assert(gsl_spmatrix_uint_get(grid->t, 4, 3) == DIR_WEST);
    assert(gsl_spmatrix_uint_get(grid->t, 4, 8) == DIR_SW);
    printf("\033[32mTest 8/8 PASSED\033[0m\n");
    printf("-----Finished Testing initialize_graph_positions_classic?--OK---------- \n");
    free_graph(grid);

}

void test_make_i_j(){
    printf("-----Started Testing making zero in position i,j in csr matrix ---------- \n");
    // Create a graph
    struct graph_t * graph = initialize_graph(5);

    assert(gsl_spmatrix_uint_get(graph->t,0, 1 ) == 7);
    make_zero_i_j(graph, 0, 1);
    assert(gsl_spmatrix_uint_get(graph->t, 0, 1 ) == 0);
    printf("\033[32mTest 1/6 PASSED\033[0m\n");

    assert(gsl_spmatrix_uint_get(graph->t, 5, 6 ) == 7);
    make_zero_i_j(graph, 5, 6);
    assert(gsl_spmatrix_uint_get(graph->t, 5, 6 ) == 0);
    printf("\033[32mTest 2/6 PASSED\033[0m\n");

    assert(gsl_spmatrix_uint_get(graph->t, 11, 20 ) == 0);
    make_zero_i_j(graph, 11, 20);
    assert(gsl_spmatrix_uint_get(graph->t, 11, 20 ) == 0);
    printf("\033[32mTest 3/6 PASSED\033[0m\n");

    assert(gsl_spmatrix_uint_get(graph->t, 19, 18 ) == 3);
    make_zero_i_j(graph, 19, 18);
    assert(gsl_spmatrix_uint_get(graph->t, 19, 18 ) == 0);
    printf("\033[32mTest 4/6 PASSED\033[0m\n");

    assert(gsl_spmatrix_uint_get(graph->t, 20, 15 ) == 1);
    make_zero_i_j(graph, 20, 15);
    assert(gsl_spmatrix_uint_get(graph->t, 20, 15 ) == 0);
    printf("\033[32mTest 5/6 PASSED\033[0m\n");

    assert(gsl_spmatrix_uint_get(graph->t, 21, 18 ) == 0);
    make_zero_i_j(graph, 12, 18);
    assert(gsl_spmatrix_uint_get(graph->t,21, 18 ) == 0);
    printf("\033[32mTest 6/6 PASSED\033[0m\n");
  
    printf("-----Finished Testing making zero in position i,j in csr matrix ?--OK---------- \n");
    free_graph(graph);
}


void test_make_hole(){
    // Create a graph
    printf("-----Started Testing make hole ---------- \n");
    unsigned int size=5;
    struct graph_t* graph = initialize_graph(size);
    make_hole(graph, 6, 3);
    assert(gsl_spmatrix_uint_get(graph->t, 5, 6 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 6, 7 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 7, 8 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 9, 8 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 8, 9 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 3, 8 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 8, 12 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 18, 23 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 17, 22 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 16, 21 ) == 0);
    assert(gsl_spmatrix_uint_get(graph->t, 16, 15 ) == 0);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing make hole?--OK ---------- \n");
    free_graph(graph);
}