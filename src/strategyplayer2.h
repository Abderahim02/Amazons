#ifndef _STRATEGYPLAYER2_H_
#define _STRATEGYPLAYER2_H_

#include "moteur.h"
#include "dir.h"

int position_inside(int queen, struct graph_t* graph, enum dir_t dir, struct player_t player);

unsigned int* dir_in_board(int pos, struct graph_t* graph, struct player_t player);

int opening_dst(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player);

unsigned int *all_opening(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player);

enum dir_t random_dir_in(int queen, struct graph_t* graph, struct player_t player);

#endif