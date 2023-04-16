#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "graph.h"
#include "dir.h"
#include "grid.h"
#include "move.h"
#include <time.h>


struct player {
    unsigned int id;
    char const* name;
    struct graph_t* graph;
    unsigned int num_queens;
    unsigned int* current_queens;
    unsigned int* other_queens;
};

int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);

struct player player_blanc;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
char const* get_player_name(){
    player_blanc.name = "Dir_niya";
    return player_blanc.name;
}

void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_blanc.id=player_id;
    player_blanc.graph=graph;
    player_blanc.num_queens=num_queens;
    int m=((graph->num_vertices/10)+1)*4;
    player_blanc.current_queens=malloc(sizeof(unsigned int)*num_queens);

    player_blanc.other_queens=malloc(sizeof(unsigned int)*num_queens);
    for(int i=0;i<num_queens;i++){
        player_blanc.current_queens[i]=queens[player_id][i];
        player_blanc.other_queens[i]=queens[(player_id+1)%2][i];
    }
}



int random_dst(struct graph_t *graph, enum dir_t dir, int pos){
   // if(pos==61) printf("hna wls\n");
    int t[LENGHT*2];
    int i=0;
    int tmp=pos;
    while(get_neighbor(tmp,dir,graph)!=-1){
       //  printf("dkhl %d dir=%d queen=%d\n",tmp,dir,pos);

        // printf("dirrrrrrrrrr %d tmp=%d\n",dir, tmp);
        t[i]=get_neighbor(tmp,dir,graph);
        tmp=t[i];
        i++;
       // if(tmp>LENGHT*LENGHT-1)
         //   break;
    }
    // printf("ha direction %d\n");    
    // printf("madkhlx\n");
     return t[rand()%i];

}



enum dir_t available_dir(int queen, struct graph_t *graph, enum dir_t direction){
    enum dir_t dir=rand()%8+1;
  //  printf("dir ------- %d\n", dir);
    int cmp=0;
    while((get_neighbor(queen,dir,graph)==-1 || dir==direction) && cmp<9){
        dir=(dir+1)%8;
        cmp++;
        if(dir==0) dir++;
    }
 //   printf("cmp--------------%d\n",cmp);
    if(cmp==9) return NO_DIR;
   //  printf("dir ------------------ %d\n", dir);

    return dir;

}

struct move_t play(struct move_t previous_move){
   //    srand(300);
    if(previous_move.queen_dst!=-1 && previous_move.queen_dst!=-1 )
        execute_move(previous_move,player_blanc.graph,player_blanc.other_queens);
    struct move_t move={-2,-2,-2};
    int r=rand()%player_blanc.num_queens;
    int queen=player_blanc.current_queens[r];
    enum dir_t dir=available_dir(queen,player_blanc.graph,NO_DIR);
   // printf("dir bash jay %d\n", dir);
    int cmp=0;
    if(dir==NO_DIR){
        //printf("_____________________________________________________\n");
    while(dir==NO_DIR && cmp<player_blanc.num_queens){
        cmp++;
        r=(r+1)%player_blanc.num_queens;
        queen=player_blanc.current_queens[r];
        dir=available_dir(queen,player_blanc.graph,NO_DIR);
    }
    }
    
