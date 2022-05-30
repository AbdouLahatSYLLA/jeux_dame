all:  serveur client

dames.o: dames.c dames.h
	gcc -c dames.c

reseau.o: reseau.c reseau.h
	gcc -c reseau.c

serveur.o :serveur.c reseau.h dames.h
	gcc -c serveur.c

client.o : client.c reseau.h dames.h
	gcc -c client.c

serveur : serveur.o dames.o reseau.o
	gcc -o serveur serveur.o reseau.o dames.o  -lm -Wall -pedantic -pthread

client : client.o dames.o reseau.o
	gcc -o client client.o reseau.o dames.o  -lm -Wall -pedantic

clean:
	rm -f *.o main
