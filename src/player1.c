#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "grid.h"
#include <time.h>




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
    player_blanc.turn=0;
    int m=((graph->num_vertices/10)+1)*4;
    player_blanc.current_queens=(unsigned int *)malloc(sizeof(unsigned int)*m);

    player_blanc.other_queens=(unsigned int *)malloc(sizeof(unsigned int)*m);
    for(unsigned int i=0;i<num_queens;i++){
        player_blanc.current_queens[i]=queens[player_id][i];
        player_blanc.other_queens[i]=queens[(player_id+1)%2][i];
    }
}




//function that loops over the neighbors of a queen and returns the one that has the max neighbors in all directions
int best_queen_move_in_direction(struct graph_t *graph, enum dir_t dir, int pos){
    unsigned int length=sqrt(graph->t->size1);
    int t[length*2];
    int i=0;
    int tmp=pos;
    //fill the t array with all the neighbors of the queen in the given direction
    while(get_neighbor(tmp,dir,graph)!=-1){
        t[i]=get_neighbor(tmp,dir,graph);
        tmp=t[i];
        i++;
    }
    //calculate the queen_dst that has the max number of neigbors in all directions
    int max=0;
    int max_pos=0;
    for(int j=0;j<i;j++){
        int cmp=0;
        for(int k=1;k<9;k++){
            if(get_neighbor(t[j],k,graph)!=-1){
                cmp++;
            }
        }
        if(cmp>max){
            max=cmp;
            max_pos=t[j];
        }
    }
    return max_pos;
}
//function that prints an array of struct move_t
void print_array(struct move_t *moves, int size){
    for(int i=0;i<size;i++){
        printf("queen_src = %d, queen_dst = %d, arrow_dst = %d \n",moves[i].queen_src,moves[i].queen_dst,moves[i].arrow_dst);
        }
        printf("\n");}


//function that fills an array with all neighbors of an adversary queen


//function that calculates all possible moves for all the queens puts them in an array and returns the max of the best_queen_move_in_direction for each queen and the queen corresponding to the max
struct move_t best_move(struct graph_t *graph, unsigned int* queens, int num_queens){
    unsigned int length=sqrt(graph->t->size1);
    struct move_t moves[length*2*num_queens];
    int capcity = 0;
    struct move_t move ={UINT_MAX,UINT_MAX,UINT_MAX};
    //fill the moves array with all the possible moves for each queen
    int counter=0;
    for(int i=0;i<num_queens;i++){
        //printf("first iteration we have i = %d\n",i);
        //printf("queen %d\n   ",queens[i]);
        //loop over all the directions
        for(int j=1;j<9;j++){
            if(get_neighbor(queens[i],j,graph)!=-1){
                moves[counter].queen_src=queens[i];
                moves[counter].queen_dst=best_queen_move_in_direction(graph,j,queens[i]);
                enum dir_t dir2=available_dir(moves[counter].queen_dst,player_blanc.graph,NO_DIR, player_blanc);
                if(dir2==NO_DIR){
                    moves[counter].arrow_dst=UINT_MAX;
                }
                else{
                    moves[counter].arrow_dst=random_dst(graph,dir2,moves[counter].queen_dst, player_blanc);
                }
                counter++;
            }
        }
        capcity=counter;
    }
            if (counter ==0 ){
            return move;
        }
    //calculate the queen_dst that has the max number of neigbors in all directions
    int max=0;
    int max_pos=0;
    for(int i=0;i<capcity;i++){
        int cmp=0;
        for(int j=1;j<9;j++){
            if(get_neighbor_gen(moves[i].queen_dst,j,graph, player_blanc)!=-1){
                cmp++;
            }
        }
        if(cmp>=max){
            max=cmp;
            max_pos=i;
        }
    }
    //         printf("the array moves is :\n");
    //     printf("capcity = %d\n",capcity);
    //     print_array(moves,capcity);
    // printf("max is %d\n",max);
    // printf("max pos is %d\n",max_pos);
    struct move_t move2 ={moves[max_pos].queen_src,moves[max_pos].queen_dst,moves[max_pos].arrow_dst};
    // printf("the movement we are going to do is %d",moves[max_pos].queen_src);
    // printf("the movement we are going to do is %d to %d",moves[max_pos].queen_src,moves[max_pos].queen_dst);
    return move2;
}
//function that returns the number of neighbors of a queen
int num_neighbors(int queen, struct graph_t *graph){
    int cmp=0;
    for(int i=1;i<9;i++){
        if(get_neighbor(queen,i,graph)!=-1){
            cmp++;
        }
    }
    return cmp;
}

//function that finds index of a queen in an array of queens notvery useful right now
int find_queen(unsigned int queen, unsigned int* queens, int num_queens){
    for(int i=0;i<num_queens;i++){
        if(queens[i]==queen){
            return i;
        }
    }
    return -1;
}





struct move_t play(struct move_t previous_move){
    if(previous_move.queen_dst != (unsigned int)-1 && previous_move.queen_dst != (unsigned int)-1 ){
        execute_move(previous_move,player_blanc.graph,player_blanc.other_queens);
        player_blanc.turn++;
        printf("turn pour white: %d \n", player_blanc.turn);
    }
    if(player_blanc.turn<4){
        printf("YEssssssssssssssssssss\n");
    }
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    int r=rand()%player_blanc.num_queens;
    int queen=player_blanc.current_queens[r];
    
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    //finds an avaliable direction for a queen
    while(dir==NO_DIR && cmp<player_blanc.num_queens){
        queen=player_blanc.current_queens[r];
        dir=available_dir(queen,player_blanc.graph,NO_DIR, player_blanc);
        r=(r+1)%player_blanc.num_queens;
        cmp++;
    }
    
    if(dir==NO_DIR){
        free_player(player_blanc);
        return move;
    }
     move.queen_src=queen;
     move.queen_dst=random_dst(player_blanc.graph,dir,queen, player_blanc);
     player_blanc.current_queens[r]=move.queen_dst;
     queen=move.queen_dst;
     enum dir_t dir2=available_dir(queen,player_blanc.graph,dir, player_blanc);
     if(dir2==NO_DIR){
        move.arrow_dst=-1;
     }
     else {
         move.arrow_dst=random_dst(player_blanc.graph,dir2,queen, player_blanc);
     }
    execute_move(move,player_blanc.graph,player_blanc.current_queens);
    return move;  
}




//function play2 that uses the best_move function to find the best move
// struct move_t play2(struct move_t previous_move ){
//     if(previous_move.queen_dst!=-1 && previous_move.queen_dst!=-1){
//         execute_move(previous_move,player_blanc.graph,player_blanc.other_queens);
//         player_blanc.turn++;
//     }
//     struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
//     struct move_t best=best_move(player_blanc.graph,player_blanc.current_queens,player_blanc.num_queens);
//     move.queen_src=best.queen_src;
//     move.queen_dst=best.queen_dst;
//     move.arrow_dst=best.arrow_dst;
//     execute_move(move,player_blanc.graph,player_blanc.current_queens);
//     //printf("move is %d %d %d",move.queen_src,move.queen_dst,move.arrow_dst);
//     return move;
// }
int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
    return get_neighbor_gen(pos, dir, graph, player_blanc);
}

void finalize(){
    free(player_blanc.current_queens);
    free(player_blanc.other_queens);
}