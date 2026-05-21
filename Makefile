flags=-02 -Wall
ldflags=-lbu

SRC = src/ping.c
INCLUDE = include/ping.h

.PHONY: all clean

all: clean ping

ping: ping.o
	cc $(flags) $^ -o $@ $(ldflags)

ping.o: $(SRC) $(INCLUDE)
	cc  $(flags) -c $<

clean: 
	rm -f 