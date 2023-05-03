GSL_PATH ?=/usr/local


BIN = server
CC = gcc
SRC = src
TST = tst
INSTALL = install

CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -I$(GSL_PATH)/include -I${INSTALL} -I${SRC}

LDFLAGS = -lm -lgsl -lgslcblas -ldl -lgcov\ -L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \ -Wl,--rpath=${GSL_PATH}/lib

export LD_LIBRARY_PATH=./

all: build
build: server install test libraries


######################################################### Début tests #####################################################################################
test: tst/* src/*
#	${CC} ${CFLAGS} -L${GSL_PATH}/lib -ftest-coverage -fprofile-arcs tst/test_graph.c tst/test_mechanism.c  tst/alltests.c src/mechanism.c src/graph.c src/color.c -lgsl -lgslcblas -lm -o alltests
	${CC} -L${GSL_PATH}/lib -I$(GSL_PATH)/include  -ftest-coverage -fprofile-arcs tst/test__moves.c tst/test_get_neighbor.c   src/graph.c src/moteur.c src/hole.c -lgsl -lgslcblas -lm -ldl -o alltests -ldl


######################################################### Fin tests #####################################################################################

######################################################### Début fichiers objets #####################################################################################

graph.o: ${SRC}/graph.c ${SRC}/graph.h
	${CC}  -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/graph.c 

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC}  -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/hole.c 

moteur.o: ${SRC}/moteur.c ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/moteur.c 

player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<  

server.o: ${SRC}/server.c ${SRC}/player.h ${SRC}/graph.h ${SRC}/hole.h
	${CC} $(CFLAGS) -c ${SRC}/server.c -ldl 


libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so



server: server.o  graph.o moteur.o hole.o 
	${CC} -L${GSL_PATH}/lib server.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 





#alltests:  ${TST}/test_execute_move.o graph.o  moteur.o hole.o
#	make server
#	${CC} -L${GSL_PATH}/lib  ${TST}/test_execute_move.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 


install: server
	make server
	make libraries
	make test
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	cp *.so install
	make clean

clean:
	@rm -f *~ *.so *.o  ${TST}/*.o  tst/*.gcno ${BIN} *~ */*~ ${SRC}/*.o server alltests ${TEST}

.PHONY: client install test clean
