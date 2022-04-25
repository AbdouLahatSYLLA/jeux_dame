#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <string.h>

void initialiser_jeu(jeu_t * jeu){
  int num = 1;
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
/*
void verifier_dame(jeu_t * jeu){
  for(int i = 0; i < 5; i++){
    if(jeu->plateau[i].pion == 1 && jeu->plateau[i].couleur == 1){
      jeu->plateau[i].dame = 1;
    }
  }
  for(int i = 45; i < 50; i++){
    if(jeu->plateau[i].pion == 1 && jeu->plateau[i].couleur == 0){
      jeu->plateau[i].dame = 1;
    }
  }
  return;
}*/

void deplacer_pion (jeu_t * jeu , int x1,int y1,int x2,int y2){
  if(jeu->plateau[x1][y1].pion){
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
        if(jeu->plateau[i][j].pion && jeu->plateau[i][j].couleur == couleur){
            n++;
        }
      }
    }
    return n;
}

void afficher_jeu(jeu_t jeu){
  printf("\033[32;01m|---|--------------------|\n| □ |\033[00m");
  for(int i = 0; i < 10; i++){
    printf("\033[32;01m%d\033[00m ", i);
  }
  printf("\033[32;01m|\n|---|--------------------|\n\033[00m");
  for(int i = 0; i < 10; i++){
    printf("\033[32;01m| %d |\033[00m", i);
    for(int j = 0 ; j < 10 ; j++){
      if(jeu.plateau[i][j].pion){
        if(jeu.plateau[i][j].couleur == NOIR){
          if(i % 2 == 0){
            putchar(' ');
          }
          printf("\033[31;01mN\033[00m ");
          if(i % 2 != 0){
            putchar(' ');
          }
        }
        else if(jeu.plateau[i][j].couleur == BLANC){
          if(i % 2 == 0){
            putchar(' ');
          }
          printf("\033[36;01mB\033[00m ");
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
        printf("\033[32;01m.\033[00m ");
        if(i % 2 != 0){
          putchar(' ');
        }
      }
    }
    printf("\033[32;01m|\n\033[00m");
  }
  printf("\033[32;01m|---|--------------------|\n\033[00m");
}

int saisir_deplacement(char * deplacement, int * x1, int * y1, int * x2, int * y2, int tour, jeu_t * jeu){
    printf("\n%s : ",jeu->tour == 1 ? "\033[36;01mBlanc\033[00m" : "\033[31;01mNoir\033[00m");
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
      printf("\nIl s'agit d'un déplacement.\n");
      sscanf(deplacement, "%d-%d", &numero1, &numero2);
      if(verifier_deplacement(*jeu, numero1, numero2)){
        numero_coord(*jeu, numero1, x1, y1);
        numero_coord(*jeu, numero2, x2, y2);
        return 0;
      }
      return 1;
    }
    if(mouvement == 2){
      printf("\nIl s'agit d'une capture.\n");
      sscanf(deplacement, "%dx%d", &numero1, &numero2);
      if(verifier_capture(*jeu, numero1, numero2, 1)){
        capturer(jeu, numero1, numero2, x1, y1, x2, y2);
        return 0;
      }
      return 1;
    }
    if(mouvement == 3){
      printf("Il ne s'agit ni d'un déplacement ni d'une capture.\n");
      return 1;
    }
    return 1;
}

