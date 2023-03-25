#include "move.h"
#include "grid.h"


struct set{
    unsigned int taille;
    struct move_t positions[GRID_SIZE];
};

void available_moves(struct graph_t * graph, struct set* set);




