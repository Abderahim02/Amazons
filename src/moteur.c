#include <stdio.h>
#include "moteur.h"
#include <math.h>

#include <gsl/gsl_spmatrix.h>

#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx){
    for(unsigned int i=0; i< graph->num_vertices; i++){
        delete_element(graph, i, idx);
    }
    for(unsigned int i=0; i<graph->num_vertices; i++){
        delete_element(graph, idx, i);
    }
}

void delete_element(struct graph_t* graph, unsigned int i, unsigned int j){
    size_t row_start=graph->t->p[i];
    size_t row_end=graph->t->p[i+1];

    for(size_t k=row_start; k<row_end; k++){
        if(graph->t->i[k]==j){
            for(size_t l=k; l<graph->t->nz-1; l++){
                graph->t->data[l]=graph->t->data[l+1];
                graph->t->i[l]=graph->t->i[l+1];
            }
            graph->t->nz--;
            for(size_t l=i+1; l<graph->t->size1+1; l++){
                graph->t->p[l]--;
            }
        }
    }
}

/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens){
    unsigned int length=sqrt(graph->t->size1);
    if((int)move.queen_dst>=0){
    int queen_number = 4*(length/10 + 1 );
    for(int  i =0; i < queen_number ; ++i ){
        if ( queens[i] == move.queen_src ){ //we look for the ex_position and then we put the new position
            queens[i] = move.queen_dst;
            break;
        }
    }
    if((int)move.arrow_dst!=-1 || move.arrow_dst!=UINT_MAX){
        put_arrow(graph, move.arrow_dst);
    }
    }
}

int element_in_array(unsigned int *array, unsigned int size, unsigned int element){
    for(unsigned int j=0; j<size; j++){
        if(array[j]==element){
            return 1;
        }
    }
    return 0;
}

enum dir_t available_dir(unsigned int queen, struct graph_t *graph, enum dir_t direction,struct player player){
    enum dir_t dir=rand()%8+1;
    int cmp=0;
    while((get_neighbor_gen(queen,dir,graph,player)==UINT_MAX || dir==direction) && cmp<9){
        dir++;
        dir=dir%9;
        if(dir==0) dir++;
        cmp++;
    }
    if(cmp==9){
        return NO_DIR;
    }
    return dir;
}

unsigned int* available_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player player){
    unsigned int length=sqrt(graph->t->size1);
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*(length*2+1));
    int i=1;
    unsigned int tmp=pos;
    while(get_neighbor_gen(tmp,dir,graph,player)!=UINT_MAX){
        t[i]=get_neighbor_gen(tmp,dir,graph,player);
        tmp=t[i];
        i++;
    }
    t[0]=i-1;
    return t;

}

int random_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player player){
    unsigned int *t=available_dst(graph, dir, pos,player);
    int dst=t[(rand()%t[0])+1];
    free(t);
    return dst;

}




unsigned int get_neighbor_gen(unsigned int pos, enum dir_t direction, struct graph_t* graph, struct player player){
    if(direction==NO_DIR){
            return UINT_MAX;
    }
    unsigned int row_start=graph->t->p[pos];
    unsigned int row_end=graph->t->p[pos+1];
    for(size_t j=row_start; j<row_end; j++){
        unsigned int neighbor=graph->t->i[j];
        unsigned int dir=graph->t->data[j];
        if(dir==direction && (!element_in_array(player.other_queens,player.num_queens,neighbor))&&(!element_in_array(player.current_queens,player.num_queens,neighbor))){
            return neighbor;
        }
    }
    return UINT_MAX;

}

//this function beging positions of the queen for both players 
void begining_position(unsigned int* queens[NUM_PLAYERS], unsigned int length){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((length/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=(1+length/7)*i+length*(length-1);
        tmp++;
        t[tmp]=length-1-(1+length/7)*i+length*(length-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=length*(length-1)-length*(1+length/7)*i;
        tmp++;
        t[tmp]=length*(length-1)-length*(1+length/7)*i+length-1;
        tmp++;
    }
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=(1+length/7)*i;
        tmp++;
        t2[tmp]=length-1-(1+length/7)*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=length*(1+length/7)*(i);
        tmp++;
        t2[tmp]=length*(1+length/7)*i+length-1;
        tmp++;
    }
}

void free_player(struct player player){
    free(player.current_queens);
    free(player.other_queens);
}