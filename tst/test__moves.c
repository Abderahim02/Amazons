#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/graph.h"
#include "../src/move.h"
#include "../src/moteur.h"
#include <dlfcn.h>

void print__array(int* t){
    int* ptr=t;
    printf("[");
    while(*ptr){
        printf("%d ", *ptr);
        ptr++;
    }
    printf("]\n");
}


extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);
extern int empty_cell(struct graph_t *graph, int x, unsigned int size);


unsigned int *graph_table(struct graph_t *graph){
    unsigned int length=sqrt(graph->t->size1);
    unsigned int *t=(unsigned int *)malloc(sizeof(unsigned int)*length*length);
    for(unsigned int i=0 ; i<length*length;i++){
     if(empty_cell(graph,i,length*length))   
            t[i]=UINT_MAX;
        else t[i]=0;
    }
    return t;
}

void table(unsigned int* queens[NUM_PLAYERS], unsigned int *t, unsigned int queens_number){
    for(unsigned int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number){
    unsigned int length=sqrt(graph->t->size1);
    unsigned int *t = graph_table(graph);
    table(queens,t,queens_number);
    for(unsigned int i=0;i<length*length;i++){
        if(i!=0 && i%length==0) printf("\n");
        if(t[i]==UINT_MAX) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n");
    free(t);
}





void test__available_dst(){
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    struct player player;
    player.num_queens=0;

    unsigned int position=0;
    unsigned int* t=available_dst(graph, DIR_NORTH, position, player);
    assert(t[0]==0);
    t=available_dst(graph, DIR_SOUTH, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+size);
    assert(t[2]==position+size*2);
    assert(t[3]==position+size*3);
    t=available_dst(graph, DIR_EAST, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+1);
    assert(t[2]==position+2);
    assert(t[3]==position+3);
    t=available_dst(graph, DIR_SE, position, player);
    assert(t[0]==size-1);
    assert(t[1]==position+size+1);
    assert(t[2]==position+size*2+2);
    assert(t[3]==position+size*3+3);
    t=available_dst(graph, DIR_WEST, position, player);
    assert(t[0]==0);
    t=available_dst(graph, DIR_NE, position, player);
    assert(t[0]==0);
    t=available_dst(graph, DIR_NW, position, player);
    assert(t[0]==0);
    t=available_dst(graph, DIR_SW, position, player);
    assert(t[0]==0);
    free_graph(graph);
    printf("OK test__available_dst\n");
}

void test__delete_element(struct graph_t)

void test__put_arrow(){
    unsigned int size=4;
    struct graph_t* graph = initialize_graph(size);    // enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int position=0;

    free_graph(graph);
    printf("OK test__put_arrow\n");
}

void test__begining_position(){
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
    printf("test__begining_position OK\n");
    free_graph(graph);
}

void test__execute_move(){
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

    struct move_t move2={61, 63, 55};
    execute_move(move2, graph, queens[0]);
    assert(queens[0][1]==63);

    free_graph(graph);
}





int main(){
    test__available_dst();
    test__put_arrow();
    test__begining_position();
    test__execute_move();
    printf("OK all__tests\n");
    return 0;
}