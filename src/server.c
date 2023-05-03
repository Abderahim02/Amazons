#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>

#include "server.h"




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:


extern struct graph_t * initialize_graph(unsigned int length);

extern void free_graph(struct graph_t* g);

extern gsl_spmatrix_uint* copy_matrix(struct graph_t *graph,int size);

extern struct graph_t *graph_cpy(const struct graph_t *graph, int size);

extern int empty_cell(struct graph_t *graph, int x, unsigned int size);



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


extern struct player player_blanc;

char *(*get_player1_name)(void);
char *(*get_player2_name)(void);

void(*initialize_player1)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);
void(*initialize_player2)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);

void(*finalize_player1)(void);
void(*finalize_player2)(void );


struct move_t(*play1)(struct move_t previous_move);
struct move_t(*play2)(struct move_t previous_move);
        



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


void print_queens(struct player p, int num_queens ){
    for(int i=0; i < num_queens ; ++i){
        printf("current [%d] = %d /// other[%d] = %d\n", i,p.current_queens[i] ,i, p.other_queens[i]);
    }
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
//function that prints the move
void print_move(struct move_t move){
    printf("move from %d to %d and arrow at %d \n", move.queen_src, move.queen_dst,move.arrow_dst);
}




unsigned int* table_q(int length){
     unsigned int m = ((length / 10) + 1) * 4;
    unsigned int *q = malloc(m * sizeof(unsigned int));
    

    // Initialisation des tableaux
    for (unsigned int i = 0; i < m; i++) {
        q[i] = i;  // exemple d'initialisation
    }

    return q;
}


void copy(unsigned int *queen[NUM_PLAYERS],unsigned int *q[NUM_PLAYERS] ,int m){
     for (int i = 0; i < m; i++) {
        q[0][i] = queen[0][i];
        q[1][i] = queen[1][i];
    }

}
/*this function makes a graph depending on the type of graph taken as argument
*/
void make_graph(struct graph_t * g, unsigned int m ,char s ){ 
    switch(s){
        case 'c' :
            g->num_vertices = m*m;
            break;
        case 'd':
            make_hole(g, (m/3)*m + m/3 , m/3);
            g->num_vertices = 8*m*m/9;
            break;
        case 't':
            make_hole(g, m/5*m + m/5, m/5 );
            make_hole(g, m/5*m + 3*m/5 , m/5 );
            make_hole(g, 3*m/5*m + m/5, m/5 );
            make_hole(g, 3*m/5*m + 3*m/5, m/5 );
            g->num_vertices = 21*m*m / 25 ;
            break;
        case '8':
            make_hole(g, 2*(m/4) * m + m/4, m/4 );
            make_hole(g, (m/4) * m + 2*m/4 , m/4 );
            g->num_vertices = 21*m*m / 25 ;
            break;
        default :
            break;
  }
}

int main(int argc, char* argv[]){
    /* START GETOPT */
    unsigned int length=8;
    unsigned int turns=50;
    extern char *optarg;
    int opt=0;
    char graph_type  = 'c'; //we set the default type of world at squared world
    while((opt=getopt(argc, argv, "s:m:t:h")) != -1){
        switch(opt){
            case 'm':
                if(optarg!=NULL){
                    length=atoi(optarg); //we get the lenght of the grid== the variable m
                }
                break;
            case 's':
                if(optarg!=NULL){
                    turns=atoi(optarg); // we get the number of turns
                }
                break;
            case 't':
                 if(optarg!=NULL){
                    graph_type = optarg[0]; // we get the type of world
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
     if (argc > 1) {
     void * lib1 = dlopen(argv[argc-2], RTLD_LAZY); 
     void * lib2 = dlopen(argv[argc-1], RTLD_LAZY); 
     if (lib1 == NULL || lib2 == NULL ) { 
        printf("bibliothèque vide\n"); 
        exit(EXIT_FAILURE); 
    } 
    printf("%d %d \n",length, length);
    printf("#\n");

    //get player name functions.
    get_player1_name= dlsym(lib1,"get_player_name");
    get_player2_name = dlsym(lib2,"get_player_name");
        
    //Initialize player functions.
    initialize_player1 = dlsym(lib1,"initialize");
    initialize_player2 = dlsym(lib2,"initialize");

    //play functions 
    play1=dlsym(lib1,"play");
    play2=dlsym(lib2,"play");
    //opening=dlsym(lib1,"opening_play");
    //finalize player functions.
    finalize_player1 = dlsym(lib1,"finalize");
    finalize_player2 = dlsym(lib2,"finalize");
    

    
    char *white_player = get_player1_name();
    char *black_player = get_player2_name();
        //Initialize graphs
        struct graph_t* graph = initialize_graph(length);

        struct graph_t* white_graph = initialize_graph(length);
        struct graph_t* black_graph = initialize_graph(length);

        //we make hole or not depending on the type of the grapg for the tree graphs 
        make_graph(graph, length, graph_type);
        make_graph(white_graph, length, graph_type);
        make_graph(black_graph, length, graph_type);

        //Initialize queens for each player
        unsigned int m=((length/10)+1)*4;
        unsigned int white_queens[m];
        unsigned int black_queens[m];
        unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};

        unsigned int *queens1[NUM_PLAYERS]= {table_q(length),table_q(length)};
        unsigned int *queens2[NUM_PLAYERS]={table_q(length),table_q(length)};
        

        begining_position(queens, length);
         copy(queens, queens1, m);
         copy(queens,queens2,m);
        initialize_player1(0,white_graph,m,queens1);
        initialize_player2(1,black_graph,m,queens2);
        //The starting board
       /;
        sdl_display(graph,queens,m,length);
        // make_hole(graph, 10, 2);
       // display(graph,queens,m);

        struct move_t move={-1,-1,-1};
        int player = start_player();
        //The game loop
        for(unsigned int i=0;i<turns;i++){
         //  printf("########## TOUR: %d ##########\n", i+1);
        if(player==BLACK){
            move=play2(move);
         //   printf("Joueur: %s\n", black_player);
            execute_move(move,graph,queens[1]);

        }
        else{
            move=play1(move);
            execute_move(move,graph,queens[0]);
          //  print_move(move);
        }
        if(move.queen_dst==UINT_MAX){
            if(i==length*length) printf("eqalité\n");
            else printf("\n game is finished: %s wins\n", (player ? black_player : white_player));
            sdl_display(graph,queens,m,length);
          //  display(graph,queens,m);

            free_graph(graph);
            finalize_player1();
            finalize_player2();
            dlclose(lib1);
            dlclose(lib2);
            return 0;
            
        }
        player=next_player(player);
        sdl_display(graph,queens,m,length);
        //display(graph,queens,m);

        }
        free_graph(graph);
        finalize_player1();
        finalize_player2();
        dlclose(lib1);
        dlclose(lib2);
    }
    return 0;

}
