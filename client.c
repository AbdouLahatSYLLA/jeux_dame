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

	//printf("%d",argc);
	 if (argc < 2)
	 {
		printf(" Usage %s adresse du joueur ou nom de domaine \n",argv[0]);
		exit(2);
	 }

	/* 1. Création d'une socket tcp ipv6 */
	uint8_t rapport[256];
	uint8_t recu[20];
  	rapport[0] = 1;
	int n = 1;
	/* Création de la sockaddr */
	/*Utilisation de getaddrinfo pour pouvour utiliser de l'ipv4/ipv6,
		chez le serveur on utilisera la famille d'adresse ipv6,
		car les adresse ipv4 seront mappées. */
		int stat;
		int sock ;
		struct addrinfo hints = { .ai_socktype = SOCK_STREAM,
															.ai_flags = AI_V4MAPPED,
															.ai_family = AF_INET6};

		struct addrinfo *cur;

	  if ((stat = getaddrinfo(argv[1], "49153", &hints, &cur)) != 0) {
	      printf("%s\n", gai_strerror(stat));
	      return 2;
	  }
	  while (cur != NULL)
	  {
		  sock = socket(cur->ai_family, SOCK_STREAM, 0);
			if (sock < 0) {
				cur = cur->ai_next;
				continue;
				}
		int cn = connect(sock, cur->ai_addr, cur->ai_addrlen);
		  if(cn == 0){
			  struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *) cur->ai_addr;
			  copier_ipv6(rapport,&n,ipv6->sin6_addr.s6_addr);
			  puts("Connexion reussie");
			  break;
		  }
		cur = cur->ai_next ;
	  }

	freeaddrinfo(cur);
		/* Tentative de connection */

	int pion_blancs,pion_noirs,test;
    jeu_t  jeu ;
	initialiser_jeu(&jeu);
	/* 4. Échange avec le serveur */
	/* 4.1 Construction de la requête INCP */
	
	while (jeu.en_cours)
	{
		printf("Coup n° %d \n",jeu.nb_coups);
		read(sock,deplacement,sizeof(deplacement));
		test = tester_coup(jeu,deplacement);
		if(test == 0) {
			write(sock,"INVALIDE",strlen("INVALIDE")+1);
			break;
		}
		appliquer_coup(&jeu,deplacement);
		printf("Coup n° %d \n",jeu.nb_coups);
		faire_dames(&jeu);
		afficher_jeu(jeu);
		jouer(&jeu,deplacement,rapport,&n,recu);
		faire_dames(&jeu);
		write(sock,deplacement,sizeof(deplacement));
		afficher_jeu(jeu);
		pion_noirs = compter_pions(NOIR,&jeu);
		pion_blancs = compter_pions (BLANC,&jeu);
		if(pion_blancs == 0 ){
			write(sock,"PERDU",strlen("PERDU")+1);
			jeu.en_cours = 0;
			break;
		}
		if(jeu.nb_coups == 100){
			write(sock,"EGALITE",strlen("EGALITE")+1);
			jeu.en_cours = 0;
			break;
		}
		afficher_jeu(jeu);
	}
	if(pion_noirs == 0){
      	printf("Victoire des blancs\n");
   		 }

   	else if(pion_blancs == 0){
    	  printf("Victoire des noirs\n");

   		 }

   	   else if(jeu.nb_coups == 100){
      	printf("Egalite\n");
    	}

	close(sock);
/*	for(n;n < 256;n++){
		rapport[n] = '\0';
	}
	printf("%d octets\n",n);
	for ( int i = 0; i < n; i++)
	{
		printf("%x ",rapport[i]);
	}*/
	putchar('\n');
	return 0;
}
