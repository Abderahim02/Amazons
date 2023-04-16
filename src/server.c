
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
int empty_cell(struct graph_t *graph, int x, int size){
    for(int i=0;i<size;i++){

        if(gsl_spmatrix_uint_get(graph->t, x, i)!=NO_DIR) return 0;
    }
    return 1;
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

int main(int argc,char* argv[]){
    // int param;
    // int m=8;
    // char t='c';
    // while((param = getopt(argc, argv, "m:t")) != -1){   
    //     switch(param){ 
    //   case 'm': 
    //     m = atoi(optarg); 
    //     break; 
    //   case 't':
    //     t=*optarg;
    //     break;  
    //   default: 
    //     abort(); 
    //  } 
    // }

    void *handle1;
    void *handle2;
        char*(*player_name1)(void);
        struct move_t(*play1)(struct move_t previous_move);
    int (*get_neighbor)(int pos, enum dir_t dir, struct graph_t* graph);


        struct move_t(*play2)(struct move_t previous_move);
        char*(*player_name2)(void);
        char*(*initialize1)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);
        char*(*initialize2)(unsigned int player_id, struct graph_t* graph,
                unsigned int num_queens, unsigned int* queens[NUM_PLAYERS]);

        char *error;
        handle2 = dlopen ("libplayer2.so", RTLD_LAZY);
        handle1 = dlopen("libplayer1.so",RTLD_LAZY);
        if (!handle2 || !handle1  ) {
            fputs (dlerror(), stderr);
            exit(1);
        }
        player_name1 = dlsym(handle1,"get_player_name");
        player_name2 = dlsym(handle2,"get_player_name");
        initialize1 = dlsym(handle1,"initialize");
        initialize2 = dlsym(handle2,"initialize");
        get_neighbor=dlsym(handle2,"get_neighbor");
        play1=dlsym(handle1,"play");
        play2=dlsym(handle2,"play");        
        if ((error = dlerror()) != NULL)  {
            fputs(error, stderr);
            exit(1);
        }
        struct graph_t* graph = initialize_graph();
        initialize_graph_positions_classic(graph);
        //make_hole(graph,graph->num_vertices/2,2);
        struct graph_t* graph1 = initialize_graph();
        initialize_graph_positions_classic(graph1);
        struct graph_t* graph2 = initialize_graph();
        initialize_graph_positions_classic(graph2);
        int m=((N/10)+1)*4;
        unsigned int queens_player1[m];
        unsigned int queens_palyer2[m];
        unsigned int *queens[NUM_PLAYERS] = {queens_player1,queens_palyer2};
        begining_position(queens);
        initialize1(0,graph1,m,queens);
        initialize2(1,graph2,m,queens);
        display(graph,queens,m);
        struct move_t move={-1,-1,-1};
        for(int i=0;i<40;i++){
        move=play2(move);
        if(move.queen_dst==-2){
            printf("game finished2\n");
            break;
        }
    
        
        execute_move(move,graph,queens[1]);
        printf("player2\n");
        display(graph,queens,m);
        move=play1(move);
         if(move.queen_dst==-2){
            printf("%d game finished1 \n",move.queen_dst);
            break;
        }
         execute_move(move,graph,queens[0]);
        // printf("%d\n",move.arrow_dst);

        //  printf("%d\n",move.queen_src);

        //  printf("%d\n",move.queen_dst);
        printf("player1\n");
        display(graph,queens,m);
        }
        //}

        dlclose(handle1);
        dlclose(handle2);
    return 0;
}










