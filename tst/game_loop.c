#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <dlfcn.h>


#include "../src/grid.h"

void get_opt(int argc, char* argv[]){
  int turns;
  extern char *optarg;
  int opt = 0;
  while((opt = getopt(argc, argv, "m:t:h")) != -1){
    switch (opt)
      {
      case 'm':
	if(optarg != NULL){
	  turns = atoi(optarg);
	}
      
	break;
      case 't':
	if(optarg[0] == 'c'){
	}      
	break;
      case 'h':
	printf("usage: ./project [-h help]\n \t \t [-m allows you to specify the width of the game board] \n \t \t [-t allows you to specify the shape of the game board (square grid c, donut d, cloverleaf t or figure eight 8 ) \n]");
	return 0;
	break;
    
      default:
	break;
      }
  }
}

int random_or_config(){
      srand(time(NULL));
      int random_number = rand() % 2;
      return random_number;

}

int main(){
      int start_player = random_or_config();
      //INITIALISATION DES JOUEURS AVEC LES LIBPLAYERS.SO
      void *player1 = dlopen ("libplayer1.so", RTLD_LAZY);
      void *player2 = dlopen ("libplayer1.so", RTLD_LAZY);
      if (!player2 || !player1  ){
            fputs (dlerror(), stderr);
            exit(1);
      }
      char*(*initialize1)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]) = dlsym(player1,"initialize");
      char*(*initialize2)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]) = dlsym(player2,"initialize");
      char *error;
      if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
      }
      //FIN D'INITIALISATION DES JOUEURS AVEC LES LIBPLAYERS.SO

      //INITIALISATION DES GRAPHES
      struct graph_t* graph = initialize_graph();
      initialize_graph_positions_classic(graph);
      struct graph_t* graph1 = initialize_graph();
      initialize_graph_positions_classic(graph1);
      struct graph_t* graph2 = initialize_graph();
      initialize_graph_positions_classic(graph2);
      int m=((N/10)+1)*4;
      unsigned int queens_player1[m], queens_palyer2[m];
      unsigned int *queens[NUM_PLAYERS]={queens_player1,queens_palyer2};
      begining_position(queens);
      initialize1(0,graph1,m,queens);
      initialize2(1,graph2,m,queens);
      display(graph,queens,m);
      //FIN D'INITIALISATION DES GRAPHES

      for(int i = 0; i<3; i++){

      }
      dlclose(player1);
      dlclose(player2);
      printf("\tOK\n");
      return 0;
}
  
