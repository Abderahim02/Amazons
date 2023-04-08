#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#include "graph.h"
#include "player.h"
#include "move.h"
#include "grid.h"



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


// int main() { 
//   return 0;
// }
  
