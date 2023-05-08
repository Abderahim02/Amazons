#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "graph.h"
#include "strategyplayer2.h"
#include <time.h>


struct player_t player_black;

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);


/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
// char const* get_player_name(){
//     player_black.name = "seeer_seeeer";
//     return player_black.name;
// }

char const* get_player_name(){
    // char * pt = (char *) malloc(30 * sizeof(char));
    // strcpy(pt, "seeer_seeeer");
    player_black.name = "seeer_seeeer";
    return player_black.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_black.id=player_id;
    player_black.graph=graph;
    player_black.num_queens=num_queens;
    player_black.turn=0;
    player_black.current_queens=queens[player_id];
    player_black.other_queens=queens[(player_id+1)%2];
}

unsigned int *liberté_queen(int queen, struct graph_t* graph, struct player_t player){
    enum dir_t dir=0;
    unsigned int degre=0;
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*9);
    t[0]=0;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(queen, dir, graph, player)!=UINT_MAX){
            t[degre+1]=get_neighbor_gen(queen, dir, graph, player);
            degre++;
        }
        dir++;
    }
    t[0]=degre;
    return t;
}


unsigned int range_free_1_step(int pos, struct graph_t* g, struct player_t p){
    enum dir_t dir=0;
    unsigned int degre=0;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(pos, dir, g, p)!=UINT_MAX){ 
            degre++;
        }
        dir++;
    }
    return degre;
}

unsigned int range_free_2_step(unsigned int pos, struct graph_t* g, struct player_t p){
    enum dir_t dir=0;
    unsigned int degre=1;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(pos, dir, g, p)!=UINT_MAX){
            degre=degre+1+range_free_1_step(get_neighbor_gen(pos, dir, g, p), g, p);
        }
        dir++;
    }
    return degre;
}

//function that loops over the neighbors of a queen and returns the one that has the max neighbors in all directions
// int best_queen_move_in_direction(struct graph_t *graph, enum dir_t dir, int pos){
//     unsigned int length=sqrt(graph->t->size1);
//     int t[length*2];
//     int i=0;
//     int tmp=pos;
//     //fill the t array with all the neighbors of the queen in the given direction
//     while(get_neighbor(tmp,dir,graph)!=-1){
//         t[i]=get_neighbor(tmp,dir,graph);
//         tmp=t[i];
//         i++;
//     }
//     //calculate the queen_dst that has the max number of neigbors in all directions
//     int max=0;
//     int max_pos=0;
//     for(int j=0;j<i;j++){
//         int cmp=0;
//         for(int k=1;k<9;k++){
//             if(get_neighbor(t[j],k,graph)!=-1){
//                 cmp++;
//             }
//         }
//         if(cmp>max){
//             max=cmp;
//             max_pos=t[j];
//         }
//     return move;
// }

unsigned int perfect_dst_for_a_queen(unsigned int queen, struct graph_t* g, struct player_t p){
    unsigned max_index=0;
    for(enum dir_t i=1; i<9; i++){
        unsigned int* t=available_dst(g, i, queen, p);
        for(int j=1; j<t[0]; j++){
            if(range_free_1_step(max_index, g, p)>range_free_1_step(t[j+1], g, p)){
                max_index=t[j];
            }
        }
        free(t);

    }
    return max_index;
}

unsigned int least_queen_range(struct graph_t* g, struct player_t p){
    unsigned int queen_index=rand()%p.num_queens;
    for(int i=1; i<p.num_queens; i++){
        if(perfect_dst_for_a_queen(p.current_queens[queen_index], g, p)<perfect_dst_for_a_queen(p.current_queens[i], g, p)){
            queen_index=i;
        }
    }
    return queen_index;
}





unsigned int least_queen_move(struct graph_t* g, struct player_t p){
    unsigned int queen_index=0;
    for(int i=0; i<p.num_queens; i++){
        unsigned int* t=liberté_queen(p.other_queens[queen_index], g, p);
        unsigned int* t2=liberté_queen(p.other_queens[i], g, p);
        if(t[0]>=t2[0]){
            free(t);
            free(t2);
            queen_index=i;
        }
        else{
            free(t);
            free(t2);
        }

    }
    return queen_index;
}

