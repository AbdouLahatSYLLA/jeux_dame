all: main

dames.o: dames.c dames.h
	gcc -c dames.c

main: main.o dames.o
	gcc -o main main.o dames.o -lm -Wall -pedantic

clean:
	rm -f *.o main
