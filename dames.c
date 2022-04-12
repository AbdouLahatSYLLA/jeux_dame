#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <string.h>

void initialiser_jeu(jeu_t * jeu){
  int num = 1;
  jeu->nb_noir = 20;
  jeu->nb_blanc = 20;
  for(int i = 0; i < 10; i++){
    for(int j = 0 ; j < 10 ; j++) {
       if(i == 4 || i == 5) {

        jeu->plateau[i][j].couleur = -1;
        jeu->plateau[i][j].pion = -1;
        jeu->plateau[i][j].dame = -1;
        jeu->plateau[i][j].numero = -1;

        if(i % 2 == 0 && j % 2 == 1 ) {
        jeu->plateau[i][j].couleur = 0;
        jeu->plateau[i][j].pion = 0;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;

      }
      if(i % 2 == 1 && j % 2 == 0 ) {
        jeu->plateau[i][j].couleur = 0;
        jeu->plateau[i][j].pion = 0;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;

      }
      }
      else{
        jeu->plateau[i][j].couleur = -1;
        jeu->plateau[i][j].pion = -1;
        jeu->plateau[i][j].dame = -1;
        jeu->plateau[i][j].numero = -1;

      if(i % 2 == 0 && j % 2 == 1 && i < 4) {
        jeu->plateau[i][j].couleur = NOIR;
        jeu->plateau[i][j].pion = 1;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;

      }
      if(i % 2 == 1 && j % 2 == 0 && i < 4) {
        jeu->plateau[i][j].couleur = NOIR;
        jeu->plateau[i][j].pion = 1;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;
      }

      }
      if(i > 5 ) {

        jeu->plateau[i][j].couleur = -1;
        jeu->plateau[i][j].pion = -1;
        jeu->plateau[i][j].dame = -1;
        jeu->plateau[i][j].numero = -1;

         if(i % 2 == 0 && j % 2 == 1 ) {
        jeu->plateau[i][j].couleur = BLANC;
        jeu->plateau[i][j].pion = 1;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;

      }
      if(i % 2 == 1 && j % 2 == 0 ) {
        jeu->plateau[i][j].couleur = BLANC;
        jeu->plateau[i][j].pion = 1;
        jeu->plateau[i][j].dame = 0;
        jeu->plateau[i][j].numero = num;
        num++;
      }
      }

  }
  }

  jeu->en_cours = 1;
  jeu->tour = 1;
  jeu->nb_coups = 0;
}

void verifier_dame(jeu_t * jeu){
 /* for(int i = 0; i < 5; i++){
    if(jeu->plateau[i].pion == 1 && jeu->plateau[i].couleur == 1){
      jeu->plateau[i].dame = 1;
    }
  }
  for(int i = 45; i < 50; i++){
    if(jeu->plateau[i].pion == 1 && jeu->plateau[i].couleur == 0){
      jeu->plateau[i].dame = 1;
    }
  }*/
  return;
}

void deplacer_pion (jeu_t * jeu , int x1,int y1,int x2,int y2) {

    if(jeu->plateau[x2][y2].pion == 0) {
        printf("%s : %d-%d \n",jeu->plateau[x1][y1].pion == NOIR ? "Noir" : "Blanc",jeu->plateau[x1][y1].numero,jeu->plateau[x2][y2].numero);
        jeu->plateau[x2][y2].pion = jeu->plateau[x1][y1].pion;
        jeu->plateau[x2][y2].couleur = jeu->plateau[x1][y1].couleur;
        jeu->plateau[x1][y1].pion = 0;
        }
    else if(jeu->plateau[x2][y2].pion == 1 && (jeu->plateau[x2][y2].couleur == BLANC ||jeu->plateau[x2][y2].couleur == NOIR)){
        printf("%s : %dx%d \n",jeu->plateau[x1][y1].pion == NOIR ? "Noir" : "Blanc",jeu->plateau[x1][y1].numero,jeu->plateau[x2][y2].numero);
        jeu->plateau[x2][y2].pion = jeu->plateau[x1][y1].pion;
        jeu->plateau[x2][y2].couleur = jeu->plateau[x1][y1].couleur;
        jeu->plateau[x1][y1].pion = 0;
    }

}

int compter_pions(int couleur,jeu_t *jeu) {

    int n = 0;
    for ( int i = 0; i < 10; i++)
    {
      for(int j = 0 ; j < 10 ; j++){
        if(jeu->plateau[i][j].pion !=0 && jeu->plateau[i][j].couleur == couleur){
            n++;
        }
      }
    }
    return n;
}

