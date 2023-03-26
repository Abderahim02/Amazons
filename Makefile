#GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?= L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include -Isrc
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


all: build

build: server client

server: src/server.c libplayer1.so libplayer2.so
	gcc src/server.c -L. -lplayer2 -ldl -o $@
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
	cp server  libplayer1.so libplayer2.so ./install

clean:
	@rm -f *~ *.so *.o  tst/*.o ${BIN} *~ */*~ src/*.o install/* server

.PHONY: client install test clean
