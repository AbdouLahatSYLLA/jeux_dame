/* fichiers de la bibliothèque standard */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dames.h"
#include <stdint.h>
#include <string.h>
/* bibliothèque standard unix */
#include <unistd.h> /* close, read, write */
#include <sys/types.h>
#include <sys/socket.h>
/* spécifique à internet */
#include <arpa/inet.h> /* inet_pton */
#include <pthread.h>
#include <semaphore.h>
#include "reseau.h"

//Version bot
 void jouer(jeu_t * jeu,char * deplacement,uint8_t * octets, int * n){
     int x1,x2,y1,y2,numero1,numero2,move;
     int x = 0;
     tabi_t bourreaux[50];
     char copie[100];
     char suite[50];
     if(capture_est_possible_alea(*jeu, &numero1, &numero2,deplacement)){
      int a,b,c,d;
      numero_coord(*jeu,numero1,&a,&b);
      numero_coord(*jeu,numero2,&c,&d);
      if(verifier_dame(jeu,a,b) && dame_peut_capturer(*jeu,a,b,c,d)){
        capturer_avec_une_dame(jeu,numero1,numero2,&a,&b,&c,&d);
        int n = 0;
        numero1 = numero2;
        a = c;
        b = d;
        while (captures_dame_possibles(jeu,a,b,bourreaux,&n,&numero2))
        {
          printf("%dx%d\n",numero1,numero2);
          sprintf(suite,"x%d",numero2);
          strcat(deplacement,suite);
          numero_coord(*jeu,numero2,&c,&d);
          capturer_avec_une_dame(jeu,numero1,numero2,&a,&b,&c,&d);
          a = c;
          b = d;
           numero1 = numero2;
           n = 0;
        }
      }
      else{
        capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
        coord_numero(*jeu, x2, y2, &numero1);
        while(pion_peut_capturer(*jeu, numero1, &numero2)){
          sprintf(suite,"x%d",numero2);
          strcat(deplacement,suite);
          capturer(jeu, numero1, numero2, &x1, &y1, &x2, &y2);
          coord_numero(*jeu, x2, y2, &numero1);
        }
      }
        strcpy(copie,deplacement);
        ajouter_capture(octets,n,copie);
    }
    /*Deplacements normaux*/
    else{
      
      move_alea(*jeu,jeu->tour,deplacement);
      if (saisir_deplacement(deplacement, &x1, &y1, &x2, &y2, jeu->tour, jeu)) {
        strcpy(deplacement,"PERDU");
      }
      else{
      if(jeu->plateau[x1][y1].dame ==1 ){
        deplacer_dame(jeu,x1,y1,x2,y2);
      }
      else
      deplacer_pion(jeu,x1,y1,x2,y2);
      strcpy(copie,deplacement);
      ajouter_deplacement(octets,n,copie);
     // printf("Après ajout %s\n",copie);
      }
    }
    printf("Mon choix %s\n",deplacement);
    jeu->nb_coups++;
    jeu->tour = jeu->nb_coups % 2 == 0 ? BLANC : NOIR;
 }


void recherche_pion_qui_bouge(jeu_t * jeu,char * coup){
  int numero1,numero2;
  coup = malloc(100);

  for (int i = 0; i < 9; i++) {
    for (int j = 0; j < 9; j++) {
      if(jeu->tour == jeu->plateau[i][i].couleur){
        if(jeu->plateau[i][i].couleur == BLANC){
          if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
        }
         if(jeu->plateau[i][i].couleur == NOIR){
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
          if(jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            sprintf(coup,"%d-%d",numero1,numero2);
            printf(coup,"%d-%d",numero1,numero2);
            break;
          }
        }
      }
    }
  }
}


