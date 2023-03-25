#GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
LENGHT ?= 8
AMAZONS_FLAGS = -DLENGHT=$(LENGHT)
GSL_PATH ?= L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include 
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)

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

server: src/serveur.c libplayer1.so libplayer2.so
	gcc src/serveur.c -L. -lplayer2 -ldl -o $@
#	gcc -o executable fichier1.c fichier2.c fichier3.c ...  `gsl-config --cflags --libs`

client: #$(OBJS)

alltests: test.o $(OBJS)
	gcc $(CFLAGS) $^  -o alltests

test: alltests
	@echo "-- run tests:"
	@for e in ${BIN}; do \
	echo -n "-- $${e} -> "; ./$${e}; \
	done

test_grid.o: tst/test_grid.c src/grid.h
	gcc $(CFLAGS) -I src -I tst tst/test_grid.c -c

test_grid: test_grid.o 
	gcc test_grid.o -o $@ ${LDFLAGS}

install: server client test

clean:
	@rm -f *~ *.so *.o src/*~

.PHONY: client install test clean
