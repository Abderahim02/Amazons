
#include "server_functions.h"




////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

extern struct graph_t * initialize_graph(unsigned int length);

extern struct graph_t* initialize_eight_graph(struct graph_t* graph, unsigned int length);

extern struct graph_t* initialize_trefle_graph(struct graph_t* graph, unsigned int length);

extern struct graph_t * initialize_donut_graph(struct graph_t* graph, unsigned int length);

extern void free_graph(struct graph_t* g);

extern void make_graph(struct graph_t * g, unsigned int m ,char s );

extern struct graph_t *graph_cpy(const struct graph_t *graph);

extern int empty_cell(struct graph_t *graph, int x, unsigned int size);


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//extern struct player_t player_blanc;

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



int main(int argc, char* argv[]){
    unsigned int length=10;
    unsigned int turns=700;
    char graph_type='c';
    get_opt(argc, argv, &graph_type, &length, &turns);
    //printf("turns = %d\n", turns);
    printf("%d %d \n",length, length);
    printf("#\n");
    if (argc > 1) {
        void * lib1 = dlopen(argv[argc-2], RTLD_LAZY); 
        void * lib2 = dlopen(argv[argc-1], RTLD_LAZY); 
        if (lib1 == NULL || lib2 == NULL ) { 
            printf("bibliothèque vide\n"); 
            exit(EXIT_FAILURE); 
        }

        //get player name functions.
        get_player1_name= dlsym(lib1,"get_player_name");
        get_player2_name = dlsym(lib2,"get_player_name");
        char *white_player = get_player1_name();
        char *black_player = get_player2_name();
        (void) white_player;
        (void) black_player;
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
    

        //Initialize graphs
        struct graph_t* graph = initialize_graph(length);
        make_graph(graph, length, graph_type);
        struct graph_t* white_graph = graph_cpy(graph);
        struct graph_t* black_graph = graph_cpy(graph);

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
        //sdl_display(graph,queens,m,length);
        display(graph,queens,m);

        struct move_t move={-1,-1,-1};
        int player = start_player();
        //The game loop
        for(unsigned int i=0;i<turns;i++){
            if(player==BLACK){
                move=play2(move);
                //printf("ANA\n");
                execute_move(move,graph,queens[1]);
            }
            else{
                move=play1(move);
                execute_move(move, graph, queens[0]);
            }
            if(move.queen_dst==UINT_MAX){
                //if(i==length*length) printf("eqalité\n");
                printf("\n game is finished: %s wins\n", (player ? black_player : white_player));
                //sdl_display(graph,queens,m,length);
                display(graph,queens,m);
                printf("%d\n" , (player+1)%2);
                free_graph(graph);
                finalize_player1();
                finalize_player2();
                dlclose(lib1);
                dlclose(lib2);
                return 0;
            
            }
            player=next_player(player);
            //sdl_display(graph,queens,m,length);
            display(graph,queens,m);

        }
        free_graph(graph);
        finalize_player1();
        finalize_player2();
        dlclose(lib1);
        dlclose(lib2);
    }
    return 0;
}