unsigned int possible_block(int pos, int queen, struct graph_t* g, struct player_t p){
    unsigned int* t=liberté_queen(queen, g, p);
    for(enum dir_t i=1; i<9; i++){
        unsigned int* t2=available_dst(g, i, pos, p);
        for(int j=1; j<t[0]+1; j++){
            for(int k=1; k<t2[0]+1; k++){
                if(t2[k]==t[j]){
                    unsigned int value=t2[k];
                    free(t);
                    free(t2);
                    return value;
                }
            }
        }
        free(t2);
    }
    free(t);
    return UINT_MAX;
}



unsigned int block_arrow(int pos, struct graph_t* g, struct player_t p){
    unsigned int possible=possible_block(pos, least_queen_move(g, p), g, p);
    if(possible!=UINT_MAX){
        return possible;
    }
    for(int i=0; i<p.num_queens; i++){
        possible=possible_block(pos, p.other_queens[i], g, p);
        if(possible!=UINT_MAX){
            return possible;
        }
    }
    return UINT_MAX;
}

unsigned int choice_block_random_arrow(int pos, struct player_t p, struct graph_t* g){
    unsigned int dst=block_arrow(pos, g, p);
    if(dst!=UINT_MAX){
        return dst;
    }   
    enum dir_t dir=NO_DIR;
    dir=available_dir(pos, g, dir, p);
    dst=random_dst(g, dir, pos, p);
    return dst;
}

unsigned int choise_dsr(int queen, struct player_t p, struct graph_t* g){
    unsigned int dst=perfect_dst_for_a_queen(queen, g, p);
    if(dst!=UINT_MAX){
        return dst;
    }
    enum dir_t dir=NO_DIR;
    dir=available_dir(queen, g, dir, p);
    dst=random_dst(g, dir, queen, p);
    return dst;
}




struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 ){
        execute_move(previous_move,player_black.graph,player_black.other_queens);
        player_black.turn++;
    }
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    
    int r=rand()%player_black.num_queens;
    int queen_index=r;
    int queen=player_black.current_queens[r];
    // we search for available direction for queen, else we change the queen 
    // cmp to avoid the infinite loop 
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    //finds an avaliable direction for a queen
    while(dir==NO_DIR && cmp<player_black.num_queens){
        cmp++;
        queen_index=r;
        queen=player_black.current_queens[queen_index];
        dir=random_dir_in(queen,player_black.graph,player_black);
        r=(r+1)%player_black.num_queens;
    }
    if(dir==NO_DIR){
        cmp=0;
        while(dir==NO_DIR && cmp<player_black.num_queens){
            cmp++;
            queen_index=r;
            queen=player_black.current_queens[queen_index];
            dir=available_dir(queen,player_black.graph,NO_DIR,player_black);
            r=(r+1)%player_black.num_queens;
        }
        if(dir==NO_DIR){
            return move;
        }
    }
    if(player_black.turn<4){
        move.queen_src=queen;
        move.queen_dst=opening_dst(player_black.graph, dir, queen,player_black);
    }
    if(player_black.turn>=4 || move.queen_dst==UINT_MAX){
        move.queen_src=queen;
        move.queen_dst=choise_dsr(queen,player_black,player_black.graph);
     
    }
    if(move.queen_dst==UINT_MAX){
        move.queen_dst=random_dst(player_black.graph,dir,queen, player_black);
    }
     player_black.current_queens[queen_index]=move.queen_dst;
     queen=move.queen_dst;
     enum dir_t dir2=available_dir(queen,player_black.graph,dir,player_black);

     if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
     }
     else {
         move.arrow_dst=choice_block_random_arrow(queen, player_black, player_black.graph);
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
    gsl_spmatrix_uint_free(player_black.graph->t);
    free(player_black.graph);
}

