#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "moteur.h" 
#include "player.h"
#include "dir.h"
#include "graph.h"
#include <time.h>
#include "server_functions.h"

// extern unsigned int* allouer_table(int length);


int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph);
//this function frees the momory blocks allocated for the graph
void free_graph2(struct graph_t* g){
  gsl_spmatrix_uint_free(g->t);
  free(g);
  g=NULL;
}

//extern struct graph_t *graph_cpy(const struct graph_t *graph, int size);
// struct graph_t *graph_cpy2(const struct graph_t *graph, int size){
//   struct graph_t *graph_cpy = malloc(sizeof(struct graph_t));
//   gsl_spmatrix_uint *matrix_copy=gsl_spmatrix_uint_alloc(graph->t->size1,graph->t->size2);
//   graph_cpy->t=gsl_spmatrix_uint_compress(matrix_copy, GSL_SPMATRIX_CSR);
//   gsl_spmatrix_uint_memcpy(graph_cpy->t, graph->t); 
//   gsl_spmatrix_uint_free(matrix_copy);
//   graph_cpy->num_vertices = graph->num_vertices;
//   return graph_cpy;
// }

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
//function that returns the occurrence of an element in an array
int occurence_in_array(const unsigned int *array, int size, unsigned int element){
  int occ = 0;
  for(int i=0;i<size;i++){
    if(array[i]==element){
      occ++;
    }
  }
  return occ;
} 
//function that  returns the number of neighbors of all queens of a player
int number_neighbors_player(unsigned int* queens, struct graph_t *graph ){
  int cmp=0;
  unsigned int length = sqrt(graph->t->size1);
  unsigned int m=((length/10)+1)*4;
  for(unsigned int i=0;i<m;i++){
    cmp+=number_neighbors(queens[i],graph);
  }
  return cmp;
}
//function that returns a random arrow destination taken for it the list of possible destinations note that it takes source position in case of no possible destination
unsigned int random_arrow_dst(unsigned int positions_possible[],unsigned int source_place) {
  if (positions_possible[0] == 0) {
    return source_place;
  }else{
    unsigned int dst = positions_possible[(rand() % (positions_possible[0])) + 1];
    return dst;
  }
}
//function that returns a random queen destination taken for it the list of possible destinations
unsigned int random_queen_dst(unsigned int positions_possible[]) {
  if (positions_possible[0] == 0) {
    return UINT_MAX;
  }else{
    unsigned int dst = positions_possible[(rand() % (positions_possible[0])) + 1];
    return dst;
  }
}
/* 
   function best_arrow  that returns the best arrow position to play
   prioritazing the positions that contain the most enemy queens neighbors
*/
unsigned int best_arrow(struct graph_t *graph, unsigned int pos, unsigned int src, struct player player, unsigned int enemy_queens_neighbors[], int num_enemy_queens){
  // printf("best arrow is caling it \n");
  unsigned int *t = available_dst_all(graph, pos, player);
  unsigned int best_arrow_pos = UINT_MAX;
  int max_occurence = -1;

  // Find the arrow position that hits the most enemy queen neighbors
  for(unsigned int i = 1; i <= t[0]; i++){

    int occurence = occurence_in_array(enemy_queens_neighbors, num_enemy_queens, t[i]);
    if(occurence >= max_occurence){
      best_arrow_pos = t[i];
      max_occurence = occurence;
    }
  }

  if(best_arrow_pos == UINT_MAX){
    best_arrow_pos = random_arrow_dst(t, src);
  }
  free(t);
  return best_arrow_pos;
}

char const* get_player_name(){
  player_blanc.name = "Dir_niya";
  return player_blanc.name;
}
// function that initializes the player
void initialize(unsigned int player_id, struct graph_t* graph, unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]){
  player_blanc.id=player_id;
  player_blanc.graph=graph;
  player_blanc.num_queens=num_queens;
  player_blanc.turn=0;
  player_blanc.current_queens=queens[player_id];
  player_blanc.other_queens=queens[(player_id+1)%2];
}



