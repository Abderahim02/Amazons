#GSL_PATH=/opt/gsl-2.6
# LENGHT ?= 8
LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?=/usr/local

BIN = server
CC = gcc
SRC = src
TST = tst
INSTALL = install
CFLAGS = -std=c99 -Wall -lm -Wextra -fPIC -g3 -I$(GSL_PATH)/include -I${INSTALL} -I${SRC} 
LDFLAGS = -lm -lgsl -lgslcblas -ldl -lgcov\	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \	-Wl,--rpath=${GSL_PATH}/lib
# OBJS = $(SRCS:.c=.o)

CFLAGS += -fprofile-arcs -ftest-coverage 
# LDFLAGS += -fprofile-arcs -ftest-coverage 


TEST = test_get_neighbor test__moves

export LD_LIBRARY_PATH=./

all: build
build: server client install test alltests libraries


test:

test_get_neighbor.o: ${TST}/test_get_neighbor.c ${SRC}/grid.c ${SRC}/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test_get_neighbor.c

test_get_neighbor: test_get_neighbor.o grid.o moteur.o hole.o 
	${CC} -fprofile-arcs -ftest-coverage -L${GSL_PATH}/lib test_get_neighbor.o grid.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

test__moves.o: ${TST}/test__moves.c ${SRC}/grid.c ${SRC}/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${TST}/test__moves.c

test__moves: test__moves.o grid.o moteur.o hole.o 
	${CC} -L${GSL_PATH}/lib test__moves.o grid.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl 

# test_get_neighbor.gcno: ${TST}/test_get_neighbor.c ${SRC}/grid.c ${SRC}/grid.h
# 	${CC} ${CFLAGS} -c ${TST}/test_get_neighbor.c -o $@

# test_get_neighbor.gcda: test_get_neighbor
# 	./test_get_neighbor

# test_get_neighbor_coverage: test_get_neighbor.gcno test_get_neighbor.gcda
# 	${CC} ${CFLAGS} -fprofile-arcs -ftest-coverage ${TST}/test_get_neighbor.c ${SRC}/grid.c -o test_get_neighbor
# 	./test_get_neighbor
# 	gcov ${TST}/test_get_neighbor.c

grid.o: ${SRC}/grid.c ${SRC}/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/grid.c -lgcov
	#${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib --coverage -c ${SRC}/grid.c -lgcov

hole.o: ${SRC}/hole.c  ${SRC}/graph.h 
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/hole.c -lgcov

moteur.o: ${SRC}/moteur.c ${SRC}/grid.h
	${CC} -Wall -I$(GSL_PATH)/include -L$(GSL_PATH)/lib -c ${SRC}/moteur.c -lgcov
	


player2.o:  ${SRC}/player2.c 
	${CC} $(CFLAGS) -I${SRC} -c  $< 

player1.o: ${SRC}/player1.c 
	${CC} $(CFLAGS) -I${SRC} -c  $<  

libraries:player1.o player2.o moteur.o
	${CC} -shared player2.o moteur.o -o libplayer2.so
	${CC} -shared player1.o moteur.o -o libplayer1.so


server.o: ${SRC}/server.c ${SRC}/player.h ${SRC}/graph.h
	${CC} $(CFLAGS) -c ${SRC}/server.c -ldl -lgcov 

server: server.o  grid.o moteur.o hole.o  #libplayer1.so libplayer2.so
	${CC} -L${GSL_PATH}/lib server.o grid.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 

client: 

test_execute_move.o: ${TST}/test_execute_move.c hole.o 
	${CC} $(CFLAGS) -I ${SRC} -I ${TST} ${TST}/test_execute_move.c  -c 


############################# NE PAS MODIFIER ####################

# OBJ = .

# # Liste des fichiers sources à compiler
# SRCS = $(wildcard $(SRC)/*.c)
# # Liste des fichiers objets à générer
# OBJS = $(patsubst $(SRC)/%.c,$(OBJ)/%.o,$(SRCS))
# # Compilation des fichiers objets
# $(OBJ)/%.o: $(SRC)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Compilation des tests
# $(TST)/%.o: $(TST)/%.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# # Cible pour l'exécutable alltests
# alltests: $(TST)/test_execute_move.o $(OBJS)
# 	$(CC) -L${GSL_PATH}/lib -lgsl -lgslcblas -lm -ldl  $^ -o $@ -ldl -lgcov
# # # Cible pour exécuter tous les tests
# # test: alltests
# # 	./$<




# alltests:  ${TST}/test_execute_move.o grid.o hole.o moteur.o
# 	make server
# 	${CC} -L${GSL_PATH}/lib  ${TST}/test_execute_move.o grid.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov

########################  FIN NE PAS MODIFIER ####################

alltests:  ${TST}/test_execute_move.o grid.o hole.o moteur.o
	make server
	${CC} -L${GSL_PATH}/lib  ${TST}/test_execute_move.o grid.o moteur.o hole.o -lgsl -lgslcblas -lm -ldl -o $@ -ldl -lgcov 

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
	rm -f *.gcno
	rm -f *.gcda

.PHONY: client install test clean
