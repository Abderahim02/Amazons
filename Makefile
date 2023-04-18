LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?=/usr/local

#-L/usr/local/lib -lgsl -lgslcblas -lm

#L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I $(GSL_PATH)/include 
LDFLAGS = -lm -lgsl -lgslcblas -ldl -L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 -Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)
BIN = test_grid test grid



all: build
build: server client install test alltests


player2.o: src/player2.c
	gcc -c -fPIC $<

player1.o: src/player1.c
	gcc -c -fPIC $<

libplayer2.so: player2.o moteur.o
	gcc -shared player2.o moteur.o -o $@ 

libplayer1.so: player1.o moteur.o
	gcc -shared player1.o moteur.o -o $@

grid.o: src/grid.c src/grid.h
	gcc -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c src/grid.c

hole.o: src/hole.c  src/graph.h 
	gcc $(CFLAGS) -c src/hole.c

moteur.o: src/moteur.c  src/graph.h 
	gcc $(CFLAGS) -fPIC -c src/moteur.c

game_loop.o: tst/game_loop.c  
	gcc $(CFLAGS) -fPIC -c tst/game_loop.c


server.o: src/server.c src/player.h src/graph.h
	gcc $(CFLAGS) -c src/server.c -ldl

server: server.o  grid.o moteur.o libplayer1.so libplayer2.so
	gcc -L${GSL_PATH}/lib server.o grid.o moteur.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

client: 


alltests: tst/test_graph.o grid.o tst/test_execute_move.o server.o moteur.o hole.o game_loop.o
	make server
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS) 



# test_grid.o: tst/test_graph.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	gcc $(CFLAGS) -I src -I tst tst/test_grid.c -c

# test_execute_move.o: tst/test_execute_move.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	gcc $(CFLAGS) -I src -I tst tst/test_execute_move.c moteur.o -c

install: server
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	make clean

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o server alltests

.PHONY: client install test clean
