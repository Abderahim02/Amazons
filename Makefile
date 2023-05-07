GSL_PATH ?=/usr/local
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)


BIN = server
CC = gcc
SRC = src
TST = tst
INSTALL = install

CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -I$(GSL_PATH)/include -I${INSTALL} -I${SRC} 
LDFLAGS = -lm -lgsl -lgslcblas -ldl -lgcov\	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \	-Wl,--rpath=${GSL_PATH}/lib
TEST = test_get_neighbor test__moves

export LD_LIBRARY_PATH=./

all: build
build: server  libraries test 


graph.o: ${SRC}/graph.c ${SRC}/graph.h
	${CC} -Wall  -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/graph.c -lgcov

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC} -Wall -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/hole.c -lgcov 

moteur.o: ${SRC}/moteur.c ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/moteur.c -lgcov
player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<

server_functions.o: src/server_functions.c src/hole.h src/moteur.h src/server_functions.h
	${CC} $(CFLAGS) -I${SRC} -c  $<

server.o: ${SRC}/server.c  ${SRC}/player.h graph.o ${SRC}/hole.h
	${CC} $(CFLAGS) -c -I${SRC} $< -o $@ -ldl -lgcov


######################################################### Début tests ##########################################################

test_get_neighbor.o: ${TST}/test_get_neighbor.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_get_neighbor.c


test__moves.o: ${TST}/test__moves.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test__moves.c

test_execute_move.o: ${TST}/test_execute_move.c ${SRC}/server_functions.h src/hole.h
	${CC} -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -I ${SRC}  ${TST}/test_execute_move.c   -c


test.o: tst/test.c
	gcc -c tst/test.c
test: test.o test_execute_move.o test__moves.o test_get_neighbor.o  graph.o src/moteur.c hole.o src/server_functions.c
	${CC} -L${GSL_PATH}/lib -fprofile-arcs -ftest-coverage $^ -lgsl -lgslcblas -lm -ldl -o alltests -ldl

######################################################### Fin tests ###########################################################

######################################################### Début fichiers objets #################################################



######################################################### Fin fichiers objets #######################################################

######################################################### Début libraries ##########################################################

libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so

######################################################### Fin libraries #########################################################


######################################################### Début Server ###########################################################

server: server.o  server_functions.o graph.o moteur.o hole.o 
	${CC} -L${GSL_PATH}/lib server.o  server_functions.o graph.o moteur.o hole.o  -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 

######################################################### Fin Server #############################################################



######################################################### Début Alltests ########################################################


######################################################### Fin Alltests ############################################################


install: server
	make server
	make libraries
#	make test
	if [ -f server ]; then cp server install/; fi
	if [ -f alltests ]; then cp alltests install/; fi
	cp *.so install
	make clean

clean:
	@rm -f *~ *.so *.o  ${TST}/*.o  tst/*.gcno ${BIN} *~ */*~ ${SRC}/*.o server alltests ${TEST}
	rm -f test_get_neighbor.o
	rm -f *.gcda

.PHONY: client install test clean
