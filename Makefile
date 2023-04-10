GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?=/usr/local

#-L/usr/local/lib -lgsl -lgslcblas -lm

#L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include 
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
        -L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
        -Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)
BIN = test_grid test grid


all: build
build: server client install test


player2.o: src/player2.c
	gcc -c -fPIC $<
player1.o: src/player1.c
	gcc -c -fPIC $<
libplayer2.so: player2.o
	gcc -shared $< -o $@
libplayer1.so: player1.o
	gcc -shared $< -o $@


hole.o: src/hole.c  src/graph.h 
	gcc $(CFLAGS) -c src/hole.c


moteur.o: src/moteur.c  src/graph.h 
	gcc $(CFLAGS) -c src/moteur.c


server.o: src/server.c src/player.h
	gcc $(CFLAGS) -c src/server.c

server: src/server.o  src/grid.o src/player.h src/hole.o src/moteur.o libplayer1.so libplayer2.so
	gcc -L$(GSL_PATH)/lib src/server.o src/grid.o src/hole.o src/moteur.o  -lgsl -lgslcblas -lm -ldl -o $@

client: 

alltests: 

test: tst/test_graph.o grid.o tst/test_execute_move.o server.o moteur.o hole.o
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS) 

alltests: 

grid.o: src/grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst src/grid.c -c

# test_grid.o: tst/test_graph.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	gcc $(CFLAGS) -I src -I tst tst/test_grid.c -c

# test_execute_move.o: tst/test_execute_move.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	gcc $(CFLAGS) -I src -I tst tst/test_execute_move.c moteur.o -c

install: 
	cp libplayer1.so libplayer2.so ${PWD}/install
	cp server ${PWD}/install/server

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o install/server/* server install/*.so install/server

.PHONY: client install test clean