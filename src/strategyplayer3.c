#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "strategyplayer3.h"

int position_inside(int queen, struct graph_t* graph, enum dir_t dir, struct player_t player){
    unsigned int length=sqrt(graph->t->size1);
    if(queen==-1 || queen ==UINT_MAX){
        return 0;
    }
    else if(queen>length && queen<length*length-length && queen!=0 && queen%length!=length-1){
        return 1;
    }
    return 0;
}

unsigned int *dir_in_board(int pos, struct graph_t* graph, struct player_t player){
    enum dir_t dir=1;
    unsigned int* all=(unsigned int *)malloc(sizeof(unsigned int)*9 );
    all[0]=0;
    int count=1;
    for(int i=1; i<9; i++){
        if(position_inside(get_neighbor_gen(pos, dir, graph, player), graph, dir, player)==1){
            all[count]=dir;
            count++;
            all[0]++;
        }
        dir++;
    }
    return all;
}

unsigned int *all_opening(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player){
    unsigned int *t=available_dst(graph, dir, pos,player);
    unsigned int length=sqrt(graph->t->size1);
    unsigned int* t_in=(unsigned int *)malloc(sizeof(unsigned int)*(length*2+1));
    t_in[0]=0;
    for(int i=0; i<t[0]; i++){
        if(position_inside(t[i+1], graph, dir, player)==1){
            t_in[i+1]=t[i+1];
            t_in[0]++;
        }
    }
    free(t);
    return t_in;
}

enum dir_t random_dir_in(int queen, struct graph_t* graph, struct player_t player){
    unsigned int* all=dir_in_board(queen, graph, player);
    if(all[0]==0){
        free(all);
        return NO_DIR;
    }
    enum dir_t dir=all[rand()%all[0]+1];
    free(all);
    return dir;
}

int opening_dst(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player){
    unsigned int *t=all_opening(graph, dir, pos,player);
    if(t[0]==0){
        free(t);
        return UINT_MAX;
    }
    int dst=t[(rand()%t[0])+1];
    free(t);
    return dst;
}

unsigned int *liberté_queen(int queen, struct graph_t* graph, struct player_t player){
    enum dir_t dir=0;
    unsigned int degre=0;
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*10);
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
        if(perfect_dst_for_a_queen(p.other_queens[queen_index], g, p)<perfect_dst_for_a_queen(p.other_queens[i], g, p)){
            queen_index=i;
        }
    }
    return queen_index;
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
    for(unsigned int i=0; i<p.num_queens; i++){
        if(res[queen_index]==0){
            queen_index=i;
        }
        else if(res[queen_index]>res[i]){
            queen_index=i;
        }
    }
    unsigned int* t=liberté_queen(p.other_queens[queen_index], g, p);
    if(t[0]==0){
        free(res);
        free(t);
        return UINT_MAX;
    }
    free(t);
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



unsigned int block_arrow(int pos, struct graph_t* g, struct player_t p){
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
