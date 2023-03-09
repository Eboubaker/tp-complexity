CC          = gcc
CFLAGS      = -g -ggdb3 -Wall -Werror=implicit-function-declaration -I./


tp all: main.o algorithms.o util.o
	$(CC) $(CFLAGS) main.o algorithms.o util.o -o tp
run: tp
	./tp
main.o: main.c
	$(CC) $(CFLAGS) -c main.c

algorithms.o: algorithms.c algorithms.h
	$(CC) $(CFLAGS) -c algorithms.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean veryclean:
	rm -f tp *.o tp.exe
