#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "graph.h"
#include <time.h>




int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);
//this function frees the momory blocks allocated for the graph
void free_graph2(struct graph_t* g){
    gsl_spmatrix_uint_free(g->t);
    free(g);
}

//extern struct graph_t *graph_cpy(const struct graph_t *graph, int size);
struct graph_t *graph_cpy2(const struct graph_t *graph, int size){
  struct graph_t *graph_cpy = malloc(sizeof(struct graph_t));
  gsl_spmatrix_uint *matrix_copy=gsl_spmatrix_uint_alloc(graph->t->size1,graph->t->size2);
  graph_cpy->t=gsl_spmatrix_uint_compress(matrix_copy, GSL_SPMATRIX_CSR);
  gsl_spmatrix_uint_free(matrix_copy);
  gsl_spmatrix_uint_memcpy(graph_cpy->t, graph->t); 
  graph_cpy->num_vertices = graph->num_vertices;
  return graph_cpy;
}

struct player player_blanc;
/* Access to player informations
 * RETURNS:
 * - the player name as an [a-zA-Z0-9 -_]* string
 */
//function that returns the number of neighbors of a queen
int number_neighbors(int queen, struct graph_t *graph){
    int cmp=0;
    for(int i=1;i<9;i++){
        if(get_neighbor_gen(queen,i,graph,player_blanc)!=UINT_MAX){
            cmp++;
        }
    }
    return cmp;
}
//function that returns the number of neighbors of a player which is the sum of the number of neighbors of each queen,this function takes array of queens as a parameter
int number_neighbors_player(unsigned int* queens, struct graph_t *graph){
    int cmp=0;
    for(int i=0;i<(int)player_blanc.num_queens;i++){
        cmp+=number_neighbors(queens[i],graph);
    }
    return cmp;
}
unsigned int random_arrow_dst(struct graph_t *graph, unsigned int pos, struct player player, unsigned int positions_possible[],unsigned int source_place) {
        if (positions_possible[0] == 0) {
        return source_place;
    }else{
    unsigned int dst = positions_possible[(rand() % (positions_possible[0])) + 1];
    return dst;
    }
}
unsigned int random_queen_dst(struct graph_t *graph, unsigned int pos, struct player player, unsigned int positions_possible[]) {
    if (positions_possible[0] == 0) {
        return UINT_MAX;
    }else{
    unsigned int dst = positions_possible[(rand() % (positions_possible[0])) + 1];
    return dst;
    }
}
unsigned int best_arrow(struct graph_t *graph, unsigned int pos, unsigned int src, struct player player, unsigned int enemy_queens_neighbors[], int num_enemy_queens){
    printf("best arrow is caling it \n");
    unsigned int *t = available_dst_all(graph, pos, player);
    unsigned int best_arrow_pos = UINT_MAX;
    int max_occurence = -1;

    // Find the arrow position that hits the most enemy queen neighbors
    for(int i = 1; i <= t[0]; i++){
        if(t[i] == src){
            // Skip the source position if it is in the list of available destinations
            continue;
        }
        int occurence = occurence_in_array(enemy_queens_neighbors, num_enemy_queens, t[i]);
        if(occurence > max_occurence){
            best_arrow_pos = t[i];
            max_occurence = occurence;
        }
    }

    // If there are multiple arrow positions with the same max number of hits, choose randomly
    if(best_arrow_pos != UINT_MAX){
        int num_max_occurences = 0;
        for(int i = 1; i <= t[0]; i++){
            if(t[i] == src){
                continue;
            }
            int occurence = occurence_in_array(enemy_queens_neighbors, num_enemy_queens, t[i]);
            if(occurence == max_occurence){
                num_max_occurences++;
            }
        }
        int random_index = rand() % num_max_occurences + 1;
        int count = 0;
        for(int i = 1; i <= t[0]; i++){
            if(t[i] == src){
                continue;
            }
            int occurence = occurence_in_array(enemy_queens_neighbors, num_enemy_queens, t[i]);
            if(occurence == max_occurence){
                count++;
                if(count == random_index){
                    best_arrow_pos = t[i];
                    break;
                }
            }
        }
    } else {
        // If no arrow position hits any enemy queen neighbor, choose randomly from all available positions
        best_arrow_pos = random_arrow_dst(graph, pos, player, t, src);
    }
    printf("freeing from BEST ARROW \n");
    free(t);
    return best_arrow_pos;
}

char const* get_player_name(){
    player_blanc.name = "Dir_niya";
    return player_blanc.name;
}
//function that returns the occurrence of an element in an array
int occurence_in_array(unsigned int *array, int size, unsigned int element){
    int occ = 0;
    for(int i=0;i<size;i++){
        if(array[i]==element){
            occ++;
        }
    }
    return occ;
}
void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
    player_blanc.id=player_id;
    player_blanc.graph=graph;
    player_blanc.num_queens=num_queens;
    player_blanc.turn=0;
    player_blanc.current_queens=queens[player_id];
    player_blanc.other_queens=queens[(player_id+1)%2];
}

