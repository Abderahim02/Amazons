LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?=/usr/local

#-L/usr/local/lib -lgsl -lgslcblas -lm

#L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I $(GSL_PATH)/include 
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

grid.o: src/grid.c src/grid.h
	gcc -Wall -I/usr/local/include -c src/grid.c
hole.o: src/hole.c  src/graph.h 
	gcc $(CFLAGS) -c src/hole.c


moteur.o: src/moteur.c  src/graph.h 
	gcc $(CFLAGS) -c src/moteur.c


server.o: src/server.c src/player.h src/graph.h
	gcc $(CFLAGS) -c src/server.c -ldl

server: server.o  grid.o  libplayer1.so libplayer2.so
	gcc -L${GSL_PATH}/lib server.o grid.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl
client: 

alltests: 

test: tst/test_graph.o grid.o 
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS) 

alltests: 


test_grid.o: tst/test_raph.c src/grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst tst/test_grid.c -c

test_execute_move.o: tst/test_execute_move.c src/grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst tst/test_execute_move.c -c

install: 
	cp libplayer1.so libplayer2.so ${PWD}/install
	cp server ${PWD}/install/server

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o install/server/* server install/*.so install/server

.PHONY: client install test clean
