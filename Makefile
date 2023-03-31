# GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
GSL_PATH ?= -L/usr/lib/x86_64-linux-gnu
#GSL_PATH ?= -L/usr/include/gsl
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

grid.o:	src/grid.c
	gcc $(CFLAGS) src/grid.c

grid: src/grid.c 
	gcc $(CFLAGS) src/grid.c -o grid
all: build

build: server client

server: src/serveur.c libplayer1.so libplayer2.so
	gcc src/serveur.c -L. -lplayer2 -ldl -o $@

client: $(OBJS)
	$(CFLAGS) 
alltests: test.o $(OBJS)
	gcc $(CFLAGS) $^  -o alltests

test: alltests

install: server client test

clean:
	@rm -f *~ *.so *.o src/*~

.PHONY: client install test clean
