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
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include "reseau.h"

typedef struct{
    jeu_t *jeu;
    int sock;
}client;

#define JEUX_DAME 7777
#define RAPPORT 5777

char deplacement[100];
void resultat_jeu(jeu_t *jeu);
void * joueur2(void * arg);

int main()
{
  pthread_t th;
  uint8_t rapport[256];
  char adresse_rapport[] = "2001:910:1410:523:0:fada:80af:2bc2";
  rapport[0] = 255;
  int n = 1;
  /* Création/Ouverture d'un fichier servant de journal de connections */
  int fic = open("journal_de_bord.log",O_WRONLY|O_CREAT|O_TRUNC, 0644);
  if(fic < 0){
    perror("Erreur : Création/Ouverture du journal de connections");
    return 1;
  }

	/* 1. Création d'une socket tcp ipv6 de la partie */
	int sock = socket(AF_INET6, SOCK_STREAM, 0);
	if (sock < 0) {
		perror("socket");
		exit(2);
	}

	/* 2. Création de la sockaddr de la partie */
	struct sockaddr_in6 sa = { .sin6_family = AF_INET6,
				                    .sin6_port = htons(JEUX_DAME),
				                    .sin6_addr = in6addr_any };
	/* Optionnel : faire en sorte de pouvoir réutiliser l'adresse sans
	 * attendre après la fin du serveur. */
  	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
	//Sockaddr pour l'envoi au serveur du prof
	struct sockaddr_in6 ss ={.sin6_family = AF_INET6,.sin6_port = htons(RAPPORT)};
	if(inet_pton(AF_INET6,adresse_rapport,&ss.sin6_addr) >0){
		puts("Succès");
	}
	/* 3. Attacher la socket d'écoute à l'adresse */
	if (bind(sock, (struct sockaddr *) &sa, sizeof(sa)) < 0) {
		perror("bind");
		exit(3);
	}

	/* 4. Écouter sur la socket d'écoute */
	if (listen(sock, 128) < 0) {
		perror("listen");
		exit(2);
	}



	/* 5. Attente passive d'une connection. */
  struct sockaddr_in6 addr_clt;
  socklen_t taille_addr = sizeof(struct sockaddr_in6);
	int sock_echange = accept(sock, (struct sockaddr *)&addr_clt, &taille_addr);
	  if(sock_echange < 0){
      perror("erreur : accept");
      exit(2);
  }
	//Ajouter l'ipv6 de l'adversaire dans le rapport
    copier_ipv6(rapport,&n,addr_clt.sin6_addr.s6_addr);
  /*Converti l'adresse ipv6 sous forme binaire en texte*/
    char addr_char[INET6_ADDRSTRLEN];
    if(inet_ntop(AF_INET6, &(addr_clt.sin6_addr), addr_char, INET6_ADDRSTRLEN) == NULL){
      perror("Erreur : inet_ntop");
    }
    else{
      /*Ecrit dans le fichier servant de journal de connections,
        la date, l'heure et de l'adresse du client qui se connecte au serveur*/
      time_t now = time(NULL);
      char date_heure[32], log_mess[256];
      strftime(date_heure, 32, "%F:%T", localtime(&now));
      sprintf(log_mess, "%s : connection avec %s\n", date_heure, addr_char);
			write(fic, log_mess, strlen(log_mess));
    }

  /*Création et initialisation d'un jeu*/
  jeu_t jeu ;
  initialiser_jeu(&jeu);
  /*Les blancs vont commencer la partie*/
  /*Pour l'attaquant*/
	int pion_noirs,pion_blancs,test;
  /*Pour le défenseur*/
	while (jeu.en_cours)
	{
		printf("Coup n° %d \n",jeu.nb_coups);
		jouer(&jeu,deplacement,rapport,&n);
		remplir_fin_de_chaine(deplacement,100);
	    jeu.tour = jeu.nb_coups % 2 == 0 ? BLANC : NOIR;
		faire_dames(&jeu);
		pion_noirs = compter_pions(NOIR,&jeu);
		pion_blancs = compter_pions (BLANC,&jeu);
		printf("BLANC : %s \n",deplacement);
		write(sock_echange,deplacement,sizeof(deplacement));
		afficher_jeu(jeu);
		read(sock_echange,deplacement,sizeof(deplacement));
		remplir_fin_de_chaine(deplacement,100);
		printf("NOIR : %s \n",deplacement);
		test = tester_coup(jeu,deplacement);
		if(test == 0){
			write(sock_echange,"INVALIDE",strlen("INVALIDE")+1);
			break;
		}
		appliquer_coup(&jeu,deplacement);
		remplir_rapport(deplacement,rapport,&n);
		printf("Coup n° %d \n",jeu.nb_coups);
		afficher_jeu(jeu);
	    pion_noirs = compter_pions(NOIR,&jeu);
    	pion_blancs = compter_pions(BLANC,&jeu);
    	if( jeu.nb_coups == 100){
			jeu.en_cours = 0;
			write(sock_echange,"EGALITE",strlen("EGALITE")+1);
			break;
		}
		if(pion_noirs == 0){
			jeu.en_cours = 0;
			write(sock_echange,"PERDU",strlen("PERDU")+1);
			break;
		}
    }
	resultat_jeu(&jeu);
	close(sock_echange);
	close(sock);
	for(n;n < 256;n++){
		rapport[n] = 0;
	}
	printf("%d octets\n",n);
	for ( int i = 0; i < n; i++)
	{
		printf("%x ",rapport[i]);
	}
	//Envoi du rapport au prof
	/*
	int sock2 =  socket(AF_INET6, SOCK_STREAM, 0);
	if (sock2 < 0) {
		perror("socket");
		exit(2);
	}
	if(connect(sock2,(struct sockaddr*)&ss,sizeof(ss)) == 0){
		write(sock2,rapport,sizeof(rapport));
		puts("Envoi réussi");
	}
	else
	{
		puts("Envoi echoué");
	}
	*/
	putchar('\n');
	return 0;
}



//DEHOOOOORS
void resultat_jeu(jeu_t *jeu){
	int pion_noirs,pion_blancs;
	pion_noirs = compter_pions(NOIR,jeu);
    pion_blancs = compter_pions(BLANC,jeu);
    	if(pion_noirs == 0){
      	printf("Victoire des blancs\n");
   		 }
   	 	else if(pion_blancs == 0){
    	  printf("Victoire des noirs\n");
   		 }

   	   else if(jeu->nb_coups == 100){
      	printf("Egalite\n");
    	}
}
