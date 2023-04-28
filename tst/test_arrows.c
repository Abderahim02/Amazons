#include <stdlib.h>
#include <stdio.h>

//#include "../src/graph.h"
#include "../src/grid.h"
#include "../src/move.h"


void test_arrows(){
    struct graph_t* graph = initialize_graph();
    initialize_graph_positions_classic(graph);
    print_board(graph);
    // struct move_t mv = {1, 1, 1};
    // play(mv);
    // print_board(graph);
    printf("OK\n");
}

int main(){
    test_arrows();
    return 0;
}