#include <stdio.h>
#include <stdlib.h>
#include "graph.h"




void sdl_display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number, int size){
    // all int numbers to display different colors with sdl.
  int n=0;   // color black in sdl
  int nel=256*50; //
  int nt=65536*50;
  int b=16777215; // wolor white 
  int bt=65536*255+256*100+50;
  int bel=65536*100+255*256; 
  int g=255;   // color red 
  int bh=65536*255+140;
  int nh=65536*80+100;
   int *t=graph_table(graph);
   table(queens,t,queens_number);
  for(int i=0;i<size*size;i++){
    if(i%size==0 && i!=0) printf("\n");
    // printf("%d " ,t[i]);
    if(t[i]==0) printf("%d ",nh );
    if(t[i]==-1) printf("%d ",bh);
    if(t[i]==1) printf("%d ",b);
     if(t[i]==2) printf("%d ", n);
  }
    printf("\n");
    printf("\n");
}



//  if(world_get(world,i)==BLACK){
//         if(world_get_sort(world,i)==2)  printf("%d ",nt );
//         else if(world_get_sort(world,i)==3)  printf("%d ",nel);
//         else if(world_get_sort(world,i)==4)  printf("%d ",nh);
//         else  printf("%d ",n );
//     }
//     else if(world_get(world,i)==WHITE){
//         if (world_get_sort(world,i)==2) printf("%d ",bt );
//         else if(world_get_sort(world,i)==3)  printf("%d ",bel);
//         else if(world_get_sort(world,i)==4)  printf("%d ",bh);
//         else printf("%d ",b);
//     }
//     else
//       p