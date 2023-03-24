#GSL_PATH ?= /net/ens/renault/save/gsl-2.6/install
GSL_PATH ?= L/usr/lib/x86_64-linux-gnu
CFLAGS = -std=c99 -Wall -Wextra -fPIC -g3 -I$(GSL_PATH)/include
LDFLAGS = -lm -lgsl -lgslcblas -ldl \
	-L$(GSL_PATH)/lib -L$(GSL_PATH)/lib64 \
	-Wl,--rpath=${GSL_PATH}/lib
OBJS = $(SRCS:.c=.o)

all: build

build: server client

server: 
#	gcc -o executable fichier1.c fichier2.c fichier3.c ...  `gsl-config --cflags --libs`

client: $(OBJS)
	$(CFLAGS) 
alltests: test.o $(OBJS)
	gcc $(CFLAGS) $^  -o alltests

test: alltests

install: server client test

clean:
	@rm -f *~ src/*~

.PHONY: client install test clean
