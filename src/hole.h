#ifndef _HOLE_H_
#define _HOLE_H_

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <math.h>

#include "graph.h"
#include "dir.h"

void  make_hole(struct graph_t *g, int id, int size);


void  make_zero_i_j(struct graph_t *g, int i, int j);
#endif // _AMAZON_PLAYER_H_
