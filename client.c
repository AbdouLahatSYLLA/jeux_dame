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

#define PORT_INCP 1234

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
    uint32_t enc,nbc,tour;
    read(sock,&enc,sizeof(uint32_t));
    read(sock,&tour,sizeof(uint32_t));
    read(sock,&nbc,sizeof(uint32_t));
	recevoir_cases(&jeu,sock);
    afficher_jeu(jeu);
	close(sock);
	return 0;
}
