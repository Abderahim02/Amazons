#ifndef _STRATEGYPLAYER3_H_
#define _STRATEGYPLAYER3_H_

#include "moteur.h"

int position_inside(int queen, struct graph_t* graph, enum dir_t dir, struct player_t player);

unsigned int* dir_in_board(int pos, struct graph_t* graph, struct player_t player);

int opening_dst(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player);

unsigned int *all_opening(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player);

enum dir_t random_dir_in(int queen, struct graph_t* graph, struct player_t player);


unsigned int *liberty_queen(int queen, struct graph_t* graph, struct player_t player);


unsigned int range_free_1_step(int pos, struct graph_t* g, struct player_t p);


unsigned int range_free_2_step(unsigned int pos, struct graph_t* g, struct player_t p);

unsigned int perfect_dst_for_a_queen(unsigned int queen, struct graph_t* g, struct player_t p);


unsigned int least_queen_range(struct graph_t* g, struct player_t p);


unsigned int least_queen_move(struct graph_t* g, struct player_t p);

unsigned int possible_block(int pos, int queen, struct graph_t* g, struct player_t p);

unsigned int block_arrow(int pos, struct graph_t* g, struct player_t p);


unsigned int choice_block_random_arrow(int pos, struct player_t p, struct graph_t* g);

unsigned int choise_dsr(int queen, struct player_t p, struct graph_t* g);

#endif