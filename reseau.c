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

 void envoyer_jeu(jeu_t *jeu , int sock){
     uint32_t pion,couleur,dame,numero,enc,nbc,tour;
  
     enc = jeu->en_cours;
      tour = jeu->tour;
      nbc = jeu->nb_coups;
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
             pion =jeu->plateau[i][j].pion;
             couleur = jeu->plateau[i][j].couleur;
             dame = jeu->plateau[i][j].dame;
             numero =jeu->plateau[i][j].numero;
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
    jeu->en_cours= ntohl(enc);
    jeu->nb_coups = ntohl(nbc);
    jeu->tour = ntohl(tour);

     for ( int i = 0; i < 10; i++)
     {
         for (int j = 0; j < 10; j++)
         {
               
                read(sock,&pion,sizeof(uint32_t));
                read(sock,&couleur,sizeof(u_int32_t));
                read(sock,&dame,sizeof(uint32_t));
                read(sock,&numero,sizeof(uint32_t));
                 pion = ntohl(pion);
             couleur = ntohl(couleur);
             dame = ntohl(dame);
             numero =ntohl(numero);
             
                 jeu->plateau[i][j].pion = pion;
                jeu->plateau[i][j].couleur= couleur;
                jeu->plateau[i][j].dame= dame;
                jeu->plateau[i][j].numero= numero;
         }
         
     }
     
 }

 void jouer(jeu_t * jeu,char * deplacement){
     int x1,x2,y1,y2,numero1,numero2,move;
    if(capture_est_possible(*jeu, &numero1, &numero2)){
      capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
      deplacer_pion(jeu,x1,y1,x2,y2);
      coord_numero(*jeu, x2, y2, &numero1);
      while(pion_peut_capturer(*jeu, numero1, &numero2)){
        capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
        deplacer_pion(jeu,x1,y1,x2,y2);
        coord_numero(*jeu, x2, y2, &numero1);
      }
    }

    else{
      while((move = saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu->tour, jeu)));
      deplacer_pion(jeu,x1,y1,x2,y2);
    }
    
 }