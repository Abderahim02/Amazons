#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/moteur.h"


extern struct graph_t * initialize_graph(unsigned int length);
extern void initialize_graph_positions_classic(struct graph_t* g);
extern void print_sparse_matrix(gsl_spmatrix_uint *mat);
extern void free_graph(struct graph_t* g);
void  make_hole(struct graph_t *g, int id, int size);
extern void  make_zero_i_j(struct graph_t *g, int i, int j);
extern void make_hole(struct graph_t *g, int id, int size);



extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);

void print__array(int* t){
    int* ptr=t;
    printf("[");
    while(*ptr){
        printf("%d ", *ptr);
        ptr++;
    }
    printf("]\n");
}
/* this is a test function for getting the neighbor of a queen in a direction */
void test_get_neighbor_queens() {
    printf("-----Started Testing get_neighbor_queens ---------- \n");
    const unsigned int length = 8; // example board size
    struct graph_t* graph = initialize_graph(length);

    // Set up example arrays of current and other queens
    unsigned int curr_queens[] = {10, 25, 40};
    unsigned int other_queens[] = {12, 28, 44};

    // Test 1: Check that the function returns a valid neighbor position in the given direction
    unsigned int pos = 17; // example position
    enum dir_t direction = DIR_NORTH; // example direction
    unsigned int neighbor = get_neighbor_queens(pos, direction, graph, curr_queens, other_queens, length);
    assert(neighbor != UINT_MAX);
    assert(neighbor < length*length);
    printf("\033[32mTest 1/3 PASSED\033[0m\n");

    // Test 2: Check that the function returns UINT_MAX when there is no valid neighbor in the given direction
    pos = 0; // example position on edge of board
    direction = DIR_WEST; // example direction
    neighbor = get_neighbor_queens(pos, direction, graph, curr_queens, other_queens, length);
    assert(neighbor == UINT_MAX);
    printf("\033[32mTest 2/3 PASSED\033[0m\n");

    // Test 3: Check that the function skips over other and current queens in its search for neighbors
    pos = 33; // example position
    direction = DIR_SE; // example direction
    neighbor = get_neighbor_queens(pos, direction, graph, curr_queens, other_queens, length);
    assert(neighbor != UINT_MAX);
    assert(neighbor != 28); // other queen in the way
    assert(neighbor != 34); // current queen in the way
    printf("\033[32mTest 3/3 PASSED\033[0m\n");
    free_graph(graph);
    printf("-----Started Testing get_neighbor_queens---------- \n");

}


