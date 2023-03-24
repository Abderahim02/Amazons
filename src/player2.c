#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* queens[NUM_PLAYERS];
};

struct player player_black;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_black.name = "seeer_seeer";
    return player_black.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_black.id=player_id;
    player_black.graph=graph;
    player_black.num_queens=num_queens;
    *player_black.queens=queens;
 }
 int main(){
    printf("%s\n",get_player_name());
    return 0;
 }


