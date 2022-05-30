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

/*La fonction qui effectue le jeux c'est le robot Robot_joueur*/
void jouer(jeu_t * jeu,char * deplacement,uint8_t * octets, int * n);
/*fonction qui verifie si une capture est possible de maniere aleatoire  et renvoie 1 si oui, sinon 0*/
int capture_est_possible_alea(jeu_t jeu, int * numero1, int * numero2,char * deplacement);
/*fonction qui nous renvoie une capture à faire de maniere aleatoire */
int choisir_capture_alea(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement);
/*fonction utiliser dans la sauvegarde de la partie qui enregistre les deplacements*/
void ajouter_deplacement(uint8_t * oct,int * pos,char * deplacement);
/*fonction utiliser dans la sauvegarde de la partie qui enregistre les captures*/
void ajouter_capture(uint8_t * oct,int * pos,char * capture);
/*fonction pour copier l'addresse ipv6 du client et le sauvegarder dans les logs*/
void copier_ipv6(uint8_t * oct,int * pos,unsigned char * addr);
/*fonction pour concatainer les octets sauvegardes*/
void concatener_octets(uint8_t * dest,uint8_t *src,int *n);
/*fonction qui teste si un coup est correcte ou pas  et renvoie 1 si oui, sinon 0  */
int tester_coup(jeu_t jeu,char * coup);
/*fonction qui se charge de faire jouer un coup */
void appliquer_coup(jeu_t *jeu,char * coup);
/*fonction qui se teste si un coup est un deplacement */
int est_deplacement (char * coup);
/*fonction qui se teste si un coup est une capture */
int est_capture(char * coup);
/*fonction qui se convertie des octets en chaine de caractere */
void convertir_octets_chaine(uint8_t * oct,char *deplacement);
/*fonction qui ajoute un '\0' à la fin d'une chaine de caracteres */
void remplir_fin_de_chaine(char * c, int taille);
/*fonction qui remplie le rapport*/
void remplir_rapport(char * dep, uint8_t * oct , int *n);
void extraire(char * s,char *dest);

void  move_alea(jeu_t jeu, int couleur,char * s);
void choisir_capture_dames_alea(tabi_t bourreaux[],int * num1,int * num2,int taille);

#endif
