CC=gcc
CXX=g++
RM=rm -f
CPPFLAGS=-g -Wall
#LDFLAGS=-g -L/home/newhall/lib  -L../lib
LDFLAGS=-g
#LDLIBS=-lmylib -lm
LDLIBS=

SRCS=condition_parser.cpp database.cpp date.cpp node.cpp token.cpp
OBJS=$(subst .cpp,.o,$(SRCS))

all: main condition_parser_test

main: main.o $(OBJS)
	$(CXX) $(LDFLAGS) -o main main.o $(OBJS) $(LDLIBS)

condition_parser_test: condition_parser_test.o $(OBJS)
	$(CXX) $(LDFLAGS) -o condition_parser_test condition_parser_test.o $(OBJS) $(LDLIBS)


main.o: main.cpp database.h date.h condition_parser.h node.h test_runner.h

condition_parser_test.o: condition_parser_test.cpp condition_parser.h test_runner.h node.h

condition_parser.o: condition_parser.cpp condition_parser.h token.h node.h

database.o: database.cpp database.h

date.o: date.cpp date.h

node.o: node.cpp node.h

token.o: token.cpp token.h

clean:
	$(RM) $(OBJS)

distclean: clean
	$(RM) tool
