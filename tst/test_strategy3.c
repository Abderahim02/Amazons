#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#include "../src/move.h"
#include "../src/strategyplayer3.h"
#include "../src/server_functions.h"

extern struct graph_t * initialize_graph(unsigned int length);
extern void initialize_graph_positions_classic(struct graph_t* g);
// extern void print_sparse_matrix(gsl_spmatrix_uint *mat);
extern void free_graph(struct graph_t* g);


extern void  make_zero_i_j(struct graph_t *g, int i, int j);

void test_all_opening(){
    printf("-----Started Testing all_opening---------- \n");

    unsigned int size=5;
    struct graph_t* graph = initialize_graph(size);
    //enum dir_t DIR_NORTH=1, DIR_NE=2, DIR_WEST=3,  DIR_SE=4, DIR_SOUTH=5, DIR_SW=6, DIR_EAST=7,  DIR_NW=8;
    
    unsigned int m=((size/10)+1)*4;
    unsigned int white_queens[m];
    unsigned int black_queens[m];
    struct player_t player;
    player.current_queens=black_queens;
    player.other_queens=white_queens;
    unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
    begining_position(queens, size);
    
    display(graph, queens, m);
    // unsigned int *all=dir_in_board(22, graph, player);
    // printf("%d \n", all[0]);
    // printf("%d \n", all[1]);
    // printf("%d \n", all[2]);
    // unsigned int *op=all_opening(graph, 7, 11, player);
    // printf("%d \n", op[0]);
    // enum dir_t dir=random_dir_in(1, graph, player);
    // printf("la direction est %d\n", dir);
    delete_element(graph, 0, 1);
    // unsigned int degre=range_free_1_step(4, graph, player);
    // printf("le degre est %d\n", degre);
    //delete_element(graph, 0, 1);
    // printf("le neighbor %d\n", get_neighbor_gen(0, 7, graph, player));
    printf("QEUFH %d\n", player.current_queens[0]);
    // free(op);
    // free(all);
    free_graph(graph);
}