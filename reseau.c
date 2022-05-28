/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dames.h"
#include <stdint.h>

/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */
#include <pthread.h>
#include <semaphore.h>
#include "reseau.h"
 void envoyer_jeu(jeu_t *jeu , int sock){
     uint32_t pion,couleur,dame,numero,enc,nbc,tour;

      enc = (uint32_t) jeu->en_cours;
      tour = (uint32_t) jeu->tour;
      nbc = (uint32_t) jeu->nb_coups;
      enc= htonl(enc);
      tour = htonl(tour);
      nbc= htonl(nbc);

    if(write(sock,&enc,sizeof(uint32_t))<=0){
      exit(2);
    }
    if(write(sock,&tour,sizeof(uint32_t))<=0){
        exit(2);
    }
    if(write(sock,&nbc,sizeof(uint32_t))<=0){
      exit(2);
    }

     for ( int i = 0; i < 10; i++)
     {
         for (int j = 0; j < 10; j++)
         {
             pion = (uint32_t) jeu->plateau[i][j].pion;
             couleur = (uint32_t) jeu->plateau[i][j].couleur;
             dame = (uint32_t)  jeu->plateau[i][j].dame;
             numero = (uint32_t) jeu->plateau[i][j].numero;
             pion = htonl(pion);
             couleur = htonl(couleur);
             dame = htonl(dame);
             numero =htonl(numero);


                if(write(sock,&pion,sizeof(uint32_t))<=0){
                    exit(2);
                }
                if(write(sock,&couleur,sizeof(uint32_t))<=0){
                    exit(2);
                }
                if(write(sock,&dame,sizeof(uint32_t))<=0){
                    exit(2);
                }
                if(write(sock,&numero,sizeof(uint32_t))<=0){
                    exit(2);
                }
         }

     }

 }


  void recevoir_jeu(jeu_t  *jeu , int sock){
     uint32_t pion,couleur,dame,numero,enc,nbc,tour;

    read(sock,&enc,sizeof(uint32_t));
    read(sock,&tour,sizeof(uint32_t));
    read(sock,&nbc,sizeof(uint32_t));
    jeu->en_cours= (int) ntohl(enc);
    jeu->nb_coups = (int) ntohl(nbc);
    jeu->tour = (int) ntohl(tour);

     for ( int i = 0; i < 10; i++)
     {
         for (int j = 0; j < 10; j++)
         {

                if(read(sock,&pion,sizeof(uint32_t)) <=0){
                  exit(2);
                }
                if(read(sock,&couleur,sizeof(uint32_t)) <=0){
                   exit(2);
                }
                if(read(sock,&dame,sizeof(uint32_t)) <=0){
                    exit(2);
                }
                if(read(sock,&numero,sizeof(uint32_t)) <=0){
                    exit(2);
                }
                 pion = ntohl(pion);
             couleur = ntohl(couleur);
             dame = ntohl(dame);
             numero =ntohl(numero);

                 jeu->plateau[i][j].pion = (int)  pion;
                jeu->plateau[i][j].couleur= (int)  couleur;
                jeu->plateau[i][j].dame= (int)  dame;
                jeu->plateau[i][j].numero= (int) numero;
         }

     }

 }

//Version bot
 void jouer(jeu_t * jeu,char * deplacement,uint8_t * octets, int * n,uint8_t *dep){
     int x1,x2,y1,y2,numero1,numero2,move;
     int x = 0;
     tabi_t bourreaux[50];
     char copie[100];
     char suite[10];
     if(capture_est_possible_alea(*jeu, &numero1, &numero2,deplacement)){
      int a,b,c,d;
      numero_coord(*jeu,numero1,&a,&b);
      numero_coord(*jeu,numero2,&c,&d);
      if(verifier_dame(jeu,a,b) && dame_peut_capturer(jeu,a,b,c,d)){
        capturer_avec_une_dame(jeu,numero1,numero2,&a,&b,&c,&d);
        int n = 0;
        numero1 = numero2;
        a = c;
        b = d;
        while (captures_dame_possibles(jeu,a,b,bourreaux,&n,&numero2))
        {
          printf("%dx%d\n",numero1,numero2);
          sprintf(suite,"x%d",numero2);
          strcat(deplacement,suite);
          numero_coord(*jeu,numero2,&c,&d);
          capturer_avec_une_dame(jeu,numero1,numero2,&a,&b,&c,&d);
          a = c;
          b = d;
           numero1 = numero2;
           n = 0;
        }
      }
      else{
        capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
        deplacer_pion(jeu,x1,y1,x2,y2);
        coord_numero(*jeu, x2, y2, &numero1);
        while(pion_peut_capturer(*jeu, numero1, &numero2)){
          sprintf(suite,"x%d",numero2);
          strcat(deplacement,suite);
          capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
          deplacer_pion(jeu,x1,y1,x2,y2);
          coord_numero(*jeu, x2, y2, &numero1);
        }
      }
       strcpy(copie,deplacement);
        ajouter_capture(octets,n,deplacement);
        ajouter_capture(dep,&x,copie);
        dep[x] = '\0';

        
    }
    /*Deplacements normaux*/
    else{
      
      if(jeu->tour == BLANC){
        recherche_pion_qui_bouge_blanc(jeu,deplacement);
      }
      else if(jeu->tour == NOIR){
        recherche_pion_qui_bouge_noir(jeu,deplacement);
      }
      while((move = saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu->tour, jeu)));
      if(jeu->plateau[x1][y1].dame ==1 ){
        deplacer_dame(jeu,x1,y1,x2,y2);
      }
      else
      deplacer_pion(jeu,x1,y1,x2,y2);
      strcpy(copie,deplacement);
      ajouter_deplacement(octets,n,deplacement);
      printf("Après ajout %s\n",copie);
      ajouter_deplacement(dep,&x,copie);
      dep[x] = '\0';

    }
    
    jeu->nb_coups++;
 }
