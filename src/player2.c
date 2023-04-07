#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "graph.h"
#include <time.h>


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

struct player player_black;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_black.name = "seeer_seeeer";
    return player_black.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
   player_black.id=player_id;
    player_black.graph=graph;
    player_black.num_queens=num_queens;
    int m=((graph->num_vertices/10)+1)*4;
    player_black.current_queens=malloc(sizeof(unsigned int));

    player_black.other_queens=malloc(sizeof(unsigned int)*m);
    for(int i=0;i<m;i++){
    player_black.current_queens[i]=queens[player_id][i];
    player_black.other_queens[i]=queens[(player_id+1)%2][i];
    }
  
}


struct move_t play(struct move_t previous_move){
    srand(600);
    execute_move(previous_move,player_black.graph,player_black.other_queens);
    int r=rand()%player_black.num_queens;
    
}


