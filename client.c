/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */
#include <time.h>
#include <ctype.h>
#include <netdb.h>
#include "reseau.h"
#include "dames.h"

#define PORT_INCP 49153

char deplacement[100];

int main(int argc, char *argv[])
{

	struct addrinfo *res;
	printf("%d",argc);
	 if (argc < 2)
	 {
		printf(" Usage %s adresse du joueur ou nom de domaine \n",argv[0]);
		exit(2);
	 }

	/* 1. Création d'une socket tcp ipv6 */
	int sock = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}

	/* Création de la sockaddr */
	/*Utilisation de getaddrinfo pour pouvour utiliser de l'ipv4/ipv6,
		chez le serveur on utilisera la famille d'adresse ipv6,
		car les adresse ipv4 seront mappées. */
		int stat;
		struct addrinfo hints = { .ai_socktype = SOCK_STREAM,
															.ai_flags = AI_V4MAPPED,
															.ai_family = AF_INET6};

		struct addrinfo *cur;

	  if ((stat = getaddrinfo(argv[1], "49153", &hints, &cur)) != 0) {
	      printf("%s\n", gai_strerror(stat));
	      return 2;
	  }

		/* Tentative de connection */
		if (connect(sock, cur->ai_addr, cur->ai_addrlen) < 0) {
			perror("connect");
			exit(3);
		}

    jeu_t  jeu ;
		jeu.en_cours = 1;
	/* 4. Échange avec le serveur */
	/* 4.1 Construction de la requête INCP */

	while (jeu.en_cours)
	{
		recevoir_jeu(&jeu,sock);
		afficher_jeu(jeu);
		jouer(&jeu,deplacement);
		afficher_jeu(jeu);
		envoyer_jeu(&jeu,sock);
	}

	close(sock);
	return 0;
}
