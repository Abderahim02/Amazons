#include <stdio.h>
#include <stdlib.h>

#include "move.h"
#include "grid.h"


struct set{
    unsigned int taille;
    struct move_t positions[GRID_SIZE];
};

//Initializes a set
void positions_init(struct set* pi ) {
    pi->taille = 0 ;
}

//Add a position to a set
void add_position(struct set* p ,unsigned int place ){
    p->positions[p->taille]=place ;
    p->taille+=1;
}

//Verify the existence of a place in a set  and return 1 if it does 0 if it doesn't
int is_in_set(struct set* ens, unsigned int place ){
    
    for (unsigned int i =0; i < ens->taille; i++){
        if (place == ens->positions[i]){
            return 1;
        }
    }
    return 0;
}

//
void available_moves(struct graph_t* graph, struct set* set){
    enum dir_t array[8]={DIR_NORTH=1, DIR_NE=2,
                         DIR_WEST=3,  DIR_SE=4,
                         DIR_SOUTH=5, DIR_SW=6,
                         DIR_EAST=7,  DIR_NW=8,};
    
}


//Initializes a set
void positions_init(struct set* set ) {
    set->taille = 0 ;
}

//Add a position to a set
void add_position(struct set* set ,unsigned int place ){
    set->positions[set->taille]=place ;
    set->taille+=1;
}

//Verify the existence of a place in a set  and return 1 if it does 0 if it doesn't
int is_in_set(struct set* ens, unsigned int place ){
    
    for (unsigned int i =0; i < ens->taille; i++){
        if (place == ens->positions[i]){
            return 1;
        }
    }
    return 0;
}

//
void available_moves(struct graph_t* graph, struct set* set){
    enum dir_t array[8]={DIR_NORTH, DIR_NE,
                         DIR_WEST,  DIR_SE,
                         DIR_SOUTH, DIR_SW,
                         DIR_EAST,  DIR_NW};
    int* t = graph_table(struct graph_t* graph);
    for(int i=; i<graph->num_vertices; i++){
        printf("%d", t[i])
    }
    
}

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    struct set* set;
    positions_init(set);
    int m=4*(LENGHT/10 + 1);
    switch (dir)
    {
    case 1:
        if(pos-LENGHT >= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !is_in_set(set,pos-LENGHT))
            return pos-LENGHT;
        break;
    case 3:
        if(pos-1>= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !is_in_set(set,pos-1))
            return pos-1;
        break;
    case 5:
        if(pos+LENGHT<= LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !is_in_set(set,pos+LENGHT))
            return pos+LENGHT;
        break;
    case 7:
        if(pos+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !is_in_set(set,pos+1))
            return pos+1;
        break;
    case 2:
        if(pos-LENGHT+1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !is_in_set(set,pos-LENGHT+1) )
            return pos-LENGHT+1;
    case 4:
        if(pos+LENGHT+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !is_in_set(set,pos+LENGHT+1))
            return pos+LENGHT+1;
    case 6:
        if(pos+LENGHT-1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !is_in_set(set,pos+LENGHT-1))
            return pos+LENGHT-1;
    case 8:
        if(pos-LENGHT-1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !is_in_set(set,pos-LENGHT-1))
            return pos-LENGHT-1;
    default:
        break;
    }
    return -1;
}

