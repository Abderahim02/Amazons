
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

struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

void begining_position(unsigned int* queens[NUM_PLAYERS]);


// void print_queens(struct player p, int num_queens );

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number);


void table(unsigned int* queens[NUM_PLAYERS], int *t, int queens_number);

int *graph_table(struct graph_t *graph);