void afficher_jeu(jeu_t jeu){
  printf("|---|--------------------|\n| □ |");
  for(int i = 0; i < 10; i++){
    printf("%d ", i);
  }
  printf("|\n|---|--------------------|\n");
  for(int i = 0; i < 10; i++){
    printf("| %d |", i);
    for(int j = 0 ; j < 10 ; j++){
      if(jeu.plateau[i][j].pion){
        if(jeu.plateau[i][j].couleur == NOIR){
          if(i % 2 == 0){
            putchar(' ');
          }
          printf("N ");
          if(i % 2 != 0){
            putchar(' ');
          }
        }
        else if(jeu.plateau[i][j].couleur == BLANC){
          if(i % 2 == 0){
            putchar(' ');
          }
          printf("B ");
          if(i % 2 != 0){
            putchar(' ');
          }
        }
        else{
          putchar(' ');
        }
      }
      else if(jeu.plateau[i][j].numero != 0){
        if(i % 2 == 0){
          putchar(' ');
        }
        printf(". ");
        if(i % 2 != 0){
          putchar(' ');
        }
      }
    }
    printf("|\n");
  }
  printf("|---|--------------------|\n");
}
int saisir_deplacement(char * deplacement, int * x1, int * y1, int * x2, int * y2, int tour, jeu_t * jeu){
    printf("Saisissez le déplacement du pion %s : ",jeu->tour == 1 ? "blanc" : "noir");
    scanf("%s", deplacement);
    int mouvement = 3;
    int numero1, numero2;
    for(int i = 0; i < strlen(deplacement); i++){
      if(deplacement[i] == '-'){
        mouvement = 1;
        break;
      }
      if(deplacement[i] == 'x'){
        mouvement = 2;
        break;
      }
    }
    if(mouvement == 1){
      printf("Il s'agit d'un déplacement.\n");
      sscanf(deplacement, "%d-%d", &numero1, &numero2);
      if(verifier_deplacement(*jeu, numero1, numero2)){
        coord_numero(*jeu, numero1, x1, y1);
        coord_numero(*jeu, numero2, x2, y2);
        return 0;
      }
      return 1;
    }
    if(mouvement == 2){
      /*
      on verifie si la case qui suis est libre avant de pouvoir faire la capture
      et la capture est obligatoir qd c possible.
      aussi on doit prendre en compte les raffles qd tu peux capturer plus c obligatoire 
        1. on initialise un tableau avec toutes les cases qui font partie de la capture
        2. on vérifie et effectue les captures deux par deux
      */

      printf("Il s'agit d'une capture.\n");
      return 1;
    }
    if(mouvement == 3){
      printf("Il ne s'agit ni d'un déplacement ni d'une capture.\n");
      return 1;
    }
}

void coord_numero(jeu_t jeu, int numero, int * x, int * y){
  for(int i = 0; i < 10; i ++){
    for(int j = 0; j < 10; j++){
      if(jeu.plateau[i][j].numero == numero){
        *x = i;
        *y = j;
        return;
      }
    }
  }
  *x = -1;
  *y = -1;
}

int verifier_deplacement(jeu_t jeu, int numero1, int numero2){
  int x1, y1, x2, y2;
  coord_numero(jeu, numero1, &x1, &y1);
  coord_numero(jeu, numero2, &x2, &y2);
  putchar('\n');
  if(jeu.plateau[x1][y1].pion){
    if(jeu.plateau[x2][y2].pion == -1 || jeu.plateau[x2][y2].pion == 0){
      if(jeu.plateau[x1][y1].couleur == NOIR){
        if((x2 - x1 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
          printf("Déplacement possible.\n\n");
          return 1;
        }
        printf("Déplacement impossible.\n\n");
        return 0;
      }
      else if(jeu.plateau[x1][y1].couleur == BLANC){
        if((x1 - x2 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
          printf("Déplacement possible.\n\n");
          return 1;
        }
        printf("Déplacement impossible.\n\n");
        return 0;
      }
    }
    printf("Déplacement impossible : Il y a un pion sur la case d'arrivée.\n\n");
    return 0;
  }
  printf("Déplacement impossible : Pas de pion sur la case de départ.\n\n");
  return 0;
}

int verifier_capture(jeu_t jeu, int numero1, int numero2){
  int x2, y2;
  coord_numero(jeu, numero2, &x2, &y2);
  putchar('\n');
  if(verifier_deplacement(jeu, numero1, numero2)){

  }
  printf("Capture impossible : tom.\n\n");
  return 0;
}

/*fonction pour la capture l' idée est quand y a capture on remplace le pion par un point et on decremente le nombre du pion en question*/
void effacer_pions_graphique( jeu_t * jeu,int i, int j ){
  jeu->plateau[i][j] = '.';
}


/*
int ScanToutDammierSiJoueurDoitPrendre (int damier[10][10], int numerojoueur, int numeroAdversaire){

	int i, j, k;

	for (j=1; j<=10 ; j++)
		for (i= 1; i<=10 && k !=1 ;i++)
			 k = ScanCasesContigueSiPionAdverseAPrendre (damier,i, j,numerojoueur,numeroAdversaire); // dès qu'on trouve que le joueur peut prendre un pion, on arrête la recherche avec k == 1. Si le joueur ne peut pas prendre aucun pion, la boucle se termine avec k == 0
	return k;
}
*/
