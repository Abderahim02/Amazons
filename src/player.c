#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"


struct player {
    unsigned int player_id;
    char const* player_name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* queens[NUM_PLAYERS];
};

struct player player_black;
struct player player_White;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_black.player_name = "Dir_niya";
    return player_black.player_name;
}

int main(){
    printf("%s", get_player_name());
    return 0;
}