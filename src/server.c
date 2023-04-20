#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// #include <gsl/gsl_spmatrix.h>
// #include <gsl/gsl_spmatrix_uint.h>
// #include <gsl/gsl_spblas.h>

#include "server.h"


struct player player_blanc;
struct player player_black;

void begining_position(unsigned int* queens[NUM_PLAYERS]){
    unsigned int *t=queens[0];
    unsigned int *t2=queens[1];
    int m=((N/10)+1)*4;
    int tmp=0;
    for(int i=1;i<=m/4;i++){
        t[tmp]=2*i+N*(N-1);
        tmp++;
        t[tmp]=N-1-2*i+N*(N-1);
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t[tmp]=N*(N-1)-N*2*i;
        tmp++;
        t[tmp]=N*(N-1)-N*2*i+N-1;
        tmp++;
    }
     tmp=0;
    for(int i=1;i<=m/4;i++){
        t2[tmp]=2*i;
        tmp++;
        t2[tmp]=N-1-2*i;
        tmp++;
    }
    for(int i=1;i<=m/4;i++){
        t2[tmp]=N*2*(i);
        tmp++;
        t2[tmp]=N*2*i+N-1;
        tmp++;
    }
    //printf("tmp2=%d \n",tmp);
}

int *graph_table(struct graph_t *graph){
    int *t=malloc(sizeof(int)*LENGHT*LENGHT);
    for(int i=0;i<N*N;i++){
     if(empty_cell(graph,i,N*N))   
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
void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS], int queens_number) {

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
    for(int i=0;i<N*N;i++){
        if(i!=0 && i%N==0) printf("\n");
        if(t[i]==-1) printf("  ");
    else printf("%d ",t[i] );
    }
    printf("\n");
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

int main(int argc, char* argv[]){
    /* START GETOPT */
    int turns=100;
    extern char *optarg;
    int opt=0;
    while((opt=getopt(argc, argv, "s:m:t:h")) != -1){
        switch(opt){
            case 'm':
                if(optarg!=NULL){
                    #undef LENGHT
                    #define LENGHT atoi(optarg)
                    printf("%d\n", LENGHT);
                }
                break;
            case 's':
                if(optarg!=NULL){
                    turns=atoi(optarg);
                }
                break;
            case 't':
                if(optarg[0]='c'){

                }
                else if(optarg[0]='d'){

                }
                else if(optarg[0]='t'){

                }
                else if(optarg[0]='8'){

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
    /* END GETOPT */
    //printf("%d\n", LENGHT);
    void *handle1;
    void *handle2;
        char *(*get_white_player_name)(void);
        char *(*get_black_player_name)(void);
        struct move_t(*white_move)(struct move_t previous_move);


        struct move_t(*black_move)(struct move_t previous_move);
        char*(*initiamize_white_player)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);
        char*(*initiamize_black_player)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);

        char *error;
        handle2 = dlopen ("libplayer2.so", RTLD_LAZY);
        handle1 = dlopen("libplayer1.so",RTLD_LAZY);
        if (!handle2 || !handle1  ) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        //Initialize players
        get_white_player_name = dlsym(handle1,"get_player_name");
        get_black_player_name = dlsym(handle2,"get_player_name");
        char *white_player = get_white_player_name();
        char *black_player = get_black_player_name();
        initiamize_white_player = dlsym(handle1,"initialize");
        initiamize_black_player = dlsym(handle2,"initialize");
        white_move=dlsym(handle1,"play");
        black_move=dlsym(handle2,"play");        
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        //Initialize graphs
        struct graph_t* graph = initialize_graph();
        initialize_graph_positions_classic(graph);
        //make_hole(graph,graph->num_vertices/2,2);
        struct graph_t* white_graph = initialize_graph();
        initialize_graph_positions_classic(white_graph);
        struct graph_t* black_graph = initialize_graph();
        initialize_graph_positions_classic(black_graph);

        //Initialize queens for each player
        int m=((N/10)+1)*4;
        unsigned int white_queens[m];
        unsigned int black_queens[m];
        unsigned int *queens[NUM_PLAYERS] = {white_queens,black_queens};
        begining_position(queens);
        initiamize_white_player(0,white_graph,m,queens);
        initiamize_black_player(1,black_graph,m,queens);
        //The starting board
        display(graph,queens,m);
        struct move_t move={-1,-1,-1};
        int player = start_player();
        //The game loop
        for(int i=0;i<turns;i++){
            printf("########## TOUR: %d ##########\n", i+1);
        if(player==BLACK){
            move=black_move(move);
            printf("Joueur: %s\n", black_player);
            execute_move(move,graph,queens[1]);
            print_move(move);
        }
        else{
            move=white_move(move);
            printf("Joueur: %s\n", white_player);
            execute_move(move,graph,queens[0]);
            print_move(move);
        }
        if(move.queen_dst==UINT_MAX || i==99){
            printf("\n game is finished: %s wins\n", (player ? black_player : white_player));
            display(graph,queens,m);
            //player? printf("%d \n", 2): printf("%d \n", 1);
            dlclose(handle1);
            dlclose(handle2);
            return 0;
            
        }
        player=next_player(player);
        display(graph,queens,m);

        }
        dlclose(handle1);
        dlclose(handle2);
    return 0;
}










