#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>
#include "server_functions.h"




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern struct graph_t * initialize_graph(unsigned int length);

extern struct graph_t* initialize_eight_graph(struct graph_t* graph, unsigned int length);

extern struct graph_t* initialize_trefle_graph(struct graph_t* graph, unsigned int length);

extern struct graph_t * initialize_donut_graph(struct graph_t* graph, unsigned int length);

extern void free_graph(struct graph_t* g);

extern void make_graph(struct graph_t * g, unsigned int m ,char s );


extern struct graph_t *graph_cpy(const struct graph_t *graph, int size);

extern int empty_cell(struct graph_t *graph, int x, unsigned int size);



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//extern struct player player_blanc;

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
        
// to display the queens positions
void print_queens(struct player p, int num_queens ){
    for(int i=0; i < num_queens ; ++i){
        printf("current [%d] = %d /// other[%d] = %d\n", i,p.current_queens[i] ,i, p.other_queens[i]);
    }
}

//function that prints the move
void print_move(struct move_t move){
    printf("move from %d to %d and arrow at %d \n", move.queen_src, move.queen_dst,move.arrow_dst);
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
        make_graph(graph, length, graph_type);
        struct graph_t* white_graph = graph_cpy(graph, length);
        struct graph_t* black_graph = graph_cpy(graph, length);

        //we make hole or not depending on the type of the grapg for the tree graphs 

        //Initialize queens for each player
        unsigned int m=((length/10)+1)*4;
        unsigned int white_queens[m];
        unsigned int black_queens[m];
        unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
        //to creat a copy of the table queens for the first player
        unsigned int *queens1[NUM_PLAYERS]= {allouer_table(length),allouer_table(length)};
        //to creat a copy of the table queens for the first player
        unsigned int *queens2[NUM_PLAYERS]={allouer_table(length),allouer_table(length)};
        // to initialize queens table 
        begining_position(queens, length);
        // copy queens in queens1 and queens2
        queens_copy(queens, queens1, m);
        queens_copy(queens,queens2,m);

        initialize_player1(0,white_graph,m,queens1);
        initialize_player2(1,black_graph,m,queens2);
        //The starting board
    
        sdl_display(graph,queens,m,length);
        //display(graph,queens,m);

        struct move_t move={-1,-1,-1};
        int player = start_player();
        //The game loop
        for(unsigned int i=0;i<turns;i++){
        if(player==BLACK){
            move=play2(move);
            execute_move(move,graph,queens[1]);
        }
        else{
            move=play1(move);
            execute_move(move,graph,queens[0]);
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
