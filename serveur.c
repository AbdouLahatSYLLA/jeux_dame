/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dames.h"
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */
#include <pthread.h>
#include <semaphore.h>
#include "reseau.h"
typedef struct{
    jeu_t *jeu;
    int sock;
}client;

#define PORT_INCP 1234
sem_t attaquant;
sem_t defense;
char deplacement[100];
int numero1, numero2;
void * joueur2(void * arg);  
int main()
{
    pthread_t th;
	/* 1. Création d'une socket tcp ipv4 */
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}

	/* 2. Création de la sockaddr */
	struct sockaddr_in sa = { .sin_family = AF_INET,
				  .sin_port = htons(PORT_INCP),
				  .sin_addr.s_addr = htonl(INADDR_ANY) };
	/* Optionnel : faire en sorte de pouvoir réutiliser l'adresse sans
	 * attendre après la fin du serveur. */
	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));

	/* 3. Attacher la socket d'écoute à l'adresse */
	if (bind(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
		perror("bind");
		exit(3);
	}

	/* 4. Écouter sur la socket d'écoute */
	if (listen(sock, 10) < 0) {
		perror("listen");
		exit(2);
	}

	/* 5. Attente passive d'une connection. */
	int sock_echange = accept(sock, NULL, NULL);
     jeu_t * jeu = malloc(sizeof(jeu_t));
    initialiser_jeu(jeu);
    client * att = malloc(sizeof(client));
    att->jeu= jeu;
    att->sock = sock;
    uint32_t enc,tour,nbc;
      enc = (uint32_t) jeu->en_cours;
      tour = 1;
      nbc = (uint32_t) jeu->nb_coups; 
      write(sock_echange,&enc,sizeof(uint32_t));
      write(sock_echange,&tour,sizeof(uint32_t));
      write(sock_echange,&nbc,sizeof(uint32_t));
      envoyer_cases(jeu,sock_echange);

	close(sock_echange);
	close(sock);
    
	return 0;
}

  

