CC=gcc
CFLAGS=-Wall

SRCS=$(wildcard *.c)
OBJS=$(SRCS:.c=.o)
EXEC=daemon

all: $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@

clear:
	rm -f $(OBJS) $(EXEC)

run:
	./daemon

find:
	ps -eo 'tty,pid,comm' | grep ^?
