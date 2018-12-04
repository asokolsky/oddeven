CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall
#LDFLAGS=-g -L/home/newhall/lib  -L../lib
LDFLAGS=-g
#LDLIBS=-lmylib -lm
LDLIBS=

SRCS=condition_parser.cpp condition_parser_test.cpp database.cpp date.cpp node.cpp main.cpp token.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main

main: $(OBJS)
	$(CXX) $(LDFLAGS) -o main $(OBJS) $(LDLIBS)

depend: .depend

.depend: $(SRCS)
	$(RM) ./.depend
	$(CXX) $(CPPFLAGS) -MM $^>>./.depend;

clean:
	$(RM) $(OBJS) main

distclean: clean
	$(RM) tool /.depend

include .depend
