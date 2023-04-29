#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/grid.h"
#include "../src/move.h"
#include "../src/moteur.h"


void test__get_neighbor_gen(){
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);
    initialize_graph_positions_classic(graph);
    print_sparse_matrix(graph->t);

    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    //Positions in the corners
    //position 0, 3 neighbors
    unsigned int position=0;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==-1);
    
    //position 15(size*size-1)
    position=size*size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==-1);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==-1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==position-size-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==-1);

    //position 11
    position=size*size-size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==-1);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==-1);

    //position 3(size-1)
    position=size-1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==-1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==position+size-1);

    //position in the left of the board
    position=size;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==-1);


    //position in the upper of the board
    position=2;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==-1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==position+size-1); 

    //In the center of the board
    position=size+1;
    assert(get_neighbor_gen(position, DIR_NORTH, graph)==position-size);
    assert(get_neighbor_gen(position, DIR_SOUTH, graph)==position+size);
    assert(get_neighbor_gen(position, DIR_EAST, graph)==position+1);
    assert(get_neighbor_gen(position, DIR_WEST, graph)==position-1);
    assert(get_neighbor_gen(position, DIR_NE, graph)==position-size+1);
    assert(get_neighbor_gen(position, DIR_NW, graph)==position-size-1);
    assert(get_neighbor_gen(position, DIR_SE, graph)==position+size+1);
    assert(get_neighbor_gen(position, DIR_SW, graph)==position+size-1);

    free_graph(graph);
    printf("OK\n");
}


int main(){
    test__get_neighbor_gen();
    return 0;
}