    // printf("queen %d\n",queen);
    if(cmp==player_blanc.num_queens ){
      //  printf("    aaaaaaaaaaaaa\n");
        return move;
    }
  // printf("dir=%d\n",dir);
     move.queen_src=queen;
     move.queen_dst=random_dst(player_blanc.graph,dir,queen);
     enum dir_t dir2=available_dir(queen,player_blanc.graph,dir);
     if(dir2==NO_DIR){
        move.arrow_dst=-1;
     }
     else {
        //printf("queen %d\n",queen);
         move.arrow_dst=random_dst(player_blanc.graph,dir2,queen);
     }
    execute_move(move,player_blanc.graph,player_blanc.current_queens);
    return move;  
}


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
    if(pos<0) return -1;
    switch (dir)
    {
    case 1:
        if(pos-LENGHT >= 0){
            if( gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !element_in_array(player_blanc.other_queens,m,pos-LENGHT) &&  !element_in_array(player_blanc.current_queens,m,pos-LENGHT))
            return pos-LENGHT;
        
        }
        return -1;
         break;
    case 3:
         if(pos-1>= 0){
         if(gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !element_in_array(player_blanc.other_queens,m,pos-1) && !element_in_array(player_blanc.current_queens,m,pos-1))
            return pos-1;
        
         }
         return -1;
          break;
    case 5:
     if(pos+LENGHT<= LENGHT*LENGHT-1){
         if( gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !element_in_array(player_blanc.other_queens,m,pos+LENGHT) && !element_in_array(player_blanc.current_queens,m,pos+LENGHT))
        //    printf("lelement pos =%d %d\n",!element_in_array(player_black.other_queens,m,pos+LENGHT), pos);
            return pos+LENGHT;
        
     }
     return -1;
      break;
    case 7:
     if(pos+1<=LENGHT*LENGHT-1){
        if(gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !element_in_array(player_blanc.other_queens,m,pos+1) && !element_in_array(player_blanc.current_queens,m,pos+1))
            return pos+1;
    
     }
     return -1;
      break;
    case 2:
     if(pos-LENGHT+1>=0){
        if(gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !element_in_array(player_blanc.other_queens,m,pos-LENGHT+1) && !element_in_array(player_blanc.current_queens,m,pos-LENGHT+1))
            return pos-LENGHT+1;
           
     }
     return -1;
      break;
    case 4:
        if(pos+LENGHT+1<=LENGHT*LENGHT-1){
            if(gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !element_in_array(player_blanc.other_queens,m,pos+LENGHT+1) && !element_in_array(player_blanc.current_queens,m,pos+LENGHT+1)){
           return pos+LENGHT+1;
            }
        }
        return -1;
         break;
    case 6:
        if(pos+LENGHT-1<=LENGHT*LENGHT-1){
         if(gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !element_in_array(player_blanc.other_queens,m,pos+LENGHT-1) && !element_in_array(player_blanc.current_queens,m,pos+LENGHT-1) )
            return pos+LENGHT-1;
            
        }
        return -1;
         break;
    case 8:
     if(pos-LENGHT-1>=0){
     if(gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !element_in_array(player_blanc.other_queens,m,pos-LENGHT-1) && !element_in_array(player_blanc.current_queens,m,pos-LENGHT-1))
            return pos-LENGHT-1;
     }
     return -1;
      break;
    default:
    return -1;
    break;
    }
    return -1;
}


// int is_in_set(int *t, int size, int x){
//     for(int i=0;i<size;i++){
//         if(t[i]==x) return 1;
//     }
//     return 0;
// }

// int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
//     int m=4*(LENGHT/10 + 1);
//     switch (dir)
//     {
//     case 1:
//         if(pos-LENGHT >= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT) && !is_in_set(player_blanc.other_queens,m,pos-LENGHT))
//             return pos-LENGHT;
//         break;
//     case 3:
//         if(pos-1>= 0 && gsl_spmatrix_uint_get(graph->t, pos, pos-1) && !is_in_set(player_blanc.other_queens,m,pos-1))
//             return pos-1;
//         break;
//     case 5:
//         if(pos+LENGHT<= LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT) && !is_in_set(player_blanc.other_queens,m,pos+LENGHT))
//             return pos+LENGHT;
//         break;
//     case 7:
//         if(pos+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+1) && !is_in_set(player_blanc.other_queens,m,pos+1))
//             return pos+1;
//         break;
//     case 2:
//         if(pos-LENGHT+1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT+1) && !is_in_set(player_blanc.other_queens,m,pos-LENGHT+1) )
//             return pos-LENGHT+1;
//     case 4:
//         if(pos+LENGHT+1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT+1) && !is_in_set(player_blanc.other_queens,m,pos+LENGHT+1))
//             return pos+LENGHT+1;
//     case 6:
//         if(pos+LENGHT-1<=LENGHT*LENGHT-1 && gsl_spmatrix_uint_get(graph->t, pos, pos+LENGHT-1) && !is_in_set(player_blanc.other_queens,m,pos+LENGHT-1))
//             return pos+LENGHT-1;
//     case 8:
//         if(pos-LENGHT-1>=0 && gsl_spmatrix_uint_get(graph->t, pos, pos-LENGHT-1) && !is_in_set(player_blanc.other_queens,m,pos-LENGHT-1))
//             return pos-LENGHT-1;
//     default:
//         break;
//     }
//     return -1;
// }




 


