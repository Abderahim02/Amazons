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
        for(unsigned int j=1; j<t[0]; j++){
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
    for(unsigned int i=1; i<p.num_queens; i++){
        if(perfect_dst_for_a_queen(p.current_queens[queen_index], g, p)<perfect_dst_for_a_queen(p.current_queens[i], g, p)){
            queen_index=i;
        }
    }
    return queen_index;
}


unsigned int *liberté_queen(int queen, struct graph_t* graph, struct player player){
    enum dir_t dir=0;
    unsigned int degre=0;
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*9);
    t[0]=0;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(queen, i, graph, player)!=UINT_MAX){
            t[degre+1]=get_neighbor_gen(queen, dir, graph, player);
            degre++;
        }
    }
    t[0]=degre;
    return t;
}


unsigned int least_queen_move(struct graph_t* g, struct player_t p){
    unsigned int queen_index=0;
    unsigned int* res=malloc(sizeof(unsigned int)*p.num_queens);
    for(unsigned int i=0; i<p.num_queens; i++){
        unsigned int* t=liberté_queen(p.other_queens[i], g, p);
        res[i]=t[0];
        free(t);
    }
    queen_index=0;
    for(unsigned int i=1; i<p.num_queens; i++){
        if(res[queen_index]==0){
            queen_index=i;
        }
        else if(res[queen_index]>res[i]){
            queen_index=i;
        }
    }
    unsigned int* t=liberté_queen(p.other_queens[queen_index], g, p);
    if(t[0]==0){
        return UINT_MAX;
    }
    free(res);
    return queen_index;
}

unsigned int possible_block(int pos, int queen, struct graph_t* g, struct player_t p){
    unsigned int* t=liberté_queen(queen, g, p);
    for(enum dir_t i=1; i<9; i++){
        unsigned int* t2=available_dst(g, i, pos, p);
        for(unsigned int j=1; j<t[0]+1; j++){
            for(unsigned int k=1; k<t2[0]+1; k++){
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



unsigned int block_arrow(int pos, struct graph_t* g, struct player p){
    unsigned int possible=0;
    unsigned int least=least_queen_move(g, p);
    if(least==UINT_MAX){
        int i=0;
        while(i<p.num_queens && possible==UINT_MAX){
            possible=possible_block(pos, p.other_queens[i], g, p);
            i++;
        }
        if(possible!=UINT_MAX){
            return possible;
        }
    }
    else{
        possible=possible_block(pos, p.other_queens[least], g, p);
        if(possible!=UINT_MAX){
            return possible;
        }
    }
    for(unsigned int i=0; i<p.num_queens; i++){
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




struct move_t play2(struct move_t previous_move){
    if(previous_move.queen_dst!= (unsigned int) -1 && previous_move.queen_dst!= (unsigned int) -1 ){
        execute_move(previous_move,player_brown.graph,player_brown.other_queens);
        player_brown.turn++;
    }
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
    // if(player_brown.turn<4){
    //     move.queen_src=queen;
    //     move.queen_dst=opening_dst(player_brown.graph, dir, queen,player_brown);
    // }
    // if(player_brown.turn>=4 || move.queen_dst==UINT_MAX){
    //     move.queen_src=queen;
    //     move.queen_dst=choise_dsr(queen,player_brown,player_brown.graph);
     
    // }
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
    execute_move(move,player_brown.graph,player_brown.current_queens);
    return move;  
}

struct move_t play(struct move_t previous_move){
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
     move.queen_dst=random_dst(player_brown.graph,dir,queen, player_brown);
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

