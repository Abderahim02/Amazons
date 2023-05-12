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
    else if(queen>=length && queen<=length*length-length && queen%length!=0 && queen%length!=length-1){
        return 1;
    }
    return 0;
}

unsigned int *dir_in_board(int pos, struct graph_t* graph, struct player_t player){
    //enum dir_t dir=1;
    unsigned int* all=(unsigned int *)malloc(sizeof(unsigned int)*9 );
    for(int i=0; i<9; i++){
        all[i]=0;
    }
    int count=1;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(pos, i, graph, player)!=UINT_MAX && position_inside(get_neighbor_gen(pos, i, graph, player), graph, i, player)==1){
            all[count]=i;
            count++;
            all[0]++;
        }
    }
    return all;
}

unsigned int *all_opening(struct graph_t* graph, enum dir_t dir, int pos, struct player_t player){
    unsigned int *t=available_dst(graph, dir, pos,player);
    unsigned int length=sqrt(graph->t->size1);
    unsigned int* t_in=(unsigned int *)malloc(sizeof(unsigned int)*(length*length));
    t_in[0]=0;
    int count=1;
    for(int i=1; i<t[0]+1; i++){
        if(position_inside(t[i], graph, dir, player)==1){
            t_in[count]=t[i];
            t_in[0]++;
            count++;
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
    enum dir_t dir=all[(rand()%all[0])+1];
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

unsigned int *liberty_queen(int queen, struct graph_t* graph, struct player_t player){
    enum dir_t dir=0;
    unsigned int degre=0;
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*graph->t->size1);
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
    unsigned int degre=0;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(pos, i, g, p)!=UINT_MAX){ 
            degre++;
        }
    }
    return degre;
}

unsigned int range_free_2_step(unsigned int pos, struct graph_t* g, struct player_t p){

    unsigned int degre=1;
    for(int i=1; i<9; i++){
        if(get_neighbor_gen(pos, i, g, p)!=UINT_MAX){
            degre=degre+1+range_free_1_step(get_neighbor_gen(pos, i, g, p), g, p);
        }
    }
    return degre;
}



unsigned int perfect_dst_for_a_queen(unsigned int queen, struct graph_t* g, struct player_t p){
    unsigned int max_index=0;
    for(enum dir_t i=1; i<9; i++){
        unsigned int* t=available_dst(g, i, queen, p);
        for(unsigned int j=1; j<t[0]+1; j++){
            if(range_free_1_step(max_index, g, p)>=range_free_1_step(t[j+1], g, p)){
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
        unsigned int* t=liberty_queen(p.other_queens[i], g, p);
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
    unsigned int* t=liberty_queen(p.other_queens[queen_index], g, p);
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
    unsigned int* t=liberty_queen(queen, g, p);
    if(t[0]==0){
        free(t);
        return UINT_MAX;
    }
    for(enum dir_t i=1; i<9; i++){
        unsigned int* t2=available_dst(g, i, pos, p);
        if(t2[0]==0){
            free(t2);
            return UINT_MAX;
        }
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
    if(least!=UINT_MAX){
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
    enum dir_t dir=available_dir(pos, g, p);
    dst=random_dst(g, dir, pos, p);
    return dst;
}

unsigned int choise_dsr(int queen, struct player_t p, struct graph_t* g){
    //unsigned int dst_index=perfect_dst_for_a_queen(queen, g, p);
    unsigned int *dir=dir_in_board(queen, g, p);
    if(dir[0]==0){
        free(dir);
        enum dir_t dir2=available_dir(queen, g, p);
        unsigned int dst=random_dst(g, dir2, queen, p);
        return dst;
    }
    unsigned int dst=random_dst(g, dir[1], queen, p);
    free(dir);
    return dst;
}
