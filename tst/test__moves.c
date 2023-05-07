#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/moteur.h"
#include "../src/server_functions.h"
#include <dlfcn.h>


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







void test__available_dst(){
    printf("-----Started Testing available_dst---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    struct player player;
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
    printf("-----Finished Testing available_dst---------- \n");
}

void test__delete_element(){
    
    printf("test__delete_element OK\n");
}

void test__put_arrow(){
    printf("-----Started Testing put_arrow---------- \n");
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
   // unsigned int position=0;
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free_graph(graph);
    printf("-----Finished Testing put_arrow---------- \n");
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
    printf("-----Finished Testing begining_position_size_5---------- \n");
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
    printf("-----Finished Testing begining_position_size_8---------- \n");

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
    printf("-----Finished Testing begining_position_size_9---------- \n");
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
    printf("-----Finished Testing begining_position_size_12---------- \n");
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
    printf("-----Finished Testing execute_move---------- \n");
    free_graph(graph);
}
