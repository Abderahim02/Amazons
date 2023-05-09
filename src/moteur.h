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
struct move_t random_move(struct move_t move, enum dir_t dir, unsigned int queen_index, struct player_t player);
/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx);

//a function that removes a specific element (i.e., edge) from the graph.
void delete_element(struct graph_t* graph, unsigned int i, unsigned int j);


/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens);

//a function that checks if a particular element is present in an array.
int element_in_array(unsigned int *array, unsigned int size, unsigned int element);

/*a function that returns an array of all available destinations for a player given a 
current position on the board. This function takes into account the presence of 
other players and is used to generate valid moves.*/
unsigned int* available_dst_all(struct graph_t *graph, unsigned int pos,const struct player_t player);

/*a function that returns the neighbor of a given position in a particular
 direction, considering the presence of other players.*/
unsigned int get_neighbor_queens(unsigned int pos, enum dir_t direction, struct graph_t* graph, unsigned int* curr_queens,unsigned int* other_queens , unsigned int length);


//a function that returns a random distination
int random_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player);

/*a function that returns an array of available destinations for a player given a 
direction of movement.*/
unsigned int* available_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player);

//a function that returns a random direction in which a player can move.
enum dir_t available_dir(unsigned int queen, struct graph_t *graph, struct player_t player);


//a function that returns the neighbor of a position in specific direction
unsigned int get_neighbor_gen(unsigned int pos, enum dir_t direction, struct graph_t* graph,struct player_t player);


//this function beging positions of the queen for both players 
void begining_position(unsigned int* queens[NUM_PLAYERS], unsigned int length);


//a function that frees the memory allocated for a player
void free_player(struct player_t player);
#endif
