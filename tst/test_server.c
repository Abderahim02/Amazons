
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../src/server_functions.h"
#include "../src/strategyplayer3.h"
#include <assert.h>

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number);
extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);
extern void make_graph(struct graph_t * g, unsigned int m ,char s );
extern int position_inside(int queen, struct graph_t* graph, enum dir_t dir, struct player_t player);
/*
    a test for the graph_table function, it should return a pointer with inialized values to 0
*/
void test_graph_table(void){
    printf("-----Started Testing graph_table---------- \n");
    struct graph_t* graph=initialize_graph(4);
    make_graph(graph,4,'c');
    int *t=graph_table(graph);
    for(int i=0;i<9;i++){
        assert(t[0]==0);
    }
    free(t);
    free_graph(graph);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    printf("-----Finished Testing graph_table---------- \n");

}

/*
    a test for the function table that fills an array of positions of the queens and positions with
    no pawn.
*/
void test_table(void){
    printf("-----Started Testing table---------- \n");
    struct graph_t* graph=initialize_graph(3);
    make_graph(graph,3,'c');
    int *t=graph_table(graph);

    unsigned int a[1]={0};
    unsigned int b[1]={8};
    unsigned int *queens[NUM_PLAYERS]={a,b};
    table(queens,t,1);
    assert(t[0]==1);
    assert(t[8]==2);
    assert(t[3]==0);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free(t);
    free_graph(graph);
    printf("-----FinishedTesting table---------- \n");
}
/*
    a function for testing gthe next and start player functions
*/
void start_next(void){
    printf("-----Started Testing strat_next_players---------- \n");
    assert(start_player()>=0);
    assert(start_player()<=1);
    printf("\033[32mTest 1/2 PASSED\033[0m\n");

    int player=BLACK;
    assert(next_player(player)==WHITE);
    assert(next_player(WHITE)==BLACK);
    printf("\033[32mTest 2/2 PASSED\033[0m\n");
    printf("-----Finished Testing strat_next_players---------- \n");

}

/*
    a tests for the function copying the two arrays of queens positions from the server to players 
*/
void test_copy_queens(void){
    printf("-----Started Testing copy_queens---------- \n");
    unsigned int t[2]={2,4};
    unsigned int h[2]={1,3};
    unsigned int *queens[2]={t, h};
    unsigned int *queens1[2]={allouer_table(2), allouer_table(2)};
    queens_copy(queens, queens1, 2);
    assert(queens1[0][0]==queens[0][0]);
    assert(queens1[0][1]==queens[0][1]);
    assert(queens1[1][0]==queens[1][0]);
    assert(queens1[1][1]==queens[1][1]);
    printf("\033[32mTest 1/1 PASSED\033[0m\n");
    free(queens1[0]);
    free(queens1[1]);
    printf("-----Finished Testing copy_queens---------- \n");

}
void test_display(void){
     struct graph_t* graph=initialize_graph(4);
    make_graph(graph,4,'c');
    struct graph_t *graph2=graph_cpy(graph);
     unsigned int t[2]={2,4};
    unsigned int h[2]={1,3};
    unsigned int *queens[2]={t, h};
    sdl_display(graph2,queens,2,4);
    printf("\n");
    display(graph,queens,2);
    free_graph(graph);
    free_graph(graph2);

}

/*
    a test for the function checking if the position is in the missle of the grid and not in
    boundaries.
*/
void test_inside_position(){
    printf("-----Started Testing inside_position---------- \n");
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    struct player_t p;
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    display(graph,queens,m);
    assert(position_inside(0, graph, DIR_NW, p ) == 0);
    assert(position_inside(6, graph, DIR_NW, p ) == 0);
    assert(position_inside(7, graph, DIR_NW, p ) == 0);
    printf("\033[32mTest 1/2 PASSED\033[0m\n");

    assert(position_inside(25, graph, DIR_NW, p ) == 1);
    assert(position_inside(21, graph, DIR_NW, p ) == 1);
    assert(position_inside(35, graph, DIR_NW, p ) == 1);
    printf("\033[32mTest 2/2 PASSED\033[0m\n");
    printf("-----Finished Testing indie position---------- \n\n");
    free_graph(graph);
}

/*
    a test function for the function returning all positions of a position 
    in the grid in one direction.
*/
void test_dir_in_board(){
    printf("-----Started Testing dir_in_board---------- \n");
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
    struct player_t p;
    p.num_queens=m;
    p.current_queens=white_queens;
    p.other_queens=black_queens;
    display(graph, queens, MAX_QUEENS);
    unsigned int* t=dir_in_board(2, graph, p);
    assert(t[0]==3);
    assert(t[1]==4);
    assert(t[2]==5);
    assert(t[3]==6);
    free(t);
    t=dir_in_board(5, graph, p);
    assert(t[0]==3);
    assert(t[1]==4);
    assert(t[2]==5);
    assert(t[3]==6);
    free(t);
    t=dir_in_board(16, graph, p);
    assert(t[0]==3);
    assert(t[1]==2);
    assert(t[2]==4);
    assert(t[3]==7);
    free(t);
    t=dir_in_board(23, graph, p);
    assert(t[0]==3);
    assert(t[1]==3);
    assert(t[2]==6);
    assert(t[3]==8);
    free(t);
    free_graph(graph);
    printf("-----Finished Testing dir_in_board---------- \n");
}
