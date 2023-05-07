#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

#include "strategyplayer2.h"

int position_inside(int queen, struct graph_t* graph, enum dir_t dir, struct player player){
    unsigned int length=sqrt(graph->t->size1);
    if(queen==-1 || queen ==UINT_MAX){
        return 0;
    }
    else if(queen>length && queen<length*length-length && queen!=0 && queen%length!=length-1){
        return 1;
    }
    return 0;
}

unsigned int *dir_in_board(int pos, struct graph_t* graph, struct player player){
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

unsigned int *all_opening(struct graph_t* graph, enum dir_t dir, int pos, struct player player){
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

enum dir_t random_dir_in(int queen, struct graph_t* graph, struct player player){
    unsigned int* all=dir_in_board(queen, graph, player);
    if(all[0]==0){
        return NO_DIR;
    }
    enum dir_t dir=all[rand()%all[0]+1];
    free(all);
    return dir;
}

int opening_dst(struct graph_t* graph, enum dir_t dir, int pos, struct player player){
    unsigned int *t=all_opening(graph, dir, pos,player);
    if(t[0]==0){
        return UINT_MAX;
    }
    int dst=t[(rand()%t[0])+1];
    free(t);
    return dst;
}