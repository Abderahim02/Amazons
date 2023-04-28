#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "grid.h"
#include <time.h>


struct player player_black;

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);


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
    player_black.turn=0;
    unsigned int m=((graph->num_vertices/10)+1)*4;
    player_black.current_queens=(unsigned int *)malloc(sizeof(unsigned int)*m);

    player_black.other_queens=(unsigned int *)malloc(sizeof(unsigned int)*m);
    for(unsigned int i=0;i<m;i++){
    player_black.current_queens[i]=queens[player_id][i];
    player_black.other_queens[i]=queens[(player_id+1)%2][i];
    }
}






struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 )
        execute_move(previous_move,player_black.graph,player_black.other_queens);
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    int r=rand()%player_black.num_queens;
    int queen=player_black.current_queens[r];

    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    while(dir==NO_DIR && cmp<player_black.num_queens){
        cmp++;
        queen=player_black.current_queens[r];
        dir=available_dir(queen,player_black.graph,NO_DIR, player_black);
        r=(r+1)%player_black.num_queens;
    }
    
    if(dir==NO_DIR){
        free_player(player_black);
        return move;
    }
  // printf("dir=%d\n",dir);
     move.queen_src=queen;
     move.queen_dst=random_dst(player_black.graph,dir,queen, player_black);
     player_black.current_queens[r]=move.queen_dst;
     queen=move.queen_dst;
     enum dir_t dir2=available_dir(queen,player_black.graph,dir, player_black);
     if(dir2==NO_DIR){
        move.arrow_dst=-1;
     }
     else {
        //printf("queen %d\n",queen);
         move.arrow_dst=random_dst(player_black.graph,dir2,queen, player_black);
     }
    execute_move(move,player_black.graph,player_black.current_queens);
    return move;  
}


int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    return get_neighbor_gen(pos, dir, graph, player_black);
}

void finalize(){
    free(player_black.current_queens);
    free(player_black.other_queens);
}

