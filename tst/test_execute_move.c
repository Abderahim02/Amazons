
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "dir.h"
#include <dlfcn.h>
#include <math.h>
#include "hole.h"
#include "moteur.h"

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
        print_queens(p);
        display(graph1,queens,m);
        struct move_t move = {.queen_dst = 2 + LENGHT, .queen_src = 2, .arrow_dst = 4 };
        execute_move(move, graph1, p.other_queens);
        print_queens(p);
        printf("\n");
        display(graph1, queens, m);
}
// int main(){
//     test_execute_move();
//     return 1;
// }