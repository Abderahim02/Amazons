#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/hole.h"

extern struct graph_t * initialize_graph(unsigned int length);
extern void  make_zero_i_j(struct graph_t *g, int i, int j);
extern void make_hole(struct graph_t *g, int id, int size);
extern void free_graph(struct graph_t* g);


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