CC = gcc
list = ../list
CFLAGS = -std=c11 -g -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -I$(list)  -DHOLDALL_INSERT_TAIL
LDFLAGS =
VPATH = $(list)
objects =  main.o mset_longint.o $(list)list.o
executable = mset_longint

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c mset_longint.h
list.o: list.c list.h
mset_longint.o: mset_longint.h list.h
