#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "graph.h"
#include "player.h"
#include "server.h"


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx);

/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens);

int element_in_array(unsigned int *t, int size, unsigned int x);

/*a test function */
void test_execute_move();

int random_dst(struct graph_t *graph, enum dir_t dir, int pos);

enum dir_t available_dir(int queen, struct graph_t *graph, enum dir_t direction);



int get_neighbor_gen(int pos, enum dir_t dir, struct graph_t* graph, struct player player);

#endif
