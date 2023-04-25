LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
#GSL_PATH ?=/usr/local
CC = gcc

# CFLAGS = -Wall -Wextra -std=c99 -g3 -I ${GSL_PATH}/include 
# LDFLAGS = #-lm -lgsl -lgslcblas -ldl -L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 -Wl,--rpath=${GSL_PATH}/lib
GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \	
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)
BIN = server
TEST = test_arrows

export LD_LIBRARY_PATH=./

all: build
build: server client install test alltests


test:

test_arrows.o: tst/test_arrows.c src/grid.c
	${CC} $(CFLAGS) -c tst/test_arrows.c -ldl

test_arrows: tst/test_arrows.o grid.o
	make server
	${CC} -L${GSL_PATH}/lib tst/test_arrows.o grid.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 


player2.o: src/player2.c
	${CC} -c -fPIC $<

player1.o: src/player1.c
	${CC} -c -fPIC $<

libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so
	


grid.o: src/grid.c src/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c src/grid.c

hole.o: src/hole.c  src/graph.h 
	${CC} $(CFLAGS) -c src/hole.c

moteur.o: src/moteur.c  src/graph.h 
	${CC} $(CFLAGS) -fPIC -c src/moteur.c

game_loop.o: tst/game_loop.c  
	${CC} $(CFLAGS) -fPIC -c tst/game_loop.c


server.o: src/server.c src/player.h src/graph.h
	${CC} $(CFLAGS) -c src/server.c -ldl

server: server.o  grid.o moteur.o #libplayer1.so libplayer2.so
	${CC} -L${GSL_PATH}/lib server.o grid.o moteur.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

client: 


alltests:  


# test_grid.o: tst/test_graph.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	${CC} $(CFLAGS) -I src -I tst tst/test_grid.c -c

# test_execute_move.o: tst/test_execute_move.c src/grid.c src/grid.h hole.o moteur.o server.o 
# 	${CC} $(CFLAGS) -I src -I tst tst/test_execute_move.c moteur.o -c

install: server
	make server
	make libraries
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	cp *.so install
	make clean

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o server alltests ${TEST}

.PHONY: client install test clean
