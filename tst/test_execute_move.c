
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include "../src/graph.h"
#include "../src/server_functions.h"
#include <assert.h>

extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);

void test_graph_table(void){
    struct graph_t* graph=initialize_graph(4);
    make_graph(graph,4,'c');
    int *t=graph_table(graph);
    for(int i=0;i<9;i++){
        assert(t[0]==0);
    }
    printf("graph_table passed\n");
free(t);
free_graph(graph);

}

void test_table(void){
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
    printf("table passed\n");
    printf("%d %d \n#\n", 3, 3);
    sdl_display(graph,queens,1,3);
    printf("sdl passed \n");
    free(t);
    free_graph(graph);
}

void start_next(void){
    assert(start_player()>=0);
    assert(start_player()<=1);
    printf("start_player passed\n");

    int player=BLACK;
    assert(next_player(player)==WHITE);
    assert(next_player(WHITE)==BLACK);
    printf("next_player passed\n");

}

void test_copy_queens(void){
    unsigned int t[2]={2,4};
    unsigned int h[2]={1,3};
    unsigned int *queens[2]={t, h};
    unsigned int *queens1[2]={allouer_table(2), allouer_table(2)};
    queens_copy(queens, queens1, 2);
    assert(queens1[0][0]==queens[0][0]);
    assert(queens1[0][1]==queens[0][1]);
    assert(queens1[1][0]==queens[1][0]);
    assert(queens1[1][1]==queens[1][1]);
    printf("queens_copy passed\n");
    free(queens1[0]);
    free(queens1[1]);




}



int main(){
    //test_execute_move();
    test_graph_table();
    test_table();
    start_next();
    test_copy_queens();
    return 0;
}
