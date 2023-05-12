#include<stdio.h>


#include "../src/graph.h"
#include "../src/move.h"
#include "../src/moteur.h"
#include "../src/server_functions.h"

extern struct graph_t * initialize_graph(unsigned int length);
extern void free_graph(struct graph_t* g);
extern void make_graph(struct graph_t * g, unsigned int m ,char s );
extern void free_graph(struct graph_t* g);
extern void initialize_graph_positions_classic(struct graph_t* g);
void  make_hole(struct graph_t *g, int id, int size);
extern void test_inside_position();

extern void print__array(int* t);
extern void test__available_dst();
extern void test__put_arrow();
extern void test__begining_position_size_5();
extern void test__begining_position_size_8();
extern void test__begining_position_size_9();
extern void test__begining_position_size_12();
extern void test__begining_position_size_15();
extern void test__execute_move();
extern void test_make_hole();
extern void test_make_i_j();
extern void test_initialize_graph_positions_classic();
extern void test__get_neighbor_gen();
extern void test_graph_table(void);
extern void test_table(void);
extern void start_next(void);
extern void test_copy_queens(void);
extern void test_begining_position();
extern void test_get_neighbor_queens();
extern void test_display();
extern void test_dir_in_board();
extern void test_all_opening();
int main(){
    test__available_dst();
    test__put_arrow();
    test__begining_position_size_5();
    test__begining_position_size_8();
    test__begining_position_size_9();
    test__begining_position_size_12();
    test__execute_move();
    test_make_hole();
    test_make_i_j();
    test_initialize_graph_positions_classic();
    test__get_neighbor_gen();
    test_graph_table();
    test_table();
    start_next();
    test_copy_queens();
    test_begining_position();
    test_get_neighbor_queens();
    test_inside_position();
    test_display();
    test_dir_in_board();
    test_all_opening();
    printf("OK all__tests\n");

}





