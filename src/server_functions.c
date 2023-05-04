#include <stdio.h>
#include <stdlib.h>
#include "server_functions.h"
#include <time.h>




int empty_cell(struct graph_t *graph, int x, unsigned int size);

int *graph_table(struct graph_t *graph){
    unsigned int length=sqrt(graph->t->size1);
    int *t=(int *)malloc(sizeof(int)*length*length);
    for(unsigned int i=0 ; i<length*length;i++){
     if(empty_cell(graph,i,length*length))   
            t[i]=-1;
        else t[i]=0;
    }
    return t;
}

void table(unsigned int* queens[NUM_PLAYERS], int *t, unsigned int queens_number){
    for(unsigned int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}



void sdl_display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number, int size){
    // all int numbers to display different colors with sdl.
  int n=0;   // color black in sdl
  //int nel=256*50; //
  //int nt=65536*50;
  int b=16777215; // wolor white 
  //int bt=65536*255+256*100+50;
  //int bel=65536*100+255*256; 
  //int g=255;   // color red 
  int bh=65536*255+140;
  int nh=65536*80+100;
   int *t=graph_table(graph);
   table(queens,t,queens_number);
  for(int i=0;i<size*size;i++){
    if(i%size==0 && i!=0) printf("\n");
    if(t[i]==0) printf("%d ",nh );
    if(t[i]==-1) printf("%d ",bh);
    if(t[i]==1) printf("%d ",b);
     if(t[i]==2) printf("%d ", n);
  }
    free(t);
    printf("\n");
    printf("\n");
}

void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number){
    unsigned int length=sqrt(graph->t->size1);
    int *t = graph_table(graph);
    table(queens,t,queens_number);
    for(unsigned int i=0;i<length*length;i++){
        if(i!=0 && i%length==0) printf("\n");
        if(t[i]==-1) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n \n");
    
    free(t);
}


int start_player(){
  srand(time(NULL));
  int ran=rand();
  return ran%2;
}

int next_player(int player){
    if(player==BLACK){
        return WHITE;
    }
    return BLACK;
}


unsigned int* allouer_table(int length){
     unsigned int m = ((length / 10) + 1) * 4;
    unsigned int *q = malloc(m * sizeof(unsigned int));
    

    // Initialisation des tableaux
    for (unsigned int i = 0; i < m; i++) {
        q[i] = i;  // exemple d'initialisation
    }

    return q;
}


void queens_copy(unsigned int *queen[NUM_PLAYERS],unsigned int *q[NUM_PLAYERS] ,int m){
     for (int i = 0; i < m; i++) {
        q[0][i] = queen[0][i];
        q[1][i] = queen[1][i];
    }

}



void initialize_donut_graph(struct graph_t* g, unsigned int m){
    make_hole(g, (m/3)*m + m/3 , m/3);
    g->num_vertices = 8*m*m/9;
}

void initialize_trefle_graph(struct graph_t* g, unsigned int m){
    make_hole(g, m/5*m + m/5, m/5 );
    make_hole(g, m/5*m + 3*m/5 , m/5 );
    make_hole(g, 3*m/5*m + m/5, m/5 );
    make_hole(g, 3*m/5*m + 3*m/5, m/5 );
    g->num_vertices = 21*m*m / 25 ;
}

void initialize_eight_graph(struct graph_t* g , unsigned int m){
    make_hole(g, 2*(m/4) * m + m/4, m/4 );
    make_hole(g, (m/4) * m + 2*m/4 , m/4 );
    g->num_vertices = 21*m*m / 25 ;
}

/*this function makes a graph depending on the type of graph taken as argument
*/
void make_graph(struct graph_t * g, unsigned int m ,char s ){ 
    switch(s){
        case 'c' :
            g->num_vertices = m*m;
            break;
        case 'd':
            initialize_donut_graph(g, m);
            break;
        case 't':
            initialize_trefle_graph(g, m);
            break;
        case '8':
            initialize_eight_graph(g, m);
            break;
        default :
            break;
  }
}