/*
 void Robot_joueur(jeu_t * jeu,int sock){
  d abord on fait la capture s il y a une capture à faire
   sinon on recherche le premier pion qui peux se deplacer et on prends son nimero avec numero_coord-le premier deplacement
  à faire et on envoie cette chaine comme etant notre coup;

  char coup[32];
  int numero1,numero2;
  if(capture_est_possible(jeu,&numero1,&numero2)){
    sprintf(coup,"%dx%d",numero1,numero2);
    envoyer_jeu()
  }
 }
*/
void recherche_pion_qui_bouge(jeu_t * jeu,char * coup){
  int numero1,numero2;
  coup = malloc(100);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if(jeu->tour == jeu->plateau[i][i].couleur){
        if(jeu->plateau[i][i].couleur == BLANC){
          if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
        }
         if(jeu->plateau[i][i].couleur == NOIR){
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
          if(jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
        }
      }
    }
  }
}


void recherche_pion_qui_bouge_noir(jeu_t * jeu,char * coup){
  int numero1,numero2;
  int choix[2];
  int nb_choix = 0;
  int alea;
  if(jeu->tour == NOIR){ 
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 10; j++) {

      if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion > 0 ){
        if(jeu->plateau[i][j].couleur == NOIR) {
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }
           if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          if (nb_choix > 0) {
           srand(time(NULL));
           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
      
    }

  }
}
}

void recherche_pion_qui_bouge_blanc(jeu_t * jeu,char * coup){
   int numero1,numero2;
  int choix[2];
  int nb_choix = 0;
  int alea;
for (int i = 9; i >= 0; i--)
  {
    for (int j = 0; j <  10; j++)
    {
       if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion > 0 ){
        if(jeu->plateau[i][j].couleur == BLANC){
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }
          
          if(nb_choix > 0){
          srand(time(NULL));
           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
    }
    
  }
}  

int capture_est_possible_alea(jeu_t jeu, int * numero1, int * numero2,char * deplacement){
  int n = 0;
  tabi_t bourreaux[100];
  printf("Captures possibles %s :\n", jeu.tour == BLANC ? "\033[36;01mBlanc\033[00m" : "\033[31;01mNoir\033[00m");
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      //dames
      if(verifier_dame(&jeu,i,j)){
      if((jeu.tour == BLANC && jeu.plateau[i][j].couleur == BLANC) || (jeu.tour == NOIR && jeu.plateau[i][j].couleur == NOIR)){
          coord_numero(jeu, i, j, numero1);
          if (captures_dame_possibles(&jeu,i,j,bourreaux,&n,numero2))
            printf("%dx%d Dame\n",*numero1,*numero2);
            sprintf(deplacement,"%dx%d", *numero1, *numero2);
          }
        }

      //Pions normaux
      if(jeu.plateau[i][j].pion && jeu.plateau[i][j].dame == 0){
        if((jeu.tour == BLANC && jeu.plateau[i][j].couleur == BLANC) || (jeu.tour == NOIR && jeu.plateau[i][j].couleur == NOIR)){
          coord_numero(jeu, i, j, numero1);
          if(pion_peut_capturer(jeu, *numero1, numero2)){
            sprintf(deplacement,"%dx%d", *numero1, *numero2);
            bourreaux[n].t[0] = *numero1;
            bourreaux[n].t[1] = *numero2;
            n++;
          }
        }
      }
    }
  }
  if(n == 0){
    printf("Aucune capture n'est possible.\n");
    return 0;
  }
  else if(n > 0){
    choisir_capture_alea(jeu, bourreaux, n, numero1,numero2,deplacement);
    return 1;
  }

  return 1;
}

int choisir_capture_alea(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement){
  //char choix[50];
  int poubelle;
  int alea;
  srand(time(NULL));
  alea = rand() % taille;
  printf("%d taille : %d \n",alea,taille);
  *numero1 = bourreaux[alea].t[0];
  *numero2 = bourreaux[alea].t[1];
  printf("Capture : %dx%d",*numero1,*numero2);
  sprintf(deplacement, "%dx%d", numero1, numero2);
   if(capture_appartient(jeu, bourreaux, taille, deplacement)){
      return 1;
    }
  putchar('\n');
  
  return 0;
}


void ajouter_deplacement(uint8_t * oct,int * pos,char * deplacement){
    char * dep = strtok(deplacement,"-x");
    while (dep != NULL)
{
    oct[*pos] = atoi(dep)+128;
    *pos = *pos +1;
    dep = strtok(NULL,"-x");
   
}
}
void ajouter_capture(uint8_t * oct,int * pos,char * capture){
    char *dep = strtok(capture,"x-");
    while (dep != NULL)
{
    oct[*pos] =  atoi(dep);
    *pos = *pos + 1;
    dep = strtok(NULL,"x-");
}
oct[*pos -1 ] = oct[*pos -1] +128;
}
void copier_ipv6(uint8_t * oct,int * pos,unsigned char * addr){
    for (int i = 0; i <16 ; i++)
{
    oct[*pos] = addr[i];
    *pos = *pos + 1;
}

}
void concatener_octets(uint8_t * dest,uint8_t*src,int *n){
  uint8_t *c = src;
  for(;*c != '\0';++c){
    dest[*n] = *c;
    *n = *n + 1;
  }
}