/*  function that calculates the heuristic whcich is the difference between the number of neighbors of the player and the number of neighbors of the adversary
    the higher the heuristic the better for this player
*/
int heuristic(struct graph_t *graph, struct move_t move, struct player player) {
  int h = 0;
  unsigned int length = sqrt(graph->t->size1);
  unsigned int m=((length/10)+1)*4;

  struct graph_t* graph_copy = graph_cpy(graph);
  unsigned int * cp1 = allouer_table(length);
  unsigned int * cp2 = allouer_table(length);
    
  unsigned int *queens[NUM_PLAYERS] ={cp1, cp2};
  //printf("la valeur de m %u \n", m);
  for(unsigned int i=0; i < m ; ++i){
    queens[0][i] = player.current_queens[i];
    queens[1][i] = player.other_queens[i];
  }
  // Apply the move to the graph copy
  execute_move(move, graph_copy, queens[0]);
  h = number_neighbors_player(queens[0], graph_copy) - number_neighbors_player(queens[1],  graph_copy);
  free_graph2(graph_copy);
  free(cp1);
  free(cp2);
  cp1=NULL;
  cp2=NULL;
  return h;
}
/* 
   functions that choses a random move from the list of possible moves 
*/
struct move_t random_move(unsigned int queen,unsigned int t[]){
  struct move_t move;
  move.queen_src = queen;
  move.queen_dst = random_queen_dst(t);
  move.arrow_dst = random_arrow_dst(t,move.queen_src);
  return move;
}





/* 
   Function that choses the best move prioritizing the moves that have the highest heuristic, 
   and then the random moves 
*/
struct move_t best_move(struct graph_t * graph, const unsigned int* queens , int num_queens){
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

  //loop over all current queens

  for (int i = 0 ; i< num_queens; i++){
    unsigned int * t = available_dst_all(graph, queens[i], player_blanc);
    if (t[0]==0){
      free(t);
    }
    else{
      for (unsigned int j = 1 ; j<t[0]+1; j++){
	if (element_in_array(enemy_queens_neighbors, num_enemy_queens, t[j])){
	  moves[moves_counter].queen_src = queens[i];
	  moves[moves_counter].queen_dst = t[j];
	  moves[moves_counter].arrow_dst = best_arrow(graph,t[j],queens[i],player_blanc,enemy_queens_neighbors,num_enemy_queens); 
	  moves_counter++;
	}
      }
      free(t);
    }
  }
  if (moves_counter>0){
    //loops over all moves and find the move with the highest heuristic value
    int max=-1000;
    int max_pos=0;
    for (int i = 0 ; i< moves_counter;i++){
      int cmp = heuristic(graph, moves[i], player_blanc);
      if (cmp>max){
	max=cmp;
	max_pos=i;
      }
    }
    move = moves[max_pos];
  }
  else{
    int move_found = 0;
    int copy_num_queens = num_queens;
    // loop until a valid move is found or all queens have been checked
    while (!move_found && copy_num_queens > 0) {
      srand((unsigned int)time(NULL));
      int random_queen = rand() % copy_num_queens;
      unsigned int * t = available_dst_all(graph, queens[random_queen], player_blanc);  
      // if no valid move was found, decrement the number of queens and try again
      if(t[0]==0){
	copy_num_queens--;
	free(t);
      }
      else if (t[0] != 0) {
	move_found = 1;
	move = random_move(queens[random_queen], t);
	free(t);
	break;
      }  
    }
  } 
  return move;

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




/* 
   function play that executes the other players move on current player's graph 
   and then returns the best move to play
*/
struct move_t play(struct move_t previous_move ){
  if(previous_move.queen_dst!= (unsigned int)-1 && previous_move.queen_dst != (unsigned int) -1){
    execute_move(previous_move, player_blanc.graph, player_blanc.other_queens);
    player_blanc.turn++;
  }
  struct move_t move={UINT_MAX,UINT_MAX,UINT_MAX};
  struct move_t best = best_move(player_blanc.graph, player_blanc.current_queens, player_blanc.num_queens);
  move.queen_src=best.queen_src;
  move.queen_dst=best.queen_dst;
  move.arrow_dst=best.arrow_dst;
  execute_move(move,player_blanc.graph,player_blanc.current_queens);
  return move;
}  
int get_neighbor(int pos, enum dir_t dir, struct graph_t* graph){
  return get_neighbor_gen(pos, dir, graph,player_blanc);
}
/* 
   the finilaze function that frees all the allocated memory
*/
void finalize(){
  free(player_blanc.current_queens);
  free(player_blanc.other_queens);
  player_blanc.current_queens=NULL;
  player_blanc.other_queens=NULL;
  // free(player_blanc.name);
  gsl_spmatrix_uint_free(player_blanc.graph->t);
  free(player_blanc.graph);
}






