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

void test__get_neighbor_gen(){
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);
    initialize_graph_positions_classic(graph);
    print_sparse_matrix(graph->t);

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


int main(){
    test__get_neighbor_gen();
    return 0;
}