//function that calculates the heuristic whcich is the difference between the number of neighbors of the player and the number of neighbors of the adversary
int heuristic(struct graph_t *graph, struct move_t move, struct player player) {
    int h = 0;
    int length = sqrt(graph->t->size1);
    struct graph_t* graph_copy = graph_cpy2(graph, length);
    unsigned int *queens[NUM_PLAYERS] = {player.current_queens, player.other_queens};

    // Apply the move to the graph copy
    execute_move(move, graph_copy, player.current_queens);
    h = number_neighbors_player(player.current_queens, graph_copy) - number_neighbors_player(player.other_queens, graph_copy);
free_graph2(graph_copy);
    return h;
}
struct move_t random_move(struct graph_t * graph , unsigned int queen,unsigned int t[]){
    struct move_t move;
    move.queen_src = queen;
    move.queen_dst = random_queen_dst(graph,move.queen_src,player_blanc,t);
    move.arrow_dst = random_arrow_dst(graph,move.queen_dst,player_blanc,t,move.queen_src);

    return move;
}
void printos2(unsigned int *array){
    for(unsigned int i=1; i<array[0]+1; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}



//function that prints an array of struct move_t
void print_array(struct move_t *moves, int size){
    for(int i=0;i<size;i++){
        printf("queen_src = %d, queen_dst = %d, arrow_dst = %d \n",moves[i].queen_src,moves[i].queen_dst,moves[i].arrow_dst);
        }
        printf("\n");}

//function that fills an array with all neighbors of an adversary queen
struct move_t best_move(struct graph_t * graph , const unsigned int * queens , int num_queens){
    struct move_t moves[graph->t->size1*graph->t->size1];
    unsigned int enemy_queens_neighbors[graph->t->size1];
    int num_enemy_queens=0;
    struct move_t move ={UINT_MAX,UINT_MAX,UINT_MAX};
    int moves_counter=0;
    //filling enemy queens neighbors array with enemy queens neighbors
    for(int i=0;i<num_queens;i++){
        for(int j=1;j<9;j++){
            unsigned int neighbor = get_neighbor_queens(player_blanc.other_queens[i],j,graph,player_blanc.current_queens,player_blanc.other_queens,player_blanc.num_queens);
            if((neighbor!=UINT_MAX)){
                enemy_queens_neighbors[num_enemy_queens]=neighbor;
                num_enemy_queens++;
            }
        }
    }
    //print_arr2(enemy_queens_neighbors,num_enemy_queens);

    //loop over all current queens

    for (int i = 0 ; i< num_queens;i++){
        //printf("queen %d\n",queens[i]);
        printf("best_move is calling available_dst_all to fill moves array  !!!!!\n\n");
        unsigned int * t =available_dst_all(graph,queens[i],player_blanc);
        printf("printing t in other function \n");
        printos2(t); 
        if (t[0]==0){
            printf("WE HAVE T[0] == 0 for this queen %d in best_move \n",queens[i]);
            free(t);
            continue;
        }else{
        for (int j = 1 ; j<(int)t[0]+1;j++){

        if (element_in_array(enemy_queens_neighbors,num_enemy_queens,t[j])){
                moves[moves_counter].queen_src=queens[i];
                moves[moves_counter].queen_dst=t[j];
                moves[moves_counter].arrow_dst=best_arrow(graph,t[j],queens[i],player_blanc,enemy_queens_neighbors,num_enemy_queens); 
                moves_counter++;
        }
        }
        printf("freeing the array for the queen %d in best_move \n\n",queens[i]);
        free(t);
    }
    }
    // for(int i = 0 ; i < moves_counter ; i++){
    //     printf("moves[%d] = %d %d %d\n",i,moves[i].queen_src,moves[i].queen_dst,moves[i].arrow_dst);
    // }
//     printf("moves counter = %d\n",moves_counter);
//     if (moves_counter>0){
//         //loops over all moves and find the move with the highest heuristic value
//     int max=-1000;
//     int max_pos=0;
//     for (int i = 0 ; i< moves_counter;i++){
//         int cmp = heuristic(graph,moves[i],player_blanc);
// printf("move %d %d %d has heuristic = %d\n",moves[i].queen_src,moves[i].queen_dst,moves[i].arrow_dst,cmp);
//         if (cmp>max){
//             max=cmp;
//             max_pos=i;
//         }
//     }
//     printf("heuristic chosen   is  = %d\n",max);
//     printf("move chosen   is  = %d %d %d\n",moves[max_pos].queen_src,moves[max_pos].queen_dst,moves[max_pos].arrow_dst);
// move = moves[max_pos];
//      }
// else{
//         //get a random queen 
//         // int random_queen = rand()%num_queens;
//         // unsigned int * t =available_dst_all(graph,queens[random_queen],player_blanc);
//         // if(t[0]!=0){
//         // move = random_move(graph,queens[random_queen],t);
//             // }
//             // free(t);
//             // set flag to false initially
//         int move_found = 0;
//         int copy_num_queens = num_queens;
//     // loop until a valid move is found or all queens have been checked
//     while (!move_found && copy_num_queens > 0) {
//         // get a random queen
//         int random_queen = rand() % copy_num_queens;
//     printf("best move again is calling available_dst_all to find the random move   !!!!!\n\n");
//         // get available destinations for the queen
//         unsigned int* t = available_dst_all(graph, queens[random_queen], player_blanc);

//         // check if there are any available destinations
//         if (t[0] != 0) {
//             // found a valid move, set flag to true and set move variable
//             move_found = 1;
//             move = random_move(graph, queens[random_queen], t);
//             printf("the random move we found is : %d %d %d\n",move.queen_src,move.queen_dst,move.arrow_dst);
//             break;
//         }

//     // free the memory allocated for available destinations
//     free(t);

//     // if no valid move was found, decrement the number of queens and try again
//     if (!move_found) {
//         copy_num_queens--;
//     }
// }


//     }


    //printf("array of moves\n");
    //print_array(moves,moves_counter);
    printf("end of function move chosen  is : %d %d %d\n",move.queen_src,move.queen_dst,move.arrow_dst);
    return move;

}

//function that calculates all possible moves for all the queens puts them in an array and returns the max of the best_queen_move_in_direction for each queen and the queen corresponding to the max
// struct move_t best_move(struct graph_t *graph, unsigned int* queens, int num_queens){
//     unsigned int length=sqrt(graph->t->size1);
//     struct move_t moves[length*2*num_queens];
//     int capcity = 0;
//     struct move_t move ={UINT_MAX,UINT_MAX,UINT_MAX};
//     //fill the moves array with all the possible moves for each queen
//     int counter=0;
//     for(int i=0;i<num_queens;i++){
//         //loop over all the directions
//         for(int j=1;j<9;j++){
//             if(get_neighbor(queens[i],j,graph)!=-1){
//                 moves[counter].queen_src=queens[i];
//                 moves[counter].queen_dst=best_queen_move_in_direction(graph,j,queens[i]);
//                 enum dir_t dir2=available_dir(moves[counter].queen_dst,player_blanc.graph,NO_DIR,player_blanc);
//                 if(dir2==NO_DIR){
//                     moves[counter].arrow_dst=UINT_MAX;
//                 }
//                 else{
//                     moves[counter].arrow_dst=random_dst(graph,dir2,moves[counter].queen_dst,player_blanc);
//                 }
//                 counter++;
//             }
//         }
//         capcity=counter;
//     }
//             if (counter ==0 ){
//             return move;
//         }
//     //calculate the queen_dst that has the max number of neigbors in all directions
//     int max=0;
//     int max_pos=0;
//     for(int i=0;i<capcity;i++){
//         int cmp=0;
//         for(int j=1;j<9;j++){
//             if((int)get_neighbor_gen(moves[i].queen_dst,j,graph,player_blanc)!=-1){
//                 cmp++;
//             }
//         }
//         if(cmp>=max){
//             max=cmp;
//             max_pos=i;
//         }
//     }
 
//     struct move_t move2 ={moves[max_pos].queen_src,moves[max_pos].queen_dst,moves[max_pos].arrow_dst};
//     return move2;
// }
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
    }
    struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
    int r=rand()%player_blanc.num_queens;
    int queen_index=r;
    int queen=player_blanc.current_queens[r];
    // we search for available direction for queen, else we change the queen 
    // cmp to avoid the infinite loop 
    enum dir_t dir=NO_DIR;
    unsigned int cmp=0;
    while(dir==NO_DIR && cmp<player_blanc.num_queens){
        cmp++;
        queen_index=r;
        queen=player_blanc.current_queens[queen_index];
        dir=available_dir(queen,player_blanc.graph,NO_DIR,player_blanc);
        r=(r+1)%player_blanc.num_queens;
    }
    
    if(dir==NO_DIR){
        return move;
    }
     move.queen_src=queen;
     move.queen_dst=random_dst(player_blanc.graph,dir,queen, player_blanc);
     player_blanc.current_queens[(r-1)%player_blanc.num_queens]=move.queen_dst;
     queen=move.queen_dst;
     enum dir_t dir2=available_dir(queen,player_blanc.graph,dir,player_blanc);
     if(dir2==NO_DIR){
        move.arrow_dst=move.queen_src;
     }
     else {
         move.arrow_dst=random_dst(player_blanc.graph,dir2,queen,player_blanc);
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
    return get_neighbor_gen(pos, dir, graph,player_blanc);
}

void finalize(){
    free(player_blanc.current_queens);
    free(player_blanc.other_queens);
   // free(player_blanc.name);
    gsl_spmatrix_uint_free(player_blanc.graph->t);
    free(player_blanc.graph);
}