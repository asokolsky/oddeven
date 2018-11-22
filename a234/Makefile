CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g $(shell root-config --cflags)
LDFLAGS=-g $(shell root-config --ldflags)
LDLIBS=$(shell root-config --libs)

SRCS=bus_manager.cpp main.cpp query.cpp responses.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
    $(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS) 

bus_manager.o: bus_manager.cpp bus_manager.h

main.o: query.h responses.h bus_manager.h

query.o: query.cpp query.h

responses.o: responses.cpp responses.h

clean:
    $(RM) $(OBJS)

distclean: clean
    $(RM) tool
