#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>

void recherche_pion_qui_bouge(jeu_t * jeu,char * coup);
void recherche_pion_qui_bouge_noir(jeu_t * jeu,char * coup);
void recherche_pion_qui_bouge_blanc(jeu_t * jeu,char * coup);
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


    if(capture_est_possible_alea(jeu, &numero1, &numero2,deplacement)){
      int a,b,c,d;
      numero_coord(jeu,numero1,&a,&b);
      numero_coord(jeu,numero2,&c,&d);
      if(verifier_dame(&jeu,a,b) && dame_peut_capturer(&jeu,a,b,c,d)){
        capturer_avec_une_dame(&jeu,numero1,numero2,&a,&b,&c,&d);
        sprintf(deplacement,"%dx%d\n",numero1,numero2);
        printf("%dx%d\n",numero1,numero2);
        int n = 0;
        numero1 = numero2;
        a = c;
        b = d;
        while (captures_dame_possibles(&jeu,c,d,bourreaux,&n,&numero2))
        {
          numero_coord(jeu,numero2,&c,&d);
          capturer_avec_une_dame(&jeu,numero1,numero2,&a,&b,&c,&d);
           a = c;
           b = d;
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
      //recherche_pion_qui_bouge(&jeu,dep);
      srand(time(NULL));
      if(jeu.tour == BLANC){
        recherche_pion_qui_bouge_blanc(&jeu,dep);
      }
      else if(jeu.tour == NOIR){
        recherche_pion_qui_bouge_noir(&jeu,dep);
      }
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
  int choix[2];
  int nb_choix = 0;
  int alea;
 if(jeu->tour == NOIR){ 
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 10; j++) {

      if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion != 0 ){
        if(jeu->plateau[i][j].couleur == NOIR) {
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }
           if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          if (nb_choix > 0) {
           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
      
    }

  }
}
else{
  for (int i = 9; i >= 0; i--)
  {
    for (int j = 0; j <  10; j++)
    {
       if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion != 0 ){
        if(jeu->plateau[i][j].couleur == BLANC){
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }
          
          if(nb_choix > 0){

           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
    }
    
  }
}
}
void recherche_pion_qui_bouge_noir(jeu_t * jeu,char * coup){
  int numero1,numero2;
  int choix[2];
  int nb_choix = 0;
  int alea;
  if(jeu->tour == NOIR){ 
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 10; j++) {

      if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion != 0 ){
        if(jeu->plateau[i][j].couleur == NOIR) {
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }
           if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          if (nb_choix > 0) {
           srand(time(NULL));
           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
      
    }

  }
}
}




void recherche_pion_qui_bouge_blanc(jeu_t * jeu,char * coup){
   int numero1,numero2;
  int choix[2];
  int nb_choix = 0;
  int alea;
for (int i = 9; i >= 0; i--)
  {
    for (int j = 0; j <  10; j++)
    {
       if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion != 0 ){
        if(jeu->plateau[i][j].couleur == BLANC){
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            //sprintf(coup,"%d-%d",numero1,numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }
          
          if(nb_choix > 0){
          srand(time(NULL));
           alea = rand() % nb_choix;
           sprintf(coup,"%d-%d",numero1,choix[alea]);
           return;
          }

        }
      }
    }
    
  }
}  



int capture_est_possible_alea(jeu_t jeu, int * numero1, int * numero2,char * deplacement){
  int n = 0;
  tabi_t bourreaux[100];
  printf("Captures possibles %s :\n", jeu.tour == BLANC ? "\033[36;01mBlanc\033[00m" : "\033[31;01mNoir\033[00m");
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      //dames
      if(verifier_dame(&jeu,i,j)){
      if((jeu.tour == BLANC && jeu.plateau[i][j].couleur == BLANC) || (jeu.tour == NOIR && jeu.plateau[i][j].couleur == NOIR)){
          coord_numero(jeu, i, j, numero1);
          if (captures_dame_possibles(&jeu,i,j,bourreaux,&n,numero2))
            sprintf(deplacement,"%dx%d Dame \n", *numero1, *numero2);
          }
        }

      //Pions normaux
      if(jeu.plateau[i][j].pion && jeu.plateau[i][j].dame == 0){
        if((jeu.tour == BLANC && jeu.plateau[i][j].couleur == BLANC) || (jeu.tour == NOIR && jeu.plateau[i][j].couleur == NOIR)){
          coord_numero(jeu, i, j, numero1);
          if(pion_peut_capturer(jeu, *numero1, numero2)){
            sprintf(deplacement,"%dx%d\n", *numero1, *numero2);
            bourreaux[n].t[0] = *numero1;
            bourreaux[n].t[1] = *numero2;
            n++;
          }
        }
      }
    }
  }
  if(n == 0){
    printf("Aucune capture n'est possible.\n");
    return 0;
  }
  else if(n > 0){
    choisir_capture(jeu, bourreaux, n, numero1,numero2,deplacement);
    return 1;
  }

  return 1;
}


int choisir_capture_alea(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement){
  //char choix[50];
  int poubelle;
  int alea;
  srand(time(NULL));
  alea = rand() % n;
  //*numero1 = bourreaux[alea];
  putchar('\n');
  while(1){
    printf("Entrer la capture à effectuer : ");
    //scanf("%s", choix);
    sscanf(deplacement, "%dx%d", numero1,numero2);

    if(capture_appartient(jeu, bourreaux, taille, deplacement)){
      sscanf(deplacement, "%dx%d", numero1, numero2);
      return 1;
    }
  }
  return 0;
}