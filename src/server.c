
#include <stdio.h>
#include <stdlib.h>

#include <gsl/gsl_spmatrix.h>
#include <gsl/gsl_spmatrix_uint.h>
#include <gsl/gsl_spblas.h>

#include "server.h"



struct player player_blanc;

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
    int *t=malloc(sizeof(int)*graph->num_vertices);
    t[0]=0;
    for(int i=0;i<N*N-1;i++){
        if(gsl_spmatrix_uint_get(graph->t, i, i+1)!=0 || (i+1)%N==0)
            t[i+1]=0;
        else t[i+1]=-1;
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
    int *t=graph_table(graph);
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










