#ifndef _HOLE_H_
#define _HOLE_H_

#include "graph.h"
#include "dir.h"

void  make_hole(struct graph_t *g, int id, int size);

void remove_node(int n,gsl_spmatrix_uint *mat);

void hollow_matrix(gsl_spmatrix_uint *mat,int *t, int len );

#endif // _AMAZON_PLAYER_H_
