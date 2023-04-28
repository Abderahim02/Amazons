
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <math.h>
#include "../src/grid.h"
#include "../src/dir.h"
#include "../src/hole.h"
#include "../src/moteur.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#ifndef NUM_PLAYERS
#define NUM_PLAYERS 2
#endif
#ifndef N
    #define N 8
#endif



// void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number){
//     int *t = graph_table(graph);
//     table(queens,t,queens_number);
//     for(int i=0;i<LENGHT*LENGHT;i++){
//         if(i!=0 && i%LENGHT==0) printf("\n");
//         if(t[i]==-1) printf("  ");
//     else printf("%d ",t[i] );
//     }
//     printf("\n");
//     free(t);
// }

void begining_position(unsigned int* queens[NUM_PLAYERS]){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((LENGHT/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=2*i+LENGHT*(LENGHT-1);
        tmp++;
        t[tmp]=LENGHT-1-2*i+LENGHT*(LENGHT-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=LENGHT*(LENGHT-1)-LENGHT*2*i;
        tmp++;
        t[tmp]=LENGHT*(LENGHT-1)-LENGHT*2*i+LENGHT-1;
        tmp++;
    }
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=2*i;
        tmp++;
        t2[tmp]=LENGHT-1-2*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=LENGHT*2*(i);
        tmp++;
        t2[tmp]=LENGHT*2*i+LENGHT-1;
        tmp++;
    }
    //printf("tmp2=%d \n",tmp);
}
void test_execute_move(){
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

        struct player p = {.id = 0, .graph = graph1, .name = "player1", .num_queens = m, .current_queens = queens[0], .other_queens = queens[1]};
        //print_queens(p);
        struct move_t move = {.queen_dst = 2 + LENGHT, .queen_src = 2, .arrow_dst = 4 };
        execute_move(move, graph1, p.other_queens);
        // print_queens(p);
        printf("\n");
}

int main(){
    // struct graph_t * g= initialize_graph(9);
    // initialize_graph_positions_classic(g);
    // printf("op %d\n",(int)sqrt(g->num_vertices));
    // make_hole(g,1,6);
    // print_sparse_matrix(g->t);
    // free_graph(g);
    return 0;
}
// int main(){
//     test_execute_move();
//     return 1;
// }