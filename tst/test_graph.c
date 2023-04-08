#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../src/grid.h"
#include "../src/graph.h"
#include "../src/hole.h"

void test_empty_graph(){
    struct graph_t * graph = initialize_graph();
    printf("\n");
    //remove_node(3, graph->t);
    print_sparse_matrix(graph->t);
    printf("tes : %u \n", gsl_spmatrix_uint_get(graph->t, 0, 1));
    free_graph(graph);
}

int main(){
    test_empty_graph();
    return 0;
}