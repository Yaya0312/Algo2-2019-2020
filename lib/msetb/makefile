CC = gcc
holdalldir = ../holdall/
CFLAGS = -std=c11 -g -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -I$(holdalldir)  -DHOLDALL_INSERT_TAIL
LDFLAGS =
VPATH = $(holdalldir)
objects =  main.o msetb.o $(holdalldir)holdall.o
executable = msetb

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c msetb.h
holdall.o: holdall.c holdall.h
msetb.o: msetb.h holdall.h