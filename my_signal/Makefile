CC = gcc
CFLAGS = -Wall -g
LDFLAGS = -lpthread

.PHONY : clean

my_signal : my_signal.o
	$(CC) -o my_signal my_signal.o $(LDFLAGS)

my_signal.o : my_signal.c
	$(CC) -c my_signal.c -o my_signal.o $(CFLAGS)

clean :
	rm -f my_signal my_signal.o