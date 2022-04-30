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
#include "reseau.h"
#include "dames.h"

#define PORT_INCP 7777
char deplacement[100];
int main(int argc, char *argv[])
{

	/* 1. Création d'une socket tcp ipv4 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}

	/* 2. Création de la sockaddr */
	struct sockaddr_in sa = { .sin_family = AF_INET, .sin_port = htons(PORT_INCP) };
	if (inet_pton(AF_INET, argv[1], &sa.sin_addr) != 1) {
		fprintf(stderr, "adresse ipv4 non valable\n");
		exit(1);
	}

	/* 3. Tentative de connection */
	if (connect(sock, (struct sockaddr *) &sa, sizeof(struct sockaddr_in)) < 0) {
		perror("connect");
		exit(3);
	}
    jeu_t  jeu ;

	/* 4. Échange avec le serveur */
	/* 4.1 Construction de la requête INCP */
    
	while (jeu.en_cours)
	{
		recevoir_jeu(&jeu,sock);
		afficher_jeu(jeu);
		printf("%d \n",jeu.en_cours);
		jouer(&jeu,deplacement);
		afficher_jeu(jeu);
		envoyer_jeu(&jeu,sock);
	}
	
	close(sock);
	return 0;
}
