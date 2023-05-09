
#include "server_functions.h"

#define ANSI_COLOR_RED     "\e[41m"
#define ANSI_COLOR_GREEN   "\e[42m"
#define ANSI_COLOR_ORANGE  "\e[43m"
#define ANSI_COLOR_YELLOW  "\e[0;103m"
#define ANSI_COLOR_BLUE    "\e[44m"
#define ANSI_COLOR_PINK    "\e[0;105m"
#define ANSI_COLOR_CYAN    "\e[46m"
#define ANSI_COLOR_VIOLET  "\e[45m"
#define ANSI_COLOR_BLACK  "\e[40m"
#define ANSI_COLOR_RESET   "\e[0m"





struct graph_t *graph_cpy(const struct graph_t *graph){
  struct graph_t *graph_cpy = malloc(sizeof(struct graph_t));
  gsl_spmatrix_uint *matrix_copy=gsl_spmatrix_uint_alloc(graph->t->size1,graph->t->size2);
  graph_cpy->t=gsl_spmatrix_uint_compress(matrix_copy, GSL_SPMATRIX_CSR);
  gsl_spmatrix_uint_memcpy(graph_cpy->t, graph->t); 
  gsl_spmatrix_uint_free(matrix_copy);
  graph_cpy->num_vertices = graph->num_vertices;
  return graph_cpy;
}
/*This function is used to start a new game by choosing the game 
mode. It returns an integer indicating the chosen player.*/
int start_player(){
  srand(time(NULL));
  int ran=rand();
  return ran%2;
}
/*This function takes in the current player and returns the next player's
 number.*/
int next_player(int player){
    if(player==BLACK){
        return WHITE;
    }
    return BLACK;
}
