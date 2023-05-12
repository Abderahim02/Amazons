#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/move.h"
#include "../src/moteur.h"

extern struct graph_t * initialize_graph(unsigned int length);
extern void initialize_graph_positions_classic(struct graph_t* g);
extern void print_sparse_matrix(gsl_spmatrix_uint *mat);
extern void free_graph(struct graph_t* g);
void  make_hole(struct graph_t *g, int id, int size);
extern void  make_zero_i_j(struct graph_t *g, int i, int j);
extern void make_hole(struct graph_t *g, int id, int size);




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