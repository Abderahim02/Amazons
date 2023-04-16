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

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);


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
    player_black.current_queens=malloc(sizeof(unsigned int)*m);

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
        // printf("dirrrrrrrrrr %d tmp=%d\n",dir, tmp);
        t[i]=get_neighbor(tmp,dir,graph);
        tmp=t[i];
        i++;
    }
    return t[rand()%i];

}


enum dir_t available_dir(int queen, struct graph_t *graph, enum dir_t direction){
    enum dir_t dir=rand()%8+1;
    int cmp=0;
    while((get_neighbor(queen,dir,graph)==-1 || dir==direction) && cmp<9){
        dir=(dir+1)%8;
        cmp++;
        if(dir==0) dir++;
    }
    if(cmp==9) return NO_DIR;
    return dir;

}

// int random_dst(struct graph_t *graph, enum dir_t dir, int pos){
//     int t[8];
//     int p=0;
//     int tmp = 59;
//     enum dir_t i = rand() % 8; 
//     //int i=0;
//     while(1 ){
//         int n = get_neighbor(tmp, i, graph );
//         if(n != -1) return n;
//         // printf("%d in direction : %d\n", get_neighbor(tmp, i, graph ), i);
//          i = rand()%8;
//     }
//     return pos;
// }

struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!=-1 && previous_move.queen_dst!=-1 )
        execute_move(previous_move,player_black.graph,player_black.other_queens);
    struct move_t move={-2,-2,-2};
    int r=rand()%player_black.num_queens;
    int queen=player_black.current_queens[r];
    enum dir_t dir=available_dir(queen,player_black.graph,NO_DIR);
   // printf("dir bash jay %d\n", dir);
    int cmp=0;
    if(dir==NO_DIR){
        //printf("_____________________________________________________\n");
    while(dir==NO_DIR && cmp<player_black.num_queens){
        cmp++;
        r=(r+1)%player_black.num_queens;
        queen=player_black.current_queens[r];
        dir=available_dir(queen,player_black.graph,NO_DIR);
    }
    }
    
    // printf("queen %d\n",queen);
    if(cmp==player_black.num_queens ){
      //  printf("    aaaaaaaaaaaaa\n");
        return move;
    }
  // printf("dir=%d\n",dir);
     move.queen_src=queen;
     move.queen_dst=random_dst(player_black.graph,dir,queen);
     enum dir_t dir2=available_dir(queen,player_black.graph,dir);
     if(dir2==NO_DIR){
        move.arrow_dst=-1;
     }
     else {
        //printf("queen %d\n",queen);
         move.arrow_dst=random_dst(player_black.graph,dir2,queen);
     }
    execute_move(move,player_black.graph,player_black.current_queens);
    return move;  
}

/*
struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!=-1 && previous_move.queen_dst!=-1 )
        execute_move(previous_move,player_black.graph,player_black.other_queens);
    struct move_t move={-2,-2,-2};
    int r=rand()%player_black.num_queens;
    int queen=player_black.current_queens[r];
    enum dir_t dir=available_dir(queen,player_black.graph,NO_DIR);
    int cmp=0;
    while(available_dir(queen,player_black.graph,NO_DIR)==NO_DIR && cmp<player_black.num_queens){
        cmp++;
        r=(r+1)%player_black.num_queens;
        queen=player_black.current_queens[r];
    }
    if(cmp==player_black.num_queens)
        return move;

  // printf("dir=%d\n",dir);
     move.queen_src=queen;
     move.queen_dst=random_dst(player_black.graph,dir,queen);
     enum dir_t dir2=available_dir(queen,player_black.graph,dir);
     if(dir2==NO_DIR){
        move.arrow_dst=-1;
     }
     else 
         move.arrow_dst=random_dst(player_black.graph,dir2,queen);
    execute_move(move,player_black.graph,player_black.current_queens);
    
    return move;  
}
*/
int element_in_array(int *t, int size, int x){
    for(int i=0;i<size;i++){
        if(t[i]==x) return i;
    }
    return 0;
}

void print(int *t, int size){
    for(int i=0;i<size;i++)
        printf("i=%d t[i]=%d\n", i, t[i]);
}

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    int m=4*(LENGHT/10 + 1);
    switch (dir)
    {
    case 1:
        if(pos-LENGHT >= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !element_in_array(player_black.other_queens,m,pos-LENGHT) &&  !element_in_array(player_black.current_queens,m,pos-LENGHT))
            return pos-LENGHT;
        break;
    case 3:
        if(pos-1>= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !element_in_array(player_black.other_queens,m,pos-1) && !element_in_array(player_black.current_queens,m,pos-1))
            return pos-1;
        break;
    case 5:
        if(pos+LENGHT<= LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !element_in_array(player_black.other_queens,m,pos+LENGHT) && !element_in_array(player_black.current_queens,m,pos+LENGHT))
        //    printf("lelement pos =%d %d\n",!element_in_array(player_black.other_queens,m,pos+LENGHT), pos);
            return pos+LENGHT;
        break;
    case 7:
        if(pos+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !element_in_array(player_black.other_queens,m,pos+1) && !element_in_array(player_black.current_queens,m,pos+1))
            return pos+1;
        break;
    case 2:
        if(pos-LENGHT+1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !element_in_array(player_black.other_queens,m,pos-LENGHT+1) && !element_in_array(player_black.current_queens,m,pos-LENGHT+1))
            return pos-LENGHT+1;
            break;
    case 4:
        if(pos+LENGHT+1<=LENGHT*LENGHT-1){
            if(gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !element_in_array(player_black.other_queens,m,pos+LENGHT+1) && !element_in_array(player_black.current_queens,m,pos+LENGHT+1)){
        //    printf("here\n");
            return pos+LENGHT+1;
            break;
            }
        }
    case 6:
        if(pos+LENGHT-1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !element_in_array(player_black.other_queens,m,pos+LENGHT-1) && !element_in_array(player_black.current_queens,m,pos+LENGHT-1) )
            return pos+LENGHT-1;
            break;
    case 8:
        if(pos-LENGHT-1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !element_in_array(player_black.other_queens,m,pos-LENGHT-1) && !element_in_array(player_black.current_queens,m,pos-LENGHT-1))
            return pos-LENGHT-1;
            break;
        
    default:
    return -1;
    break;
    //  printf("je suis là\n");
    }
    return -1;
}


