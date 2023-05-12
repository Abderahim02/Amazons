GSL_PATH ?=/usr/local
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)


BIN = server
CC = gcc
SRC = src
TST = tst
INSTALL = install

CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -g -I$(GSL_PATH)/include -I${INSTALL} -I${SRC} 
LDFLAGS = -lm -lgsl -lgslcblas -ldl -lgcov\	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \	-Wl,--rpath=${GSL_PATH}/lib
TEST = test_moteur test_hole test_graph test_server test_strategy3

export LD_LIBRARY_PATH=./

all: build
build: server  libraries test 


graph.o: ${SRC}/graph.c ${SRC}/graph.h
	${CC} -Wall  -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/graph.c -lgcov

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC} -Wall -ftest-coverage -fprofile-arcs -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/hole.c -lgcov 

moteur.o: ${SRC}/moteur.c ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/moteur.c -lgcov

strategyplayer3.o: ${SRC}/strategyplayer3.c ${SRC}/graph.h ${SRC}/strategyplayer3.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -c ${SRC}/strategyplayer3.c -lgcov

server_functions.o: src/server_functions.c src/hole.h src/moteur.h src/server_functions.h src/strategyplayer3.h
	${CC} $(CFLAGS) -I${SRC} -c  $<

server.o: ${SRC}/server.c  ${SRC}/player.h graph.o ${SRC}/hole.h
	${CC} $(CFLAGS) -c -I${SRC} $< -o $@ -ldl -lgcov



player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<

player3.o: ${SRC}/player3.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<


######################################################### Début tests ##########################################################

test_moteur.o: ${TST}/test_moteur.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_moteur.c


test_hole.o: ${TST}/test_hole.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_hole.c

test_graph.o: ${TST}/test_graph.c ${SRC}/server_functions.h ${SRC}/hole.h
	${CC} -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -I ${SRC}  ${TST}/test_graph.c   -c

test_strategy3.o: ${TST}/test_strategy3.c graph.o ${SRC}/graph.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_strategy3.c

test_server.o: ${TST}/test_server.c ${SRC}/server_functions.h
	${CC} -I$(GSL_PATH)/include -L$(GSL_PATH)/lib  -I ${SRC}  ${TST}/test_server.c   -c


test.o: ${TST}/test.c
	gcc -c -I$(GSL_PATH)/include tst/test.c
test: test.o test_graph.o test_hole.o strategyplayer3.o test_moteur.o  test_server.o test_strategy3.o graph.o src/moteur.c hole.o src/server_functions.c
	${CC} -L${GSL_PATH}/lib -I$(GSL_PATH)/include -fprofile-arcs -ftest-coverage $^ -lgsl -lgslcblas -lm -ldl -o alltests -ldl

######################################################### Fin tests ###########################################################

######################################################### Début fichiers objets #################################################



######################################################### Fin fichiers objets #######################################################

######################################################### Début libraries ##########################################################

libraries:player1.o player2.o moteur.o server_functions.o strategyplayer3.o player3.o
	${CC} -shared player3.o moteur.o  strategyplayer3.o -o libplayer3.so
	${CC} -shared player2.o moteur.o  -o libplayer2.so
	${CC} -shared player1.o moteur.o server_functions.o -o libplayer1.so

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
	rm -f test_moteur.o
	rm -f *.gcda

.PHONY: client install test clean
