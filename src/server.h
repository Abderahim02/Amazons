
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "dir.h"
#include <dlfcn.h>
#include <math.h>
#include "hole.h"
#include "moteur.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>



void begining_position(unsigned int* queens[NUM_PLAYERS]);


// void print_queens(struct player p, int num_queens );

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number);


void table(unsigned int* queens[NUM_PLAYERS], int *t, int queens_number);

int *graph_table(struct graph_t *graph);

int start_player();

int next_player(int player);


