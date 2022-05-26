#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
int main(int argc, char ** argv){
  jeu_t jeu;
  int x1,y1,x2,y2,pion_noirs,pion_blancs, move ;
  initialiser_jeu(&jeu);
  afficher_jeu(jeu);
  jeu.tour = BLANC;
  tabi_t bourreaux[50];
  char deplacement[100];
  char suite[4];
  int numero1, numero2;
  int fd = open("deplacements.txt",O_WRONLY|O_TRUNC|O_CREAT, 0644);
	if (fd < 0)
	{
		perror("open");
	}
  while(jeu.en_cours){
    /* if dame 
    if peut_capturer dame
      capturer_dame 
    else pion 
    */  
   /*Captures */
    
    
    if(capture_est_possible(jeu, &numero1, &numero2)){
      int a,b,c,d;
      numero_coord(jeu,numero1,&a,&b);
      numero_coord(jeu,numero2,&c,&d);
      if(verifier_dame(&jeu,a,b) && dame_peut_capturer(&jeu,a,b,c,d)){
        capturer_avec_une_dame(&jeu,numero1,numero2,&a,&b,&c,&d);
        sprintf(deplacement,"%dx%d\n",numero1,numero2);
        int n = 0;
        numero1 = numero2;
        while (captures_dame_possibles(&jeu,c,d,bourreaux,&n,&numero2))
        {
          capturer_avec_une_dame(&jeu,numero1,numero2,&a,&b,&c,&d);
           numero1 = numero2;
           n = 0;
          sprintf(suite,"x%d\n",numero2);
          strcat(deplacement,suite);
        }
         write(fd,deplacement,strlen(deplacement)+1);
      }
      else{
        capturer(&jeu, numero1, numero2, &x1, &y1, &x2, &y2);
        deplacer_pion(&jeu,x1,y1,x2,y2);
        coord_numero(jeu, x2, y2, &numero1);
        write(fd,deplacement,strlen(deplacement)+1);
        while(pion_peut_capturer(jeu, numero1, &numero2)){
          capturer(&jeu, numero1, numero2, &x1, &y1, &x2, &y2);
          deplacer_pion(&jeu,x1,y1,x2,y2);
          coord_numero(jeu, x2, y2, &numero1);
          sprintf(suite,"x%d\n",numero2);
          strcat(deplacement,suite);
        }
        sprintf(deplacement,"%dx%d\n",numero1,numero2);

      }

    }
    /*Deplacements normaux*/
    else{
      while((move = saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu.tour, &jeu)));
      if(jeu.plateau[x1][y1].dame ==1 ){
        deplacer_dame(&jeu,x1,y1,x2,y2);
      }
      else
      deplacer_pion(&jeu,x1,y1,x2,y2);
    }
    write(fd,deplacement,strlen(deplacement)+1);
    faire_dames(&jeu);
    afficher_jeu(jeu);
    jeu.nb_coups++;
    jeu.tour = jeu.nb_coups % 2 == 0 ? BLANC : NOIR;
    pion_noirs = compter_pions(NOIR,&jeu);
    pion_blancs = compter_pions(BLANC,&jeu);
    printf("Nb de coups : %d.\n",jeu.nb_coups);
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
