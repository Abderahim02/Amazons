#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/grid.h"
#include "../src/move.h"
#include "../src/moteur.h"
void print__array(int* t){
    int* ptr=t;
    printf("[");
    while(*ptr){
        printf("%d ", *ptr);
        ptr++;
    }
    printf("]\n");
}

int *graph_table(struct graph_t *graph){
    unsigned int length=sqrt(graph->t->size1);
    int *t=(int *)malloc(sizeof(int)*length*length);
    for(unsigned int i=0 ; i<length*length;i++){
     if(empty_cell(graph,i,length*length))   
            t[i]=-1;
        else t[i]=0;
    }
    return t;
}

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number){
    unsigned int length=sqrt(graph->t->size1);
    int *t = graph_table(graph);
    table(queens,t,queens_number);
    for(unsigned int i=0;i<length*length;i++){
        if(i!=0 && i%length==0) printf("\n");
        if(t[i]==-1) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n");
    free(t);
}

void table(unsigned int* queens[NUM_PLAYERS], int *t, unsigned int queens_number){
    for(unsigned int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}

//this function beging positions of the queen for both players 
void begining_position(unsigned int* queens[NUM_PLAYERS], unsigned int length){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((length/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=(1+length/7)*i+length*(length-1);
        tmp++;
        t[tmp]=length-1-(1+length/7)*i+length*(length-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=length*(length-1)-length*(1+length/7)*i;
        tmp++;
        t[tmp]=length*(length-1)-length*(1+length/7)*i+length-1;
        tmp++;
    }
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=(1+length/7)*i;
        tmp++;
        t2[tmp]=length-1-(1+length/7)*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=length*(1+length/7)*(i);
        tmp++;
        t2[tmp]=length*(1+length/7)*i+length-1;
        tmp++;
    }
}

// void test__available_dst(){
//     unsigned int size=4;
//     struct graph_t* graph = initialize_graph(size);
//     initialize_graph_positions_classic(graph);
//     enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;


//     unsigned int position=0;
//     int* t=available_dst(graph, DIR_NORTH, position);
//     assert(t[0]==0);
//     t=available_dst(graph, DIR_SOUTH, position);
//     assert(t[0]==size-1);
//     assert(t[1]==position+size);
//     assert(t[2]==position+size*2);
//     assert(t[3]==position+size*3);
//     t=available_dst(graph, DIR_EAST, position);
//     assert(t[0]==size-1);
//     assert(t[1]==position+1);
//     assert(t[2]==position+2);
//     assert(t[3]==position+3);
//     t=available_dst(graph, DIR_SE, position);
//     assert(t[0]==size-1);
//     assert(t[1]==position+size+1);
//     assert(t[2]==position+size*2+2);
//     assert(t[3]==position+size*3+3);
//     t=available_dst(graph, DIR_WEST, position);
//     assert(t[0]==0);
//     t=available_dst(graph, DIR_NE, position);
//     assert(t[0]==0);
//     t=available_dst(graph, DIR_NW, position);
//     assert(t[0]==0);
//     t=available_dst(graph, DIR_SW, position);
//     assert(t[0]==0);
//     free_graph(graph);
//     printf("OK test__available_dst\n");
// }

// void test__put_arrow(){
//     unsigned int size=4;
//     struct graph_t* graph = initialize_graph(size);
//     initialize_graph_positions_classic(graph);
//     enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
//     unsigned int position=0;
//     put_arrow(graph, position);
//     for(int i=0; i<size; i++){
//         assert(gsl_spmatrix_uint_get(graph->t, position, i)==0);
//     }

//     position=size*size-1;
//     put_arrow(graph, position);
//     for(int i=0; i<size; i++){
//         assert(gsl_spmatrix_uint_get(graph->t, position, i)==0);
//     }

//     free_graph(graph);
//     printf("OK test__put_arrow\n");
// }

void test__get_neighbor(){
    unsigned int size=5;
    struct graph_t* graph = initialize_graph(size);
    initialize_graph_positions_classic(graph);
    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    printf("%d est le nombre \n", m);
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    display(graph, queens, m);
    

    printf("test__get_neighbor OK\n");
}

void test__execute_move(){
    unsigned int size=8;
    struct graph_t* graph = initialize_graph(size);
    initialize_graph_positions_classic(graph);
    enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    printf("%d est le nombre \n", m);
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    struct move_t move={2, 4, 12};
    
    execute_move(move, graph, queens[1]);
    display(graph, queens, m);

    struct move_t move2={61, 63, 55};
    assert(queens[0][1]==61);
    execute_move(move2, graph, queens[0]);
    assert(queens[0][1]==63);
    display(graph, queens, m);
    print__array(queens[1]);
    print__array(queens[0]);

    free_graph(graph);
}



int main(){
    //test__available_dst();
    //test__put_arrow();
    test__get_neighbor();
    test__execute_move();
    printf("OK all__tests\n");
    return 0;
}