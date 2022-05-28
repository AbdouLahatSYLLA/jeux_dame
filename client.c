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

	int pion_blancs,pion_noirs;
	/* 4. Échange avec le serveur */
	/* 4.1 Construction de la requête INCP */
	 jeu_t jeu;
	 initialiser_jeu(&jeu);
	 jeu.en_cours =1;
	 	 jeu.tour = NOIR;
	int x1,y1,x2,y2;
	 initialiser_jeu(&jeu);
	while (jeu.en_cours)
	{
		read(sock,deplacement,sizeof(deplacement));
		if(!strcmp(deplacement,interruption)){
			jeu.en_cours = 0;
			break;
		}
		if(!strcmp(deplacement,mauvais_coup)){
			jeu.en_cours = 0;
			break;
		}
		if(!strcmp(deplacement,egalite) || !strcmp(deplacement,perdu)){
			jeu.en_cours = 0;
			break;
		}
		strcpy(dep2,deplacement);
		if(verifier_coup(deplacement, &x1,&y1,&x2, &y2,NOIR, &jeu) == 1){
			ajouter_deplacement(rapport,&n,dep2);
		}
		
		else if(verifier_coup(deplacement, &x1,&y1,&x2,&y2,NOIR, &jeu) == 2){
			ajouter_capture(rapport,&n,dep2);
		}
		else if (verifier_coup(deplacement, &x1,&y1,&x2,&y2,NOIR, &jeu) == 3)
		{
			write(sock,mauvais_coup,strlen(mauvais_coup) +1);
			close(sock);
			exit(2);
		}
		//Verifier si c'est deplacement ou une capture ou coup invalide
		//Appliquer deplacement sur notre jeu
		//Concat octets
		faire_dames(&jeu);
		jeu.nb_coups++;
		printf("Coup n° %d \n",jeu.nb_coups);
		jouer(&jeu,deplacement,rapport,&n,recu);
		faire_dames(&jeu);
		afficher_jeu(jeu);
		write(sock,deplacement,sizeof(deplacement));


	}
	
	close(sock);
	for(n;n < 256;n++){
		rapport[n] = '\0';
	}
	printf("%d octets\n",n);
	for ( int i = 0; i < n; i++)
	{
		printf("%x ",rapport[i]);
	}
	putchar('\n');
	return 0;
}
