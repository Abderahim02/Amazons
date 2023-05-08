#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "graph.h"
#include "player.h"
#include "dir.h"


#define WHITE 1
#define BLACK 0
#define CASE -1

#ifndef NUM_PLAYERS
    #define NUM_PLAYERS 2
#endif

struct player_t {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
    unsigned int turn;
};

/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx);


void delete_element(struct graph_t* graph, unsigned int i, unsigned int j);


/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens);

int element_in_array(unsigned int *array, unsigned int size, unsigned int element);
unsigned int* available_dst_all(struct graph_t *graph, unsigned int pos,const struct player_t player);
unsigned int get_neighbor_queens(unsigned int pos, enum dir_t direction, struct graph_t* graph, unsigned int* curr_queens,unsigned int* other_queens , unsigned int length);

/*a test function */
void test_execute_move();

int random_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player);

unsigned int* available_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player);

// unsigned int range_free_1_step(unsigned int pos, struct graph_t* g, struct player_t p);

unsigned int least_queen_move(struct graph_t* g, struct player_t p);

enum dir_t available_dir(unsigned int queen, struct graph_t *graph, enum dir_t direction,struct player_t player);

void begining_position(unsigned int* queens[NUM_PLAYERS], unsigned int length);

void free_player(struct player_t player);


unsigned int get_neighbor_gen(unsigned int pos, enum dir_t direction, struct graph_t* graph,struct player_t player);

#endif
