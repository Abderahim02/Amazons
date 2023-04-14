LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?=/usr

#-L/usr/local/lib -lgsl -lgslcblas -lm

#L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I $(GSL_PATH)/include 
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
        -L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
        -Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)
BIN = test_grid test grid game_loop


all: build
build: server client install test


player2.o: src/player2.c
	gcc -c -fPIC $<
player1.o: src/player1.c
	gcc -c -fPIC $<
libplayer2.so: player2.o moteur.o
	gcc -shared player2.o moteur.o -o $@
libplayer1.so: player1.o moteur.o
	gcc -shared player1.o moteur.o -o $@

grid.o: src/grid.c src/grid.h
	gcc -Wall -I/usr/local/include -c src/grid.c
hole.o: src/hole.c  src/graph.h 
	gcc $(CFLAGS) -c src/hole.c


moteur.o: src/moteur.c  src/graph.h 
	gcc $(CFLAGS) -fPIC -c src/moteur.c


server.o: src/server.c src/server.h src/player.h src/graph.h
	gcc -Wall -I/usr/local/include -c src/server.c

# server: server.o  grid.o moteur.o libplayer1.so libplayer2.so
# 	gcc -L${GSL_PATH}/lib server.o grid.o moteur.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl

client: 

alltests: 

test: tst/test_graph.o grid.o  server.o  hole.o
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS) 

game_loop: tst/game_loop.o libplayer1.so libplayer2.so grid.o server.o
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS)


install: 
	# cp libplayer1.so libplayer2.so ${PWD}/install
	# cp server ${PWD}/install/server

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o install/server/* server install/*.so install/server

.PHONY: client install test clean
