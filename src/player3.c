#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "graph.h"
#include "strategyplayer3.h"
#include <time.h>


struct player_t player_brown;

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);


/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
// char const* get_player_name(){
//     player_brown.name = "seeer_seeeer";
//     return player_brown.name;
// }

char const* get_player_name(){
    // char * pt = (char *) malloc(30 * sizeof(char));
    // strcpy(pt, "seeer_seeeer");
    player_brown.name = "aji_aji";
    return player_brown.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_brown.id=player_id;
    player_brown.graph=graph;
    player_brown.num_queens=num_queens;
    player_brown.turn=0;
    player_brown.current_queens=queens[player_id];
    player_brown.other_queens=queens[(player_id+1)%2];
}



struct move_t play(struct move_t previous_move){
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 ){
        execute_move(previous_move,player_brown.graph,player_brown.other_queens);
        player_brown.turn++;
    }
    printf("player_brown queens befoe move are :");
    for(int i=0; i<player_brown.num_queens; ++i){
        printf(" %d ", player_brown.current_queens[i]);
    }
    printf("\n");
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    
    int r=rand()%player_brown.num_queens;
    int queen_index=r;
    int queen=player_brown.current_queens[r];
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    while(dir==NO_DIR && cmp<player_brown.num_queens){
        cmp++;
        queen_index=r;
        queen=player_brown.current_queens[queen_index];
        dir=random_dir_in(queen,player_brown.graph,player_brown);
        r=(r+1)%player_brown.num_queens;
    }
    if(dir==NO_DIR){
        cmp=0;
        while(dir==NO_DIR && cmp<player_brown.num_queens){
            cmp++;
            queen_index=r;
            queen=player_brown.current_queens[queen_index];
            dir=available_dir(queen,player_brown.graph,NO_DIR,player_brown);
            r=(r+1)%player_brown.num_queens;
        }
        if(dir==NO_DIR){
            return move;
        }
    }
    if(player_brown.turn<4){
        printf("opening\n");
        move.queen_src=queen;
        move.queen_dst=opening_dst(player_brown.graph, dir, queen,player_brown);
    }
    else if(player_brown.turn>=4 || move.queen_dst==UINT_MAX){
        printf("choise dsr\n");
        move.queen_src=queen;
        move.queen_dst=choise_dsr(queen,player_brown,player_brown.graph);
     
    }
    move.queen_src=queen;
    move.queen_dst=choise_dsr(queen,player_brown,player_brown.graph);
    player_brown.current_queens[queen_index]=move.queen_dst;
    queen=move.queen_dst;
    enum dir_t dir2=available_dir(queen,player_brown.graph,dir,player_brown);

    if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
    }
    else {
        move.arrow_dst=choice_block_random_arrow(queen, player_brown, player_brown.graph);
    }
    printf("queen_src %d queen_dst %d arrox %d\n", move.queen_src, move.queen_dst, move.arrow_dst);
    execute_move(move,player_brown.graph,player_brown.current_queens);
    //printf("queen_src %d queen_dst %d arrox %d\n", move.queen_src, move.queen_dst, move.arrow_dst);
    printf("player_brown queens after move are :");
    for(int i=0; i<player_brown.num_queens; ++i){
        printf(" %d ", player_brown.current_queens[i]);
    }
    printf("\n");
    return move;  
}



struct move_t play2(struct move_t previous_move){
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 )
        execute_move(previous_move,player_brown.graph,player_brown.other_queens);
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    int r=rand()%player_brown.num_queens;
    int queen_index=r;
    int queen=player_brown.current_queens[r];
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    while(dir==NO_DIR && cmp<player_brown.num_queens){
        cmp++;
        queen_index=r;
        queen=player_brown.current_queens[queen_index];
        dir=available_dir(queen,player_brown.graph,NO_DIR,player_brown);
        r=(r+1)%player_brown.num_queens;
       
    }
    if(dir==NO_DIR){
        return move;
    }
     move.queen_src=queen;
     move.queen_dst=random_dst(player_brown.graph,dir,move.queen_src, player_brown);
     player_brown.current_queens[queen_index]=move.queen_dst;
     queen=move.queen_dst;
     enum dir_t dir2=available_dir(queen,player_brown.graph,dir,player_brown);

     if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
     }
     else {
         move.arrow_dst=random_dst(player_brown.graph,dir2,move.queen_dst,player_brown);
     }
    execute_move(move,player_brown.graph,player_brown.current_queens);
    return move;  
}


int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    return get_neighbor_gen(pos, dir, graph, player_brown);
}

void finalize(){
    free(player_brown.current_queens);
    free(player_brown.other_queens);    
    gsl_spmatrix_uint_free(player_brown.graph->t);
    free(player_brown.graph);
}

