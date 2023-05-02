
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <math.h>
#include "../src/grid.h"
#include "../src/dir.h"
#include "../src/hole.h"
#include "../src/moteur.h"




void test_execute_move(){
    int LENGHT = 8;
    void *handle1;
    void *handle2;
        char*(*player_name1)(void);
        char*(*player_name2)(void);
        (void) player_name1;
        (void) player_name2;
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
        struct graph_t* graph = initialize_graph(LENGHT);
        initialize_graph_positions_classic(graph);

        struct graph_t* graph1 = initialize_graph(LENGHT);
        initialize_graph_positions_classic(graph1);

        struct graph_t* graph2 = initialize_graph(LENGHT);
        initialize_graph_positions_classic(graph2);

        int m=((LENGHT /10)+1)*4;
        unsigned int queens_player1[m];
        unsigned int queens_palyer2[m];
        unsigned int *queens[NUM_PLAYERS]={queens_player1,queens_palyer2};
        begining_position(queens, LENGHT);
        initialize1(0,graph1,m,queens);
        initialize2(1,graph2,m,queens);

        struct player p = {.id = 0, .graph = graph1, .name = "player1", .num_queens = m, .current_queens = queens[0], .other_queens = queens[1]};
        //print_queens(p);
        struct move_t move = {.queen_dst = 2 + LENGHT, .queen_src = 2, .arrow_dst = 4 };
        execute_move(move, graph1, p.other_queens);
        // print_queens(p);
        printf("\n");
        free_graph(graph);
        free_graph(graph1);
        free_graph(graph2);
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
