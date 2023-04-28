CC=gcc
CFLAGS=-g
RM=rm -f

default: all

all: build

build: histogram.c
	$(CC) $(CFLAGS) -o histogram histogram.c

test: histogram
	./testing.sh

clean:
	$(RM) histogram
