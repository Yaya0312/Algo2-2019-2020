hashtabledir = lib/hashtable/
holdalldir = lib/holdall/
read_words = lib/read_words/
set_longint = lib/set_longint/
setb = lib/setb/
list = lib/list/
CC = gcc
CFLAGS = -std=c11 -g -Wall -Wconversion -Werror -Wextra -Wpedantic -Wwrite-strings -O2 -I$(hashtabledir) -I$(holdalldir) -I$(read_words) -I$(set_longint) -I$(setb) -I$(list) -DHOLDALL_INSERT_TAIL
LDFLAGS = 
VPATH = $(hashtabledir):$(holdalldir):$(read_words)
objects = $(hashtabledir)hashtable.o $(holdalldir)holdall.o $(read_words)read_words.o $(set_longint)set_longint.o $(setb)setb.o $(list)list.o main.o lidx.o option.o
executable = lidx

all: $(executable)

clean:
	$(RM) $(objects) $(executable)

$(executable): $(objects)
	$(CC) $(objects) $(LDFLAGS) -o $(executable)

tar: clean
	tar -zcf "$Pop.tar.gz" **

hashtable.o: hashtable.c hashtable.h
holdall.o: holdall.c holdall.h
read_words.o : read_words.c read_words.h
main.o: main.c lidx.h option.h holdall.h
lidx.o: holdall.h  hashtable.h lidx.h option.h
set_longint.o : set_longint.h holdall.h
setb.o: setb.h holdall.h
list.o: list.h
option.o : option.h
