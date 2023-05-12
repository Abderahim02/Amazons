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
//a function that removes a specific element (i.e., edge) from the graph.
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
/*a function that returns an array of all available destinations for a player given a 
current position on the board. This function takes into account the presence of 
other players and is used to generate valid moves.*/
unsigned int* available_dst_all(struct graph_t *graph, unsigned int pos, const struct player_t player){
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*(graph->t->size1-1));
    for(int i = 0 ; i<graph->t->size1-1 ; i++){
        t[i]=UINT_MAX;
    }
    t[0]=0;
    unsigned int i=1;
    for(enum dir_t dir = 1; dir <= 8; dir++) {
        unsigned int tmp=pos;
        while(get_neighbor_gen(tmp, dir, graph, player)!=UINT_MAX){
            t[i]=get_neighbor_gen(tmp, dir, graph, player);
            tmp=t[i];
            i++;
        }
    }
    t[0]=i-1;
    return t;
}
/*a function that returns the neighbor of a given position in a particular
 direction, considering the presence of other players.*/
unsigned int get_neighbor_queens(unsigned int pos, enum dir_t direction, struct graph_t* graph, unsigned int* curr_queens,unsigned int* other_queens , unsigned int length){

    unsigned int row_start=graph->t->p[pos];
    unsigned int row_end=graph->t->p[pos+1];
    for(size_t j=row_start; j<row_end; j++){
        unsigned int neighbor=graph->t->i[j];
        unsigned int dir=graph->t->data[j];
        if(dir==direction && (!element_in_array(other_queens,length,neighbor))&&(!element_in_array(curr_queens,length,neighbor))){
            return neighbor;
        }
    }
    return UINT_MAX;

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
        if((int)move.arrow_dst!=-1 && move.arrow_dst!=UINT_MAX){
            put_arrow(graph, move.arrow_dst);
        }
    }
}
//a function that checks if a particular element is present in an array.
int element_in_array(unsigned int *array, unsigned int size, unsigned int element){
    for(unsigned int j=0; j<size; j++){
        if(array[j]==element){
            return 1;
        }
    }
    return 0;
}

// the function check if there is an available direction for the the queen else return NO_DIR
enum dir_t available_dir(unsigned int queen, struct graph_t *graph, struct player_t player){
    enum dir_t dir=rand()%8+1;
    int cmp=0;
    while(get_neighbor_gen(queen,dir,graph,player)==UINT_MAX  && cmp<9){
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


/*a function that returns an array of available destinations for a player given a 
direction of movement.*/
unsigned int* available_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player){
    unsigned int length=sqrt(graph->t->size1);
    unsigned int* t=(unsigned int *)malloc(sizeof(unsigned int)*(length*length));
    for(int i = 0 ; i<length*length; i++){
        t[i]=UINT_MAX;
    }
    t[0]=0;
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

//a function that returns a random distination
int random_dst(struct graph_t *graph, enum dir_t dir, unsigned int pos,struct player_t player){
    unsigned int *t=available_dst(graph, dir, pos,player);
    int dst=t[(rand()%t[0])+1];
    free(t);
    return dst;

}



//a function that returns the neighbor of a position in specific direction
unsigned int get_neighbor_gen(unsigned int pos, enum dir_t direction, struct graph_t* graph, struct player_t player){
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

//return a random move for the queen 
struct move_t random_move(struct move_t move, enum dir_t dir, unsigned int queen_index, struct player_t player){
    move.queen_src=player.current_queens[queen_index];
    move.queen_dst=random_dst(player.graph,dir,player.current_queens[queen_index], player);
    player.current_queens[queen_index]=move.queen_dst;
    unsigned int queen=move.queen_dst;
    enum dir_t dir2=available_dir(queen,player.graph,player);
    if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
    }
    else {
        move.arrow_dst=random_dst(player.graph,dir2,move.queen_dst,player);
    }
    return move;
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

//a function that frees the memory allocated for a player
void free_player(struct player_t player){
    free(player.current_queens);
    free(player.other_queens);
}