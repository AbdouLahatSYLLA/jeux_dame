#include <stdio.h>
#include <stdlib.h>
#include "dames.h"

int main(int argc, char ** argv){
  jeu_t jeu;
  int x1,y1,x2,y2,pion_noirs,pion_blancs, move ;
  initialiser_jeu(&jeu);
  afficher_jeu(jeu);
  jeu.tour = BLANC;
  char deplacement[100];
  int numero1, numero2;
  while(jeu.en_cours){
    if(capture_est_possible(jeu, &numero1, &numero2,jeu.tour)){
      capturer(&jeu, numero1, numero2, &x1, &y1, &x2, &y2);
      deplacer_pion(&jeu,x1,y1,x2,y2);
    }
    else{
      while((move = saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu.tour, &jeu)));
      deplacer_pion(&jeu,x1,y1,x2,y2);
    }
    afficher_jeu(jeu);
    jeu.nb_coups++;
    jeu.tour = jeu.nb_coups % 2 == 0 ? BLANC : NOIR;
    pion_noirs = compter_pions(NOIR,&jeu);
    pion_blancs = compter_pions(BLANC,&jeu);
    printf("%d\n",jeu.nb_coups);
    if(pion_noirs == 0){
      printf("Victoire des blancs\n");
      jeu.en_cours = 0;
      break;
    }
    if(pion_blancs == 0){
      printf("Victoire des noirs\n");
      jeu.en_cours = 0;
      break;
    }
    if(jeu.nb_coups == 100){
      printf("Egalite\n");
      jeu.en_cours = 0;
      break;
    }
  }
  return 0;
}
