#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


void recherche_pion_qui_bouge(jeu_t * jeu,char * coup);

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


    if(capture_est_possible(jeu, &numero1, &numero2,deplacement)){
      int a,b,c,d;
      numero_coord(jeu,numero1,&a,&b);
      numero_coord(jeu,numero2,&c,&d);
      if(verifier_dame(&jeu,a,b) && dame_peut_capturer(&jeu,a,b,c,d)){
        capturer_avec_une_dame(&jeu,numero1,numero2,&a,&b,&c,&d);
        sprintf(deplacement,"%dx%d\n",numero1,numero2);
        printf("%dx%d\n",numero1,numero2);
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
        printf("%dx%d\n",numero1,numero2);

      }

    }
    /*Deplacements normaux*/
    else{
      //pour recuperer le deplacement à faire
      char dep[100];
      recherche_pion_qui_bouge(&jeu,dep);
      printf("pion qui peut bouger : %s\n",dep );
      while((move = saisir_deplacement(dep, &x1, &y1, &x2, &y2, jeu.tour, &jeu)));
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



void recherche_pion_qui_bouge(jeu_t * jeu,char * coup){
  int numero1,numero2;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion != 0 ){
        if(jeu->plateau[i][j].couleur == BLANC){
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d\n",numero1,numero2);
            return;
          }
          else if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d\n",numero1,numero2);
            return;
          }

        }
        else {
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d\n",numero1,numero2);
            return;
          }else if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d\n",numero1,numero2);
            return;
          }
        }
      }
    }
  }
}