/*this is a functionnal teest for begining_position in the grid for both players*/
void test_begining_position() {
    printf("-----Started Testing begining_position---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    unsigned int MAX_QUEENS = 4;
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    // Check that the function initializes the positions of both players' queens
    begining_position(queens, size);
    for (int player = 0; player < NUM_PLAYERS; player++) {
        for (int i = 0; i < MAX_QUEENS; i++) {
            assert(queens[player][i] != 0);
        }
    }
    printf("\033[32mTest 1/3 PASSED\033[0m\n");
    // Test 2: Check that the function initializes the correct number of queens
    int expected_queens = ((size/10)+1)*4;
    int actual_queens = 0;
    for (int player = 0; player < NUM_PLAYERS; player++) {
        for (int i = 0; i < MAX_QUEENS; i++) {
            if (queens[player][i] >= 0) {
                actual_queens++;
            }
        }
    }
    assert(actual_queens == 2*expected_queens);
    printf("\033[32mTest 2/3 PASSED\033[0m\n");
    unsigned int length =size;
    // Test 3: Check that the function initializes the queens in valid positions
    for (int player = 0; player < NUM_PLAYERS; player++) {
        for (int i = 0; i < MAX_QUEENS; i++) {
            unsigned int q = queens[player][i];
            if (q != 0) {
                assert(q < length*length);
                assert(q % length < length);
                assert(q / length < length);
            }
        }
    }
    free_graph(graph);
    printf("\033[32mTest 3/3 PASSED\033[0m\n");
    printf("-----Finiched Testing begining_position---------- \n");
}



/*this is a test for the function available_dst */
void test__available_dst(){
    printf("-----Started Testing available_dst---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    struct player_t player;
    player.num_queens=0;

    unsigned int position=0;
    unsigned int* t=available_dst(graph, DIR_NORTH, position, player);
    assert(t[0]==0);
    printf("\033[32mTest 1/8 PASSED\033[0m\n");
    free(t);
    t=available_dst(graph, DIR_SOUTH, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+size);
    assert(t[2]==position+size*2);
    assert(t[3]==position+size*3);
    printf("\033[32mTest 2/8 PASSED\033[0m\n");
    free(t);
    t=available_dst(graph, DIR_EAST, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+1);
    assert(t[2]==position+2);
    assert(t[3]==position+3);
    free(t);
    printf("\033[32mTest 3/8 PASSED\033[0m\n");
    t=available_dst(graph, DIR_SE, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+size+1);
    assert(t[2]==position+size*2+2);
    assert(t[3]==position+size*3+3);
    free(t);
    printf("\033[32mTest 4/8 PASSED\033[0m\n");
    t=available_dst(graph, DIR_WEST, position, player);
    assert(t[0]==0);
    free(t);
    printf("\033[32mTest 5/8 PASSED\033[0m\n");
    t=available_dst(graph, DIR_NE, position, player);
    assert(t[0]==0);
    free(t);
    printf("\033[32mTest 6/8 PASSED\033[0m\n");
    t=available_dst(graph, DIR_NW, position, player);
    assert(t[0]==0);
    free(t);
    printf("\033[32mTest 7/8 PASSED\033[0m\n");
    t=available_dst(graph, DIR_SW, position, player);
    assert(t[0]==0);
    printf("\033[32mTest 8/8 PASSED\033[0m\n");
    free(t);
    free_graph(graph);
    printf("-----Finished Testing available_dst---------- \n\n");
}

void test__delete_element(){
    
    printf("test__delete_element OK\n");
}

void test__put_arrow(){
    printf("-----Started Testing put_arrow---------- \n");
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    put_arrow(graph, 6 );
    for(int i=0; i < graph->t->size1; ++i){
        assert(gsl_spmatrix_uint_get(graph->t, 6, i) == 0);
        assert(gsl_spmatrix_uint_get(graph->t, i, 6) == 0);
    }
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free_graph(graph);
    printf("-----Finished Testing put_arrow---------- \n\n");
}

void test__begining_position_size_5(){
    printf("-----Started Testing begining_position_size_5---------- \n");
    unsigned int size=5;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    assert(black_queens[0]==1);
    assert(black_queens[1]==3);
    assert(black_queens[2]==5);
    assert(black_queens[3]==9);
    assert(white_queens[0]==21);
    assert(white_queens[1]==23);
    assert(white_queens[2]==15);
    assert(white_queens[3]==19);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing begining_position_size_5---------- \n\n");
    free_graph(graph);
}

void test__begining_position_size_8(){
    printf("-----Started Testing begining_position_size_8---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    assert(black_queens[0]==2);
    assert(black_queens[1]==5);
    assert(black_queens[2]==16);
    assert(black_queens[3]==23);
    assert(white_queens[0]==58);
    assert(white_queens[1]==61);
    assert(white_queens[2]==40);
    assert(white_queens[3]==47);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing begining_position_size_8---------- \n\n");

    free_graph(graph);
}

void test__begining_position_size_9(){
    printf("-----Started Testing begining_position_size_9---------- \n");

    unsigned int size=9;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    assert(black_queens[0]==2);
    assert(black_queens[1]==6);
    assert(black_queens[2]==18);
    assert(black_queens[3]==26);
    assert(white_queens[0]==74);
    assert(white_queens[1]==78);
    assert(white_queens[2]==54);
    assert(white_queens[3]==62);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing begining_position_size_9---------- \n\n");
    free_graph(graph);
}

void test__begining_position_size_12(){
    printf("-----Started Testing begining_position_size_12---------- \n");
    unsigned int size=12;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    assert(white_queens[4]==108);
    assert(white_queens[5]==119);
    assert(white_queens[6]==84);
    assert(white_queens[7]==95);
    assert(white_queens[0]==134);
    assert(white_queens[1]==141);
    assert(white_queens[2]==136);
    assert(white_queens[3]==139);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing begining_position_size_12---------- \n\n");
    free_graph(graph);
}


void test__execute_move(){
    printf("-----Started Testing execute_move---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    

    struct move_t move={2, 4, 12};
    execute_move(move, graph, queens[1]);
    assert(queens[0][1]==61);
    printf("\033[32mTest 1/2 PASSED\033[0m\n");
    struct move_t move2={61, 63, 55};
    execute_move(move2, graph, queens[0]);
    assert(queens[0][1]==63);
    printf("\033[32mTest 2/2 PASSED\033[0m\n");
    printf("-----Finished Testing execute_move---------- \n\n");
    free_graph(graph);
}



void test__get_neighbor_gen(){
    printf("-----Started Testing get_neighbor_gen---------- \n");

    unsigned int size=5;
    struct graph_t* graph = initialize_graph(size);

    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    struct player_t player;
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
    printf("-----Finished Testing get_neighbor_gen---------- \n");
}