void recherche_pion_qui_bouge_noir(jeu_t * jeu,char * coup){
  int numero1,numero2;
  int choix[4];
  int nb_choix = 0;
  int alea;
  if(jeu->tour == NOIR){
  for (int i = 0; i < 10; i++) {

    for (int j = 0; j < 10; j++) {

      if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion > 0 ){
        if(jeu->plateau[i][j].couleur == NOIR) {
          if(jeu->plateau[i][j].dame == 0){
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }
           if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          }
          else if(jeu->plateau[i][j].dame == 1){
          if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }
           if (jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }

           if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
             choix[nb_choix] = numero2;
             nb_choix++;
          }

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
       if(jeu->tour == jeu->plateau[i][j].couleur && jeu->plateau[i][j].pion > 0 ){
        if(jeu->plateau[i][j].couleur == BLANC){
          if(jeu->plateau[i][j].dame == 0){
          if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

          }
         else if(jeu->plateau[i][j].dame == 1){
           if(jeu->plateau[i-1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i-1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i-1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i+1][j+1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j+1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

           if(jeu->plateau[i+1][j-1].pion == 0){
            coord_numero(*jeu,i,j,&numero1);
            coord_numero(*jeu,i+1,j-1,&numero2);
            printf("%d-%d\n",numero1,numero2);
            choix[nb_choix] = numero2;
            nb_choix++;
          }

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
            printf("%dx%d Dame\n",*numero1,*numero2);
            sprintf(deplacement,"%dx%d", *numero1, *numero2);
          }
        }

      //Pions normaux
      if(jeu.plateau[i][j].pion && jeu.plateau[i][j].dame == 0){
        if((jeu.tour == BLANC && jeu.plateau[i][j].couleur == BLANC) || (jeu.tour == NOIR && jeu.plateau[i][j].couleur == NOIR)){
          coord_numero(jeu, i, j, numero1);
          if(pion_peut_capturer(jeu, *numero1, numero2)){
            sprintf(deplacement,"%dx%d", *numero1, *numero2);
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
    choisir_capture_alea(jeu, bourreaux, n, numero1,numero2,deplacement);
    return 1;
  }

  return 1;
}

int choisir_capture_alea(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement){

  int poubelle;
  int alea;
  srand(time(NULL));
  alea = rand() % taille;
  *numero1 = bourreaux[alea].t[0];
  *numero2 = bourreaux[alea].t[1];
  sprintf(deplacement, "%dx%d", *numero1, *numero2);
   if(capture_appartient(jeu, bourreaux, taille, deplacement)){
      return 1;
    }
  putchar('\n');

  return 0;
}


void ajouter_deplacement(uint8_t * oct,int * pos,char * deplacement){
    char * dep = strtok(deplacement,"-");
    while (dep != NULL)
{
    oct[*pos] = atoi(dep)+128;
    *pos = *pos +1;
    dep = strtok(NULL,"-");

}
}
void ajouter_capture(uint8_t * oct,int * pos,char * capture){
    char *dep = strtok(capture,"x");
    while (dep != NULL){
    oct[*pos] =  atoi(dep);
    *pos = *pos + 1;
     dep = strtok(NULL,"x");
}
oct[*pos -1 ] = oct[*pos -1] +128;
}

void copier_ipv6(uint8_t * oct,int * pos,unsigned char * addr){
    for (int i = 0; i <16 ; i++){
      oct[*pos] = addr[i];
      *pos = *pos + 1;
    }
}



int tester_coup(jeu_t jeu,char * coup){
  char test[100];
  int num1,num2,x1,y1,x2,y2;
  strcpy(test,coup);
  if(est_deplacement(coup)){
    sscanf(test,"%d-%d",&num1,&num2);
    if(verifier_deplacement(jeu,num1,num2)){
      return 1;
    }
  }
  else if(est_capture(coup)){
    int x1,y1;
    char *tmp = strtok(test,"x");
    num1 = atoi(tmp);
    while (tmp != NULL)
    {
      tmp = strtok(NULL,"x");
      if(tmp == NULL){
        break;
      }
      num2 = atoi(tmp);
       printf("Capture a tester %dx%d",num1,num2);
       numero_coord(jeu,num1,&x1,&y1);
       numero_coord(jeu,num2,&x2,&y2);

       if(!verifier_capture(jeu,num1,num2)){
       return 0;
      }
        capturer(&jeu,num1,num2,&x1,&y1,&x2,&y2);
        //faire_dames(&jeu);
        puts("Capture réussie");
        coord_numero(jeu,x2,y2,&num1);

    }
    return 1;
  }
  return 0;
}

void appliquer_coup(jeu_t *jeu,char * coup){
  char test[100];
  int num1,num2,x1,y1,x2,y2;
  strcpy(test,coup);
  if(est_deplacement(test)){
    sscanf(test,"%d-%d",&num1,&num2);
      numero_coord(*jeu,num1,&x1,&y1);
      numero_coord(*jeu,num2,&x2,&y2);
      if(jeu->plateau[x1][y1].dame == 1){
        deplacer_dame(jeu,x1,y1,x2,y2);
      }
      else
      {
        deplacer_pion(jeu,x1,y1,x2,y2);
      }

  }
  else if(est_capture(test)){
    char *tmp = strtok(test,"x");
    num1 = atoi(tmp);
    while (tmp != NULL)
    {
       tmp = strtok(NULL,"x");

      if(tmp == NULL){
        break;
      }
      num2 = atoi(tmp);
       numero_coord(*jeu,num1,&x1,&y1);
       numero_coord(*jeu,num2,&x2,&y2);
        capturer(jeu,num1,num2,&x1,&y1,&x2,&y2);
        coord_numero(*jeu,x2,y2,&num1);
    }
  }
  jeu->nb_coups++;
  jeu->tour = jeu->nb_coups % 2 == 0 ? BLANC : NOIR;
}
int est_deplacement (char * coup){
  char * c = coup;
  int cpt = 0;
  while (*c != '\0')
  {
    if(*c =='x'){
    return 0;      
    }
    if(*c == '-'){
      cpt++;
    }
    c++;
  }
  if (cpt > 1 || cpt == 0){
    return 0;
  }
  return 1;
}

int est_capture(char * coup){
  char * c = coup;
    int cpt = 0;
  while (*c != '\0')
  {
    if(*c =='x'){
      cpt++;
    }
    if(*c == '-'){
      return 0;
    }
    c++;
  }
  return cpt;
}

void remplir_fin_de_chaine(char * c, int taille){
  int k = strlen(c);
  for ( k; k < taille; k++)
  {
    c[k]= '\0';
  }
}

void remplir_rapport(char * dep, uint8_t * oct , int *n){
    char test[100];
    strcpy(test,dep);
    if(est_deplacement(dep)){
      ajouter_deplacement(oct,n,test);
    }
    else if(est_capture(dep)){
      ajouter_capture(oct,n,test);
    }
  }

  void  move_alea(jeu_t jeu, int couleur,char * s){
  int tab1[50];
  int tab2[50];
  int n = 0, numero1, numero2;
  for(int i = 0; i < 10; i++){
    for(int j = 0; j < 10; j++){
      coord_numero(jeu, i, j, &numero1);
      if(jeu.plateau[i][j].pion == 1){
        if(jeu.plateau[i][j].couleur == couleur){
          if(jeu.plateau[i][j].couleur == BLANC){
            if(jeu.plateau[i - 1][j + 1].pion == 0){
              coord_numero(jeu, i - 1, j + 1, &numero2);
              tab1[n] = numero1;
              tab2[n] = numero2;
              n++;
            }
            if(jeu.plateau[i - 1][j - 1].pion == 0){
              coord_numero(jeu, i - 1, j - 1, &numero2);
              tab1[n] = numero1;
              tab2[n] = numero2;
              n++;
            }
          }
          if(jeu.plateau[i][j].couleur == NOIR){
            if(jeu.plateau[i + 1][j + 1].pion == 0){
              coord_numero(jeu, i + 1, j + 1, &numero2);
              tab1[n] = numero1;
              tab2[n] = numero2;
              n++;
            }
            if(jeu.plateau[i + 1][j - 1].pion == 0){
              coord_numero(jeu, i + 1, j - 1, &numero2);
              tab1[n] = numero1;
              tab2[n] = numero2;
              n++;
            }
          }
        }
      }
    }
  }
  srandom(time(NULL));
    if(n > 0){
  int alea = random() % n;
  sprintf(s,"%d-%d",tab1[alea],tab2[alea]);
    }
}

