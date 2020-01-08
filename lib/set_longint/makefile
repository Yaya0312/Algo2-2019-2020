CC = gcc
list = ../list/
CFLAGS = -std=c11 -g -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -I$(list)
LDFLAGS =
VPATH = $(list)
objects =  main.o set_longint.o $(list)list.o
executable = set_longint

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

main.o: main.c set_longint.h
list.o: list.h
set_longint.o: set_longint.h list.h
