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




extern int empty_cell(struct graph_t *graph, int x, unsigned int size);

/*This function parses command-line arguments to extract the game 
settings, including the game type, board size, and number of turns.
It takes in argc and argv[] parameters from the command line and 
sets the values of type, length, and turns pointers.*/
void get_opt(int argc, char* argv[], char* type, unsigned int *length, unsigned int* turns){
    extern char *optarg;
    int opt=0; //we set the default type of world at squared world
    while((opt=getopt(argc, argv, "s:m:t:h")) != -1){
        switch(opt){
            case 'm':
                if(optarg!=NULL){
                    *length=atoi(optarg); // update the value of length
                }
                break;
            case 's':
                if(optarg!=NULL){
                    //printf("turns = %d\n", *turns);
                    *turns=atoi(optarg); // update the value of turns
                    //printf("turns = %d\n", *turns);
                }
                break;
            case 't':
                 if(optarg!=NULL){
                    *type = optarg[0]; // update the value of type
                }
                break;
            case 'h':
                printf("usage: ./project [-h help]\n \t \t [-m allows you to specify the width of the game board] \n \t \t [-t allows you to specify the shape of the game board (square grid c, donut d, cloverleaf t or figure eight 8 ) \n]");
                return;
                break;
            default:
                break;
        }
    }
}

/*This function creates a table representation of the game board using the graph data structure. 
It returns an integer pointer to the table.*/
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


/*This function takes in the positions of the queens and the number of queens and 
creates a table representation of the game board, where each 
cell in the table represents a position on the board, and a value 
of 1 indicates that there is a queen in that position.*/
void table(unsigned int* queens[NUM_PLAYERS], int *t, unsigned int queens_number){
    for(unsigned int i=0;i<queens_number;i++){
        t[queens[0][i]]=1;
        t[queens[1][i]]=2;
    }
    
}


/*This function is used to display the current state of the game 
using the SDL library. It takes in the game board, the positions 
of the queens, the number of queens, and the size of the window 
as parameters. It then displays the game board and the queen 
positions on the screen.*/
void sdl_display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],int queens_number, int size){

    int n=0;//green 255*255
    int b=255+255+0;//brown \\white  16777215
    int bh=65536*255+140;
    (void) bh;
    int nh=160*65536+100*255+19;//50+255*30+65536*15;
    int c0=205*205;
    int c1=16777215;
//160*65536+100*255+19; red: 255+255+0;

//65536*80+100;
int tmp=0;
    int *t=graph_table(graph);
    table(queens,t,queens_number);
    for(int i=0;i<size*size;i++){
        if(i%size==0 && i!=0) printf("\n");
        if(t[i]==-1) printf("%d ",nh);
        if(t[i]==1) printf("%d ",b);
        if(t[i]==2) printf("%d ", n);
        if(t[i]==0){
            if(tmp==0) printf("%d ", c0);
            if(tmp==1) printf("%d ",c1 );
        }
        if((i+1)%size!=0 ) tmp=(tmp+1)%2;
    }
    free(t);
    printf("\n");
    printf("\n");
}

/*This function is used to display the current state of the game 
using the console. It takes in the game board, the positions of 
the queens, and the number of queens as parameters. It then 
displays the game board and the queen positions on the console.*/
void display(struct graph_t* graph, unsigned int* queens[NUM_PLAYERS],unsigned int queens_number){
    unsigned int length=sqrt(graph->t->size1);
    int *t = graph_table(graph);
    table(queens,t,queens_number);
    int tmp=0;
    for(unsigned int i=0;i<length*length;i++){
            if(i%length==0 && i!=0) printf("\n");
        if(t[i]==-1) printf(ANSI_COLOR_BLACK "  " ANSI_COLOR_RESET);
        if(t[i]==1) printf(ANSI_COLOR_GREEN "♕ " ANSI_COLOR_RESET);
        if(t[i]==2) printf(ANSI_COLOR_BLUE "♕ " ANSI_COLOR_RESET);
        if(t[i]==0){
            if(tmp==0) printf(ANSI_COLOR_PINK "  " ANSI_COLOR_RESET);
            if(tmp==1) printf(ANSI_COLOR_VIOLET "  " ANSI_COLOR_RESET);
        }
        if((i+1)%length!=0 ) tmp=(tmp+1)%2;
    }
    printf(" \n \n");
    
    free(t);
}

/*This function allocates memory for a table with the given length and returns 
a pointer to the table.*/
unsigned int* allouer_table(unsigned int length){
    unsigned int m = ((length / 10) + 1) * 4;
    unsigned int *q = (unsigned int *)malloc(sizeof(unsigned int)*m);
    // Initialisation des tableaux
    for (unsigned int i = 0; i < m; i++) {
        q[i] = i;  // exemple d'initialisation
    }
    return q;
}

/*This function copies the positions of the queens from one array 
to another. It takes in the source and destination arrays of the positions
 of the queens and the number of queens as parameters.*/
void queens_copy(unsigned int *queen[NUM_PLAYERS],unsigned int *q[NUM_PLAYERS] ,int m){
     for (int i = 0; i < m; i++) {
        q[0][i] = queen[0][i];
        q[1][i] = queen[1][i];
    }

}

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
