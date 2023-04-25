#include <stdio.h>
#include "moteur.h"
#include "grid.h"

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>
#include <stddef.h>

/*this function puts an arrow in the position idx in the graph, it puts NO_DIT with all of its neighbors*/
void put_arrow(struct graph_t* graph, unsigned int idx){
    for(int i=0; i < LENGHT*LENGHT; ++i){
        if(gsl_spmatrix_uint_get(graph->t, idx, i) != NO_DIR ){
            gsl_spmatrix_uint_set(graph->t, idx, i, NO_DIR );
            gsl_spmatrix_uint_set(graph->t, i, idx, NO_DIR);
        }
    }
}

/*this function updates the graph taken as argument and the array of positions queens with the new 
position of the queen after the move*/
void execute_move(struct move_t move, struct graph_t *graph, unsigned int *queens){
   
   // printf("%d %d\n",move.arrow_dst, move.queen_dst);
    if((int)move.queen_dst>=0){
    int queen_number = 4*(LENGHT/10 + 1 );
    for(int  i =0; i < queen_number ; ++i ){
        if ( queens[i] == move.queen_src ){ //we look for the ex_position and then we put the new position
            queens[i] = move.queen_dst;
            break;
        }
    }
    if((int)move.arrow_dst!=-1 || move.arrow_dst!=UINT_MAX){
        put_arrow(graph, move.arrow_dst);
    }
     //here we updates the graph, we make the position arrow_dst isolated
    // print_sparse_matrix(graph->t);
}
}


int element_in_array(unsigned int *t, int size,unsigned int x){
    for(int i=0;i<size;i++){
        if(t[i]==x) return 1;
    }
    return 0;
}


enum dir_t available_dir(int queen, struct graph_t *graph, enum dir_t direction, struct player player){
    enum dir_t dir=rand()%8+1;
    int cmp=0;
    while((get_neighbor_gen(queen,dir,graph, player)==-1 || dir==direction) && cmp<9){
        dir++;
        dir=dir%9;
        cmp++;
    }
    if(cmp==9){
        return NO_DIR;
    }
    return dir;
}

int random_dst(struct graph_t *graph, enum dir_t dir, int pos, struct player player){
    int t[LENGHT*2];
    int i=0;
    int tmp=pos;
    while(get_neighbor_gen(tmp,dir,graph, player)!=-1){
        t[i]=get_neighbor_gen(tmp,dir,graph, player);
        tmp=t[i];
        i++;
    }
    return t[rand()%i];

}




int get_neighbor_gen(int pos, enum dir_t dir, struct graph_t* graph, struct player player){
    int m=4*(LENGHT/10 + 1);
    switch (dir)
    {
    case 1:
        if(pos-LENGHT >= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !element_in_array(player.other_queens,m,pos-LENGHT) &&  !element_in_array(player.current_queens,m,pos-LENGHT)){
            return pos-LENGHT;
        }
        break;
    case 3:
        if(pos-1>= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !element_in_array(player.other_queens,m,pos-1) && !element_in_array(player.current_queens,m,pos-1)){
            return pos-1;
        }
        break;
    case 5:
        if(pos+LENGHT<= LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !element_in_array(player.other_queens,m,pos+LENGHT) && !element_in_array(player.current_queens,m,pos+LENGHT)){
        //    printf("lelement pos =%d %d\n",!element_in_array(player.other_queens,m,pos+LENGHT), pos);
            return pos+LENGHT;
        }
        break;
    case 7:
        if(pos+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !element_in_array(player.other_queens,m,pos+1) && !element_in_array(player.current_queens,m,pos+1)){
            return pos+1;
        }
        break;
    case 2:
        if(pos-LENGHT+1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !element_in_array(player.other_queens,m,pos-LENGHT+1) && !element_in_array(player.current_queens,m,pos-LENGHT+1)){
            return pos-LENGHT+1;
        }
            break;
    case 4:
        if(pos+LENGHT+1<=LENGHT*LENGHT-1){
            if(gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !element_in_array(player.other_queens,m,pos+LENGHT+1) && !element_in_array(player.current_queens,m,pos+LENGHT+1)){
        //    printf("here\n");
            return pos+LENGHT+1;
            }
        }
        break;
    case 6:
        if(pos+LENGHT-1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !element_in_array(player.other_queens,m,pos+LENGHT-1) && !element_in_array(player.current_queens,m,pos+LENGHT-1) ){
            return pos+LENGHT-1;
        }
            break;
    case 8:
        if(pos-LENGHT-1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !element_in_array(player.other_queens,m,pos-LENGHT-1) && !element_in_array(player.current_queens,m,pos-LENGHT-1)){
            return pos-LENGHT-1;
        }
            break;
        
    default:
    return -1;
    break;
    //  printf("je suis là\n");
    }
    return -1;
}

