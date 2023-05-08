#ifndef _SERVER_FUNCTIONS_H_
#define _SERVER_FUNCTIONS_H_
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <time.h>
#include <dlfcn.h>
#include <math.h>

#include "hole.h"
#include "moteur.h"








/*This function parses command-line arguments to extract the game 
settings, including the game type, board size, and number of turns.
It takes in argc and argv[] parameters from the command line and 
sets the values of type, length, and turns pointers.*/
void get_opt(int argc, char* argv[], char* type, unsigned int *length, unsigned int* turns);

/*This function is used to display the current state of the game 
using the console. It takes in the game board, the positions of 
the queens, and the number of queens as parameters. It then 
displays the game board and the queen positions on the console.*/
void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number);

/*This function is used to display the current state of the game 
using the SDL library. It takes in the game board, the positions 
of the queens, the number of queens, and the size of the window 
as parameters. It then displays the game board and the queen 
positions on the screen.*/
void sdl_display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number, int size);


/*This function takes in the positions of the queens and the number of queens and 
creates a table representation of the game board, where each 
cell in the table represents a position on the board, and a value 
of 1 indicates that there is a queen in that position.*/
void table(unsigned int* queens[NUM_PLAYERS], int *t, unsigned int queens_number);


/*This function creates a table representation of the game board using the graph data structure. 
It returns an integer pointer to the table.*/
int *graph_table(struct graph_t *graph);

struct graph_t *graph_cpy(const struct graph_t *graph);

/*This function allocates memory for a table with the given length and returns 
a pointer to the table.*/
unsigned int* allouer_table(unsigned int length);


/*This function copies the positions of the queens from one array 
to another. It takes in the source and destination arrays of the positions
 of the queens and the number of queens as parameters.*/
void queens_copy(unsigned int *queen[NUM_PLAYERS],unsigned int *q[NUM_PLAYERS] ,int m);

/*This function is used to start a new game by choosing the game 
mode. It returns an integer indicating the chosen player.*/
int start_player();

/*This function takes in the current player and returns the next player's number.*/
int next_player(int player);


#endif
