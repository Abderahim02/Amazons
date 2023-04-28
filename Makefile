GSL_PATH=/opt/gsl-2.6
LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
#GSL_PATH ?=/usr/local

BIN = server
CC = gcc
SRC = src
TST = tst
CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \	-Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)

TEST = test_arrows

export LD_LIBRARY_PATH=./

all: build
build: server client install test alltests


test:

test_arrows.o: ${TST}/test_arrows.c ${SRC}/grid.c
	${CC} $(CFLAGS) -c  ${TST}/test_arrows.c -ldl



player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<  

libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so


grid.o: ${SRC}/grid.c ${SRC}/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/grid.c
	#${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib --coverage -c ${SRC}/grid.c -lgcov

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC} $(CFLAGS) -c ${SRC}/hole.c

moteur.o: ${SRC}/moteur.c  ${SRC}/graph.h 
	${CC} $(CFLAGS) -fPIC -c ${SRC}/moteur.c

game_loop.o: ${TST}/game_loop.c  
	${CC} $(CFLAGS) -fPIC -c ${TST}/game_loop.c


server.o: ${SRC}/server.c ${SRC}/player.h ${SRC}/graph.h
	${CC} $(CFLAGS) -c ${SRC}/server.c -ldl

server: server.o  grid.o moteur.o #libplayer1.so libplayer2.so
	${CC} -L${GSL_PATH}/lib server.o grid.o moteur.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

client: 


alltests:  #${TST}/test_arrows.o grid.o
	#${CC} ${LDFLAGS} -L${GSL_PATH}/lib  ${TST}/test_arrows.o grid.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov


# test_grid.o: ${TST}/test_graph.c ${SRC}/grid.c ${SRC}/grid.h hole.o moteur.o server.o 
# 	${CC} $(CFLAGS) -I ${SRC} -I ${TST} ${TST}/test_grid.c -c

# test_execute_move.o: ${TST}/test_execute_move.c ${SRC}/grid.c ${SRC}/grid.h hole.o moteur.o server.o 
# 	${CC} $(CFLAGS) -I ${SRC} -I ${TST} ${TST}/test_execute_move.c moteur.o -c

install: server
	make server
	make libraries
	make alltests
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	cp *.so install
	make clean

clean:
	@rm -f *~ *.so *.o  ${TST}/*.o ${BIN} *~ */*~ ${SRC}/*.o server alltests ${TEST}

.PHONY: client install test clean
