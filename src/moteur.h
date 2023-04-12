#ifndef _MOTEUR_H_
#define _MOTEUR_H_

#include "graph.h"
#include "player.h"
/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx);

/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens);

/*a test function */
void test_execute_move();
#endif
