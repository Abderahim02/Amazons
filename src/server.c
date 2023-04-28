#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
// #include <gsl/gsl_spmatrix.h>
// #include <gsl/gsl_spmatrix_uint.h>
// #include <gsl/gsl_spblas.h>

#include "server.h"


//struct player player_blanc;

char *(*get_player1_name)(void);
char *(*get_player2_name)(void);

void(*initialize_player1)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);
void(*initialize_player2)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);

struct move_t(*play1)(struct move_t previous_move);
struct move_t(*play2)(struct move_t previous_move);
        



void begining_position(unsigned int* queens[NUM_PLAYERS]){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((LENGHT/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=2*i+LENGHT*(LENGHT-1);
        tmp++;
        t[tmp]=LENGHT-1-2*i+LENGHT*(LENGHT-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=LENGHT*(LENGHT-1)-LENGHT*2*i;
        tmp++;
        t[tmp]=LENGHT*(LENGHT-1)-LENGHT*2*i+LENGHT-1;
        tmp++;
    }
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=2*i;
        tmp++;
        t2[tmp]=LENGHT-1-2*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=LENGHT*2*(i);
        tmp++;
        t2[tmp]=LENGHT*2*i+LENGHT-1;
        tmp++;
    }
    //printf("tmp2=%d \n",tmp);
}

int *graph_table(struct graph_t *graph){
    int *t=(int *)malloc(sizeof(int)*LENGHT*LENGHT);
    for(int i=0;i<LENGHT*LENGHT;i++){
     if(empty_cell(graph,i,LENGHT*LENGHT))   
            t[i]=-1;
        else t[i]=0;
    }
    return t;
}

void table(unsigned int* queens[NUM_PLAYERS], int *t, int queens_number){
    for(int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}

/*
void display(struct graph_t* graph, unsigned int* queens[LENGHTUM_PLAYERS], int queens_number) {

    int *t = graph_table(graph);
    table(queens, t, queens_number);

    unsigned int max_val = 0;
    for (int i = 0; i < graph->num_vertices; i++) {
        unsigned int val = t[i];
        if (val > max_val) {
            max_val = val;
        }
    }

    unsigned int field_width = snprintf(NULL, 0, "%u", max_val) + 1; // +1 for the space

    printf("\n");
    for (int i = 0; i < sqrt(graph->num_vertices); i++) {
        for (int j = 0; j < sqrt(graph->num_vertices); j++) {
            if (j % 2 == 0 && i % 2 == 0) {
                printf("\x1b[107m %*d \x1b[0m", field_width, t[i]);
            }
            else if (j % 2 != 0 && i % 2 == 0) {
                printf("\x1b[48;2;165;42;42m %*d \x1b[0m", field_width, t[i]);
            }
            if (j % 2 != 0 && i % 2 != 0) {
                printf("\x1b[107m %*d \x1b[0m", field_width, t[i]);
            }
            else if (j % 2 == 0 && i % 2 != 0) {
                printf("\x1b[48;2;165;42;42m %*d \x1b[0m", field_width, t[i]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

*/
void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number){
    int *t = graph_table(graph);
    table(queens,t,queens_number);
    for(int i=0;i<LENGHT*LENGHT;i++){
        if(i!=0 && i%LENGHT==0) printf("\n");
        if(t[i]==-1) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n");
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

// int main(int argc, char* argv[]){
//     /* START GETOPT */
//     int turns=2;
//     extern char *optarg;
//     int opt=0;
//     while((opt=getopt(argc, argv, "s:m:t:h")) != -1){
//         switch(opt){
//             case 'm':
//                 if(optarg!=NULL){
//                     #undef LELENGHTGHT
//                     #define LELENGHTGHT atoi(optarg)
//                     printf("%d\n", LELENGHTGHT);
//                 }
//                 break;
//             case 's':
//                 if(optarg!=NULL){
//                     turns=atoi(optarg);
//                 }
//                 break;
//             case 't':
//                 if(optarg[0]=='c'){
                    
//                 }
//                 else if(optarg[0]=='d'){

//                 }
//                 else if(optarg[0]=='t'){

//                 }
//                 else if(optarg[0]=='8'){

//                 }
//                 break;
//             case 'h':
//                 printf("usage: ./project [-h help]\n \t \t [-m allows you to specify the width of the game board] \n \t \t [-t allows you to specify the shape of the game board (square grid c, donut d, cloverleaf t or figure eight 8 ) \n]");
//                 return 0;
//                 break;
//             default:
//                 break;
//         }
//     }
//     /* ELENGHTD GETOPT */
//     //printf("%d\n", LELENGHTGHT);
//      if (argc > 1) {
//      void * lib1 = dlopen(argv[argc-2], RTLD_NOW); 
//      void * lib2 = dlopen(argv[argc-1], RTLD_NOW); 
//      if (lib1 == NULL || lib2 == NULL ) { 
//         printf("bibliothèque vide\n"); 
//         exit(EXIT_FAILURE); 
//     } 

//     //get player name functions.
//       get_player1_name= dlsym(lib1,"get_player_name");
//       get_player2_name = dlsym(lib2,"get_player_name");
        
//     //Initialize player functions.
//     initialize_player1 = dlsym(lib1,"initialize");
//     initialize_player2 = dlsym(lib2,"initialize");

//     //play functions 
//     play1=dlsym(lib1,"play");
//     play2=dlsym(lib2,"play");
//     //opening=dlsym(lib1,"opening_play");
    

    
//     char *white_player = get_player1_name();
//     char *black_player = get_player2_name();
        
               
       
//         //Initialize graphs
//         struct graph_t* graph = initialize_graph();
//         initialize_graph_positions_classic(graph);
//         //make_hole(graph,graph->num_vertices/2,2);
//         struct graph_t* white_graph = initialize_graph();
//         initialize_graph_positions_classic(white_graph);
//         struct graph_t* black_graph = initialize_graph();
//         initialize_graph_positions_classic(black_graph);

//         //Initialize queens for each player
//         int m=((LENGHT/10)+1)*4;
//         unsigned int white_queens[m];
//         unsigned int black_queens[m];
//         unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
//         begining_position(queens);
//         initialize_player1(0,white_graph,m,queens);
//         initialize_player2(1,black_graph,m,queens);
//         //The starting board
//         display(graph,queens,m);
//         struct move_t move={-1,-1,-1};
//         int player = start_player();
//         //The game loop
//         for(int i=0;i<turns;i++){
//             printf("########## TOUR: %d ##########\n", i+1);
//         if(player==BLACK){
//             move=play2(move);
//             printf("Joueur: %s\n", black_player);
//             execute_move(move,graph,queens[1]);
//             print_move(move);
//         }
//         else{
//             move=play1(move);
//             printf("Joueur: %s\n", white_player);
//             execute_move(move,graph,queens[0]);
//             print_move(move);
//         }
//         if(move.queen_dst==UINT_MAX|| i==99){
//             printf("\n game is finished: %s wins\n", (player ? black_player : white_player));
//             display(graph,queens,m);
//             //player? printf("%d \n", 2): printf("%d \n", 1);
//             free_graph(graph);
//             free_graph(white_graph);
//             free_graph(black_graph);
//             dlclose(lib1);
//             dlclose(lib2);
//             return 0;
            
//         }
//         player=next_player(player);
//         display(graph,queens,m);

//         }
//         free_graph(graph);
//         free_graph(white_graph);
//         free_graph(black_graph);
//         dlclose(lib1);
//         dlclose(lib2);
//      }
//     return 0;
// }




void make_graph(struct graph_t * g, unsigned int m ,char s){ 
    // m = (unsigned int ) LENGHT;
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
    int turns=2;
    extern char *optarg;
    int opt=0;
    struct graph_t* graph = initialize_graph();
        initialize_graph_positions_classic(graph);
    while((opt=getopt(argc, argv, "s:m:t:h")) != -1){
        switch(opt){
            case 'm':
                if(optarg!=NULL){
                    #undef LELENGHTGHT
                    #define LELENGHTGHT atoi(optarg)
                    printf("%d\n", LELENGHTGHT);
                }
                break;
            case 's':
                if(optarg!=NULL){
                    turns=atoi(optarg);
                }
                break;
            case 't':
                printf("t = %s", optarg[0]);
                if(optarg[0]=='c'){
                    make_graph(graph, LENGHT, 'c');
                }
                else if(optarg[0]=='d'){
                    make_graph(graph, LENGHT, 'd');
                }
                else if(optarg[0]=='t'){
                    make_graph(graph, LENGHT, 't');
                }
                else if(optarg[0]=='8'){
                    make_graph(graph, LENGHT, '8');
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
    /* ELENGHTD GETOPT */
    //printf("%d\n", LELENGHTGHT);
     if (argc > 1) {
     void * lib1 = dlopen(argv[argc-2], RTLD_NOW); 
     void * lib2 = dlopen(argv[argc-1], RTLD_NOW); 
     if (lib1 == NULL || lib2 == NULL ) { 
        printf("bibliothèque vide\n"); 
        exit(EXIT_FAILURE); 
    } 

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
    

    
    char *white_player = get_player1_name();
    char *black_player = get_player2_name();
        //Initialize graphs
        
        //make_hole(graph,graph->num_vertices/2,2);
        struct graph_t* white_graph = initialize_graph();
        initialize_graph_positions_classic(white_graph);
        struct graph_t* black_graph = initialize_graph();
        initialize_graph_positions_classic(black_graph);

        //Initialize queens for each player
        int m=((LENGHT/10)+1)*4;
        unsigned int white_queens[m];
        unsigned int black_queens[m];
        unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
        begining_position(queens);
        initialize_player1(0,white_graph,m,queens);
        initialize_player2(1,black_graph,m,queens);
        //The starting board
        display(graph, queens, m);
        printf("Lenght  %d\n",LENGHT);
        make_graph(graph, LENGHT,'8');
        display(graph,queens,m);
        dlclose(lib1);
        dlclose(lib2);
     }
    return 0;
}
