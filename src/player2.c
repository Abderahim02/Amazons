#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "graph.h"
#include "dir.h"
#include "grid.h"
#include <time.h>


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

struct player player_black;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_black.name = "seeer_seeeer";
    return player_black.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
   player_black.id=player_id;
    player_black.graph=graph;
    player_black.num_queens=num_queens;
    int m=((graph->num_vertices/10)+1)*4;
    player_black.current_queens=malloc(sizeof(unsigned int));

    player_black.other_queens=malloc(sizeof(unsigned int)*m);
    for(int i=0;i<m;i++){
    player_black.current_queens[i]=queens[player_id][i];
    player_black.other_queens[i]=queens[(player_id+1)%2][i];
    }
  
}


int random_dst(struct graph_t *graph, enum dir_t dir, int pos){
    int t[LENGHT*2];
    int i=0;
    int tmp=pos;
    while(get_neighbor(tmp,dir,graph)!=-1){
        t[i]=get_neighbor(tmp,dir,graph);
        tmp=t[i];
        i++;
    }
    return t[rand()%i];

}

struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!=-1)
        execute_move(previous_move,player_black.graph,player_black.other_queens);
    struct move_t move;
   // execute_move(previous_move,player_black.graph,player_black.other_queens);
    int r=rand()%player_black.num_queens;
    int queen=player_black.current_queens[r];
    enum dir_t dir=rand()%8+1;
    while(get_neighbor(queen,dir,player_black.graph)==-1){
        dir=(dir+1)%8;
        if(dir==0) dir++;
    }
     move.queen_src=queen;
     move.queen_dst=random_dst(player_black.graph,dir,queen);
    enum dir_t dir2=rand()%8+1;
    while(get_neighbor(queen,dir,player_black.graph)==-1 || dir2==dir){
        dir=(dir+1)%8;
        if(dir==0) dir++;
    }
    int arrow_dst=random_dst(player_black.graph,dir2,queen);
    move.arrow_dst=arrow_dst;
    ///to make hole in the position move.arrow_dst
    execute_move(move,player_black.graph,player_black.current_queens);
    return move;  
}

int element_in_array(int *t, int size, int x){
    for(int i=0;i<size;i++){
        if(t[i]==x) return 1;
    }
    return 0;
}


int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    int m=4*(LENGHT/10 + 1);
    switch (dir)
    {
    case 1:
        if(pos-LENGHT >= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !element_in_array(player_black.other_queens,m,pos-LENGHT))
            return pos-LENGHT;
        break;
    case 3:
        if(pos-1>= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !element_in_array(player_black.other_queens,m,pos-1))
            return pos-1;
        break;
    case 5:
        if(pos+LENGHT<= LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !element_in_array(player_black.other_queens,m,pos+LENGHT))
            return pos+LENGHT;
        break;
    case 7:
        if(pos+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !element_in_array(player_black.other_queens,m,pos+1))
            return pos+1;
        break;
    case 2:
        if(pos-LENGHT+1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !element_in_array(player_black.other_queens,m,pos-LENGHT+1) )
            return pos-LENGHT+1;
            break;
    case 4:
        if(pos+LENGHT+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !element_in_array(player_black.other_queens,m,pos+LENGHT+1))
            return pos+LENGHT+1;
            break;
    case 6:
        if(pos+LENGHT-1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !element_in_array(player_black.other_queens,m,pos+LENGHT-1))
            return pos+LENGHT-1;
            break;
    case 8:
        if(pos-LENGHT-1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !element_in_array(player_black.other_queens,m,pos-LENGHT-1))
            return pos-LENGHT-1;
            break;
    default:
    break;
    }
    printf("je suis là\n");
    return -1;
}
