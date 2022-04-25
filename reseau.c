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

 void envoyer_cases(jeu_t *jeu , int sock){
     uint32_t pion,couleur,dame,numero,enc;
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



  void recevoir_cases(jeu_t  *jeu , int sock){
     uint32_t pion,couleur,dame,numero;
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