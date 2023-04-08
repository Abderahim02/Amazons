#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grid.h"

void test_empty_graph(){
    int n = 8;
    struct graph_t * graph = initialize_graph(n);
    print_sparse_matrix(graph->t);
    free_graph(graph);
}

// int main(){
//     test_empty_graph();
//     return 0;
// }