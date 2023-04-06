#include<stdio.h>
#include <stdlib.h>
#include <string.h>

#include "player.h"


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
   unsigned int* current_queens;
    unsigned int* other_queens;
};

struct player player_blanc;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_blanc.name = "Dir_niya";
    return player_blanc.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_blanc.id=player_id;
    player_blanc.graph=graph;
    player_blanc.num_queens=num_queens;
    int m=((graph->num_vertices/10)+1)*4;
    player_blanc.current_queens=malloc(sizeof(unsigned int)*num_queens);

     player_blanc.other_queens=malloc(sizeof(unsigned int)*num_queens);
    for(int i=0;i<num_queens;i++){
    player_blanc.current_queens[i]=queens[player_id][i];
    player_blanc.other_queens[i]=queens[(player_id+1)%2][i];
    }
  

 }
 