void capturer(jeu_t * jeu, int numero1, int numero2, int * x1, int * y1, int * x2, int * y2){
  numero_coord(*jeu, numero1, x1, y1);
  numero_coord(*jeu, numero2, x2, y2);
  deplacer_pion(jeu, *x1, *y1, *x2, *y2);
  if(*y1 > *y2){
    if(jeu->plateau[*x1][*y1].couleur == NOIR){
      *x1 = *x2;
      *y1 = *y2;
      *x2 = *x2 + 1;
      *y2 = *y2 - 1;
    }
    else if(jeu->plateau[*x1][*y1].couleur == BLANC){
      *x1 = *x2;
      *y1 = *y2;
      *x2 = *x2 - 1;
      *y2 = *y2 - 1;
    }
  }
  else if(*y2 > *y1){
    if(jeu->plateau[*x1][*y1].couleur == NOIR){
      *x1 = *x2;
      *y1 = *y2;
      *x2 = *x2 + 1;
      *y2 = *y2 + 1;
    }
    else if(jeu->plateau[*x1][*y1].couleur == BLANC){
      *x1 = *x2;
      *y1 = *y2;
      *x2 = *x2 - 1;
      *y2 = *y2 + 1;
    }
  }
}

void numero_coord(jeu_t jeu, int numero, int * x, int * y){
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
  numero_coord(jeu, numero1, &x1, &y1);
  numero_coord(jeu, numero2, &x2, &y2);
  if(jeu.plateau[x1][y1].pion){
    if(jeu.plateau[x1][y1].couleur == BLANC && jeu.tour == 1 || jeu.plateau[x1][y1].couleur == NOIR && jeu.tour == 0){
      if(jeu.plateau[x2][y2].pion == 0){
        if(jeu.plateau[x1][y1].couleur == NOIR){
          if((x2 - x1 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            printf("Possible.\n\n");
            return 1;
          }
          printf("Impossible : Le pion ne peut se déplacer que d'une case en diagonale.\n");
          return 0;
        }
        else if(jeu.plateau[x1][y1].couleur == BLANC){
          if((x1 - x2 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            printf("Possible.\n\n");
            return 1;
          }
          printf("Impossible : Le pion ne peut se déplacer que d'une case en diagonale.\n");
          return 0;
        }
      }
      printf("Impossible : Il y a un pion sur la case d'arrivée.\n");
      return 0;
    }
    printf("Impossible : Le pion à déplacer n'est pas de la bonne couleur.\n");
    return 0;
  }
  printf("Impossible : Pas de pion sur la case de départ.\n");
  return 0;
}

int verifier_capture(jeu_t jeu, int numero1, int numero2, int affichage){
  int x1, y1, x2, y2;
  numero_coord(jeu, numero1, &x1, &y1);
  numero_coord(jeu, numero2, &x2, &y2);
  if(affichage){
    putchar('\n');
  }
  if(jeu.plateau[x1][y1].couleur == jeu.plateau[x2][y2].couleur){
    if(affichage){
      printf("Impossible : Un pion ne peut pas capturer un pion de la même couleur.\n");
    }
    return 0;
  }
  if(jeu.plateau[x1][y1].pion && jeu.plateau[x2][y2].pion){
    if(jeu.plateau[x1][y1].couleur == BLANC && jeu.tour == 1 || jeu.plateau[x1][y1].couleur == NOIR && jeu.tour == 0){
        if(jeu.plateau[x1][y1].couleur == NOIR){
          if((x2 - x1 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            if(y1 > y2){
              if(jeu.plateau[x1][y1].couleur == NOIR){
                if(jeu.plateau[x2 + 1][y2 - 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
              else if(jeu.plateau[x1][y1].couleur == BLANC){
                if(jeu.plateau[x2 - 1][y2 - 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
            }
            else if(y2 > y1){
              if(jeu.plateau[x1][y1].couleur == NOIR){
                if(jeu.plateau[x2 + 1][y2 + 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
              else if(jeu.plateau[x1][y1].couleur == BLANC){
                if(jeu.plateau[x2 - 1][y2 + 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
            }
          }
          if(affichage){
            printf("Impossible : Le pion ne peut se déplacer que d'une case en diagonale.\n");
          }
          return 0;
        }
        else if(jeu.plateau[x1][y1].couleur == BLANC){
          if((x1 - x2 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            if(y1 > y2){
              if(jeu.plateau[x1][y1].couleur == NOIR){
                if(jeu.plateau[x2 + 1][y2 - 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
              else if(jeu.plateau[x1][y1].couleur == BLANC){
                if(jeu.plateau[x2 - 1][y2 - 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
            }
            else if(y2 > y1){
              if(jeu.plateau[x1][y1].couleur == NOIR){
                if(jeu.plateau[x2 + 1][y2 + 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
              else if(jeu.plateau[x1][y1].couleur == BLANC){
                if(jeu.plateau[x2 - 1][y2 + 1].pion == 0){
                  if(affichage){
                    printf("Possible.\n\n");
                  }
                  return 1;
                }
                if(affichage){
                  printf("Impossible : L'espace derrière le pion à capturer n'est pas vide.\n");
                }
                return 0;
              }
            }
          }
          if(affichage){
            printf("Impossible : Le pion ne peut se déplacer que d'une case en diagonale.\n");
          }
          return 0;
        }
    }
    if(affichage){
      printf("Impossible : Le pion à déplacer n'est pas de la bonne couleur.\n");
    }
    return 0;
  }
  if(affichage){
    printf("Impossible : Pas de pion sur la case de départ.\n");
  }
  return 0;
}

void coord_numero(jeu_t jeu, int x, int y, int * numero){
  *numero = jeu.plateau[x][y].numero;
}

int pion_peut_capturer(jeu_t jeu, int numero, int * capture){
  int x, y;
  numero_coord(jeu, numero, &x, &y);
  int capture1, capture2;
  if(jeu.plateau[x][y].pion){
    if(jeu.plateau[x][y].couleur == NOIR){
      coord_numero(jeu, x + 1, y - 1, &capture1);
      coord_numero(jeu, x + 1, y + 1, &capture2);
    }
    else if(jeu.plateau[x][y].couleur == BLANC){
      coord_numero(jeu, x - 1, y - 1, &capture1);
      coord_numero(jeu, x - 1, y + 1, &capture2);
    }
    if(verifier_capture(jeu, numero, capture1, 0)){
      *capture = capture1;
      return 1;
    }
    else if(verifier_capture(jeu, numero, capture2, 0)){
      *capture = capture2;
      return 1;
    }
  }
  return 0;
}

int capture_est_possible(jeu_t jeu, int * numero1, int * numero2){
  int n = 0;
  couple_t bourreaux[50];
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      if(jeu.plateau[i][j].pion){
        coord_numero(jeu, i, j, numero1);
        if(pion_peut_capturer(jeu, *numero1, numero2)){
          printf("Le pion de la case %d peut capturer celui de la case %d.\n", *numero1, *numero2);
          bourreaux[n].a = *numero1;
          bourreaux[n].b = *numero2;
          n++;
        }
      }
    }
  }
  if(n == 0){
    printf("Aucune capture n'est possible.\n");
    return 0;
  }
  else if(n > 0){
    choisir_capture(jeu, bourreaux, n, numero1);
    return 1;
  }
  return 1;
}

int choisir_capture(jeu_t jeu, couple_t bourreaux[], int taille, int * numero){
  int choix;int dest;char chaine[6];
  while(1){
    printf("\nChoisit le ptn de pion qui doit capturer : ");
    scanf("%s",chaine );
    sscanf(chaine,"%dx%d", &choix,&dest);
    if(pion_appartient(jeu, bourreaux, taille, choix)){
      *numero = choix;
      return 1;
    }
  }
  return 0;
}

int pion_appartient(jeu_t jeu, couple_t bourreaux[], int taille, int numero){
  for(int i = 0; i < taille; i++){
    if(bourreaux[i].a == numero){
      return 1;
    }
  }
  return 0;
}

void faire_dames(jeu_t* jeu,int couleur) {
  int i,j;
  if(couleur==NOIR) {
    i=9 ;
    j=0 ;
  }else{
    i=0 ;
    j=1 ;
  }
  for(;j<10;j+=2) {
    if(jeu->plateau[i][j].couleur == couleur)
      jeu->plateau[i][j].dame = 1;
  }
}
