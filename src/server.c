#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "dir.h"
#include <dlfcn.h>
#include <math.h>
#include "hole.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#ifndef NUM_PLAYERS
#define NUM_PLAYERS 2
#endif
#ifndef N
#define N 8
#endif

struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

struct player player_blanc;

void begining_position(unsigned int* queens[NUM_PLAYERS]){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((N/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=2*i+N*(N-1);
        tmp++;
        t[tmp]=N-1-2*i+N*(N-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=N*(N-1)-N*2*i;
        tmp++;
        t[tmp]=N*(N-1)-N*2*i+N-1;
        tmp++;
    }
    // int *t2=malloc(sizeof(int)*m);
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=2*i;
        tmp++;
        t2[tmp]=N-1-2*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=N*2*(i);
        tmp++;
        t2[tmp]=N*2*i+N-1;
        tmp++;
    }

}
int *graph_table(struct graph_t *graph){
    int *t=malloc(sizeof(int)*graph->num_vertices);
    t[0]=0;
    for(int i=0;i<N*N-1;i++){
        if(gsl_spmatrix_uint_get(graph->t, i, i+1)!=0 || (i+1)%N==0)
            t[i+1]=0;
        else t[i+1]=-1;
    }
    return t;
}
void table(unsigned int* queens[NUM_PLAYERS], int *t, int queens_number){
    for(int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}
void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number){
    int *t=graph_table(graph);
    table(queens,t,queens_number);
    for(int i=0;i<N*N;i++){
        if(i!=0 && i%N==0) printf("\n");
        if(t[i]==-1) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n");
}

void print_queens(struct player p ){
    for(int i=0; i < LENGHT ; ++i){
        printf("current [%d] = %d /// other[%d] = %d\n", p.current_queens[i] ,p.other_queens[i]);
    }
}
int main(){
    void *handle1;
    void *handle2;
        char*(*player_name1)(void);
        char*(*player_name2)(void);
        char*(*initialize1)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);
        char*(*initialize2)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);

        char *error;
        handle2 = dlopen ("libplayer2.so", RTLD_LAZY);
        handle1 = dlopen("libplayer1.so",RTLD_LAZY);
        if (!handle2 || !handle1  ) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        player_name1 = dlsym(handle1,"get_player_name");
        player_name2 = dlsym(handle2,"get_player_name");
        initialize1 = dlsym(handle1,"initialize");
        initialize2 = dlsym(handle2,"initialize");
        
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        // struct graph_t* graph = initialize_graph();
        // initialize_graph_positions_classic(graph);
        // make_hole(graph,graph->num_vertices/2,2);
        // struct graph_t* graph1 = initialize_graph();
        // initialize_graph_positions_classic(graph1);
        // struct graph_t* graph2 = initialize_graph();
        // initialize_graph_positions_classic(graph2);
        // int m=((N/10)+1)*4;
        // unsigned int queens_player1[m];
        // unsigned int queens_palyer2[m];
        // unsigned int *queens[NUM_PLAYERS]={queens_player1,queens_palyer2};
        // begining_position(queens);
        // initialize1(0,graph1,m,queens);
        // initialize2(1,graph2,m,queens);
        // display(graph,queens,m);
        // dlclose(handle1);
        // dlclose(handle2);
        
        struct graph_t* graph = initialize_graph();
        initialize_graph_positions_classic(graph);

        struct graph_t* graph1 = initialize_graph();
        initialize_graph_positions_classic(graph1);

        struct graph_t* graph2 = initialize_graph();
        initialize_graph_positions_classic(graph2);

        int m=((LENGHT /10)+1)*4;
        unsigned int queens_player1[m];
        unsigned int queens_palyer2[m];
        unsigned int *queens[NUM_PLAYERS]={queens_player1,queens_palyer2};
        begining_position(queens);
        initialize1(0,graph1,m,queens);
        initialize2(1,graph2,m,queens);

        for(int i=0; i < LENGHT ; ++i){
            printf("player1 [%d] = %d /// player2[%d] = %d\n", i, queens_player1[i] ,i, queens_palyer2[i]);
        }
        display(graph,queens,m);
        // struct move_t move = {.queen_dst = 3 + LENGHT .queen_src = 3, .arrow_dst = 4 };
        // execute_move(move, );

    return 0;
}














