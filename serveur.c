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

#define PORT_INCP 7777
sem_t attaquant;
sem_t defense;
char deplacement[100];
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
	sem_init(&defense,0,0);
	sem_init(&attaquant,0,1);

	/* 5. Attente passive d'une connection. */
	int sock_echange = accept(sock, NULL, NULL);
     jeu_t * jeu = malloc(sizeof(jeu_t));
    initialiser_jeu(jeu);
	jeu->tour = BLANC;

    client * att = malloc(sizeof(client));
    att->jeu = jeu;
    att->sock = sock_echange;
    pthread_create(&th,NULL,joueur2,att);
	while (jeu->en_cours)
	{
		afficher_jeu(*jeu);
		sem_wait(&attaquant);
		jouer(jeu,deplacement);
		jeu->nb_coups++;
	    jeu->tour = jeu->nb_coups % 2 == 0 ? BLANC : NOIR;
		envoyer_jeu(jeu,sock_echange);
		sem_post(&defense);

	}

	pthread_join(th,NULL);

	close(sock_echange);
	close(sock);
    
	return 0;
}
void * joueur2(void * arg){
	client * clt = arg;
	while (clt->jeu->en_cours)
	{
		sem_wait(&defense);
		recevoir_jeu(clt->jeu,clt->sock);
		clt->jeu->nb_coups++;
	    clt->jeu->tour = clt->jeu->nb_coups % 2 == 0 ? BLANC : NOIR;
		afficher_jeu(*clt->jeu);
		sem_post(&attaquant);	

	
	
	}
	
      
	return NULL;
}


  

