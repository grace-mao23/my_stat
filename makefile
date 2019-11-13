ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: stat.o
	$(CC) -o program stat.o

stat.o: stat.c
	$(CC) -c stat.c

run:
	./program

clean:
	rm *.o
	rm *.exe

memcheck:
	valgrind --leak-check=yes ./program
