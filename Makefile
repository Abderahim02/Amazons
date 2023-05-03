GSL_PATH ?=/usr/local
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)


BIN = server
CC = gcc
SRC = src
TST = tst
INSTALL = install

CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -I$(GSL_PATH)/include -I${INSTALL} -I${SRC} #--coverage
LDFLAGS = -lm -lgsl -lgslcblas -ldl -lgcov\	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \	-Wl,--rpath=${GSL_PATH}/lib
TEST = test_get_neighbor test__moves

export LD_LIBRARY_PATH=./

all: build
build: server install alltests libraries


######################################################### Début tests #####################################################################################
test: test_get_neighbor 

test_get_neighbor.o: ${TST}/test_get_neighbor.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_get_neighbor.c

test_get_neighbor: test_get_neighbor.o graph.o moteur.o hole.o 
	${CC} -fprofile-arcs -ftest-coverage -L${GSL_PATH}/lib test_get_neighbor.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

test__moves.o: ${TST}/test__moves.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test__moves.c

test__moves: test__moves.o graph.o moteur.o hole.o 
	${CC} -L${GSL_PATH}/lib test__moves.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

test_execute_move.o: ${TST}/test_execute_move.c hole.o 
	${CC} $(CFLAGS) -I ${SRC} -I ${TST} ${TST}/test_execute_move.c  -c 

######################################################### Fin tests #####################################################################################

######################################################### Début fichiers objets #####################################################################################

graph.o: ${SRC}/graph.c ${SRC}/graph.h
	${CC} -Wall  -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/graph.c -lgcov
	#${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/graph.c -lgcov

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC} -Wall -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/hole.c -lgcov 

moteur.o: ${SRC}/moteur.c ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/moteur.c -lgcov
	
player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<  

server.o: ${SRC}/server.c ${SRC}/player.h ${SRC}/graph.h ${SRC}/hole.h
	${CC} $(CFLAGS) -c ${SRC}/server.c -ldl -lgcov 

######################################################### Fin fichiers objets #####################################################################################

######################################################### Début libraries #####################################################################################

libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so

######################################################### Fin libraries #####################################################################################


######################################################### Début Server #####################################################################################

server: server.o  graph.o moteur.o hole.o  #libplayer1.so libplayer2.so
	${CC} -L${GSL_PATH}/lib server.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 

######################################################### Fin Server #####################################################################################



######################################################### Début Alltests #####################################################################################


alltests:  ${TST}/test_execute_move.o graph.o  moteur.o hole.o
	make server
	${CC} -L${GSL_PATH}/lib  ${TST}/test_execute_move.o graph.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 

######################################################### Fin Alltests #####################################################################################


install: server
	make server
	make libraries
	make alltests
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	cp *.so install
	make clean

clean:
	@rm -f *~ *.so *.o  ${TST}/*.o  tst/*.gcno ${BIN} *~ */*~ ${SRC}/*.o server alltests ${TEST}
	rm -f test_get_neighbor.o
#	rm -f *.gcno
#	rm -f *.gcda

.PHONY: client install test clean
