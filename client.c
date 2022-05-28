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

#define PORT_INCP 7777

char deplacement[100];
char dep2[100];
int main(int argc, char *argv[])
{
	char mauvais_coup[] = "INVALIDE";
	char perdu[] = "PERDU";
	char egalite[] = "EGALITE";
	char interruption[] = "INTERRUPTION";

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
		struct addrinfo hints = { .ai_flags = AI_V4MAPPED,.ai_family = AF_INET6,.ai_socktype = SOCK_STREAM};
		struct addrinfo *cur;
	  if ((stat = getaddrinfo(argv[1], "7777", &hints, &cur)) != 0) {
	      printf("%s\n", gai_strerror(stat));
	      return 2;
	  }
	  while (cur != NULL)
	  {
		  if(cur->ai_family == AF_INET6){
		  sock = socket(AF_INET6, SOCK_STREAM, 0);
			if (sock < 0) {
				cur = cur->ai_next;
				continue;
				}
		int cn = connect(sock, cur->ai_addr, cur->ai_addrlen);
		  if(cn == 0){
			 /* struct sockaddr_in6 * ipv6 = (struct sockaddr_in6 *) cur->ai_addr;
			  copier_ipv6(rapport,&n,ipv6->sin6_addr.s6_addr);*/
			  puts("Connexion reussie");
			  break;
		  }
	  }
	  		cur = cur->ai_next ;

	  }

	freeaddrinfo(cur);
		/* Tentative de connection */

	int pion_blancs,pion_noirs;
	/* 4. Échange avec le serveur */
	/* 4.1 Construction de la requête INCP */
	 jeu_t jeu;
	int x1,y1,x2,y2;
	 initialiser_jeu(&jeu);
	 int res;
	while (1)
	{
		recv(sock,deplacement,sizeof(deplacement),MSG_NOSIGNAL);
		printf("Recu %s \n",deplacement);
		strcpy(dep2,deplacement);
		res = verifier_coup(deplacement, &x1,&y1,&x2,&y2,jeu.tour,&jeu);
		faire_dames(&jeu);
		printf("Coup n° %d \n",jeu.nb_coups);
		afficher_jeu(jeu);
		jeu.tour = NOIR;
		jeu.nb_coups++;
		//Verifier si c'est deplacement ou une capture ou coup invalide
		//Appliquer deplacement sur notre jeu
		//Concat octets
		printf("Coup n° %d \n",jeu.nb_coups);
		jouer(&jeu,deplacement,rapport,&n,recu);
		faire_dames(&jeu);
		afficher_jeu(jeu);
		send(sock,deplacement,strlen(deplacement)+1,MSG_NOSIGNAL);
		if(jeu.nb_coups == 100){
			break;
		}
		printf("coup attaque :%s \n",deplacement);


	}
	close(sock);
	/*for(n;n < 256;n++){
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
