#ifndef __RESEAU__
#define __RESEAU__
#include "dames.h"
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


void envoyer_jeu(jeu_t *jeu ,int sock);
void recevoir_jeu(jeu_t *jeu ,int sock);
void jouer(jeu_t * jeu,char * deplacement);
void recherche_pion_qui_bouge(jeu_t * jeu,char * coup);
//void Robot_joueur(jeu_t * jeu);


#endif