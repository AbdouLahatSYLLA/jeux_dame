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

    write(sock,&enc,sizeof(uint32_t));
    write(sock,&tour,sizeof(uint32_t));
    write(sock,&nbc,sizeof(uint32_t));

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
             

                write(sock,&pion,sizeof(uint32_t));
                write(sock,&couleur,sizeof(uint32_t));
                write(sock,&dame,sizeof(uint32_t));
                write(sock,&numero,sizeof(uint32_t));
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
               
                read(sock,&pion,sizeof(uint32_t));
                read(sock,&couleur,sizeof(uint32_t));
                read(sock,&dame,sizeof(uint32_t));
                read(sock,&numero,sizeof(uint32_t));
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

 void jouer(jeu_t * jeu,char * deplacement){
     int x1,x2,y1,y2,numero1,numero2,move;
     tabi_t bourreaux[50];
     if(capture_est_possible(*jeu, &numero1, &numero2)){
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
          capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
          deplacer_pion(jeu,x1,y1,x2,y2);
          coord_numero(*jeu, x2, y2, &numero1);
        }

      }

    }
    /*Deplacements normaux*/
    else{
      while((move = saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu->tour, jeu)));
      if(jeu->plateau[x1][y1].dame ==1 ){
        deplacer_dame(jeu,x1,y1,x2,y2);
      }
      else
      deplacer_pion(jeu,x1,y1,x2,y2);
    }
 }