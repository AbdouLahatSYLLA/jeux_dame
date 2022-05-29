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
void jouer(jeu_t * jeu,char * deplacement,uint8_t * octets, int * n);
void recherche_pion_qui_bouge(jeu_t * jeu,char * coup);
void recherche_pion_qui_bouge_noir(jeu_t * jeu,char * coup);
void recherche_pion_qui_bouge_blanc(jeu_t * jeu,char * coup);
int capture_est_possible_alea(jeu_t jeu, int * numero1, int * numero2,char * deplacement);
int choisir_capture_alea(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement);
void ajouter_deplacement(uint8_t * oct,int * pos,char * deplacement);
void ajouter_capture(uint8_t * oct,int * pos,char * capture);
void copier_ipv6(uint8_t * oct,int * pos,unsigned char * addr);
void concatener_octets(uint8_t * dest,uint8_t *src,int *n);
int tester_coup(jeu_t jeu,char * coup);
void appliquer_coup(jeu_t *jeu,char * coup);
int est_deplacement (char * coup);
int est_capture(char * coup);
void convertir_octets_chaine(uint8_t * oct,char *deplacement);
void remplir_fin_de_chaine(char * c, int taille);
void remplir_rapport(char * dep, uint8_t * oct , int *n);
//void Robot_joueur(jeu_t * jeu);


#endif
