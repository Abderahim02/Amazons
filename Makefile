#GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
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
BIN = test_grid test

player2.o: src/player2.c
	gcc -c -fPIC $<
player1.o: src/player1.c
	gcc -c -fPIC $<
libplayer2.so: player2.o
	gcc -shared $< -o $@
libplayer1.so: player1.o
	gcc -shared $< -o $@

grid.o:	src/grid.c  src/graph.h 
	gcc $(CFLAGS) -c src/grid.c


#gcc -L/usr/local/lib grid.o -o grid -lgsl -lgslcblas -lm
grid: src/grid.c 
	gcc -L$(GSL_PATH)/lib src/grid.c -o grid -lgsl -lgslcblas -lm
all: build

build: server client install test
server.o: src/server.c src/player.h
	gcc $(CFLAGS) -c src/server.c
	
server: src/server.o  src/grid.o src/player.h libplayer1.so libplayer2.so
	gcc -L$(GSL_PATH)/lib src/server.o src/grid.o  -lgsl -lgslcblas -lm -ldl -o $@
#	gcc -o executable fichier1.c fichier2.c fichier3.c ...  `gsl-config --cflags --libs`

client: 

alltests: 

test: tst/test_grid.o grid.o 
	gcc $(CFLAGS) $^ -o $@ $(LDFLAGS) 

alltests: 

grid.o: src/grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst src/grid.c -c

test_grid.o: tst/test_grid.c src/grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst tst/test_grid.c -c


install: 
	cp libplayer1.so libplayer2.so ${PWD}/install
	cp server ${PWD}/install/server

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o install/server/* server install/*.so

.PHONY: client install test clean
