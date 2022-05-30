#include <stdio.h>
#include <stdlib.h>
#include "dames.h"
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
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
  jeu->tour = BLANC;
}


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
          if(jeu.plateau[i][j].dame == 1) {
          printf("\033[31;01mD\033[00m ");
          }
          else
          printf("\033[31;01mN\033[00m ");

          if(i % 2 != 0){
            putchar(' ');
          }
        }
        else if(jeu.plateau[i][j].couleur == BLANC){
          if(i % 2 == 0){
            putchar(' ');
          }
          if(jeu.plateau[i][j].dame == 1){
          printf("\033[36;01mD\033[00m ");
          }
          else
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
    //scanf("%s", deplacement);
    int mouvement = 3;
    int numero1, numero2;
    int x,y,z,b;
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
      numero_coord(*jeu,numero1,&x,&y);
      numero_coord(*jeu,numero1,&z,&b);
      if(jeu->plateau[x][y].dame == 1){
         if (dame_peut_capturer(*jeu,x,y,z,b)){
           capturer_avec_une_dame(jeu,numero1,numero2,&x,&y,&z,&b);
         }
         else return 0;
      }
      if(verifier_capture(*jeu, numero1, numero2)){
        capturer(jeu, numero1, numero2, x1, y1, x2, y2);
        return 0;
      }
      return 1;
    }
    if(mouvement == 3){
      printf("Il ne s'agit ni d'un déplacement ni d'une capture.\n");
      printf("%s\n",deplacement);
      return 1;
    }
    return 1;
}

void capturer(jeu_t * jeu, int numero1, int numero2, int * x1, int * y1, int * x2, int * y2){
  numero_coord(*jeu, numero1, x1, y1);
  numero_coord(*jeu, numero2, x2, y2);
  if(jeu->plateau[*x1][*y1].dame == 1){
    return capturer_avec_une_dame(jeu,numero1,numero2,x1,y1,x2,y2);
  }
  int k,l;
  while (*x1 != *x2 && *y1 != *y2)
  {
     if(*x1 > *x2 && *y1 > *y2 ){
      k = *x1 - 1;
      l = *y1 - 1;
     }
    else if(*x1 > *x2 && *y1 < *y2 ){
      k = *x1 - 1;
      l = *y1 + 1;
    }
  
 
    else if( *x1 < *x2 && *y1 > *y2){
      k = *x1 + 1;
      l = *y1 - 1;
     
    }
    else if( *x1 < *x2 && *y1 < *y2){
      k = *x1 + 1;
      l = *y1 + 1;
    }
    deplacer_pion(jeu,*x1,*y1,k,l);
    *x1 = k;
    *y1 = l;
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
  //Dames
  if(jeu.plateau[x1][y1].pion && jeu.plateau[x1][y1].dame == 1){
    return peut_deplacer_dame(jeu,x1,y1,x2,y2);
  }
  //Pions normaux
  if(jeu.plateau[x1][y1].pion && jeu.plateau[x1][y1].dame == 0) {
    if(jeu.plateau[x1][y1].couleur == BLANC && jeu.tour == 1 || jeu.plateau[x1][y1].couleur == NOIR && jeu.tour == 0){
      if(jeu.plateau[x2][y2].pion == 0){
        if(jeu.plateau[x1][y1].couleur == NOIR){
          if((x2 - x1 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            return 1;
          }
          return 0;
        }
        else if(jeu.plateau[x1][y1].couleur == BLANC){
          if((x1 - x2 == 1) && (y2 - y1 == 1 || y2 - y1 == -1) && (x1 != x2) && (y1 != y2) && (x1 != -1) && (y1 != -1) && (x2 != -1) && (y2 != -1)){
            return 1;
          }
          return 0;
        }
      }
      return 0;
    }
    return 0;
  }
  return 0;
}

int verifier_capture(jeu_t jeu, int numero1, int numero2){
  int x1, y1, x2, y2,k,l;
  numero_coord(jeu, numero1, &x1, &y1);
  numero_coord(jeu, numero2, &x2, &y2);
  if(jeu.plateau[x1][y1].pion == 1 &&  jeu.plateau[x1][y1].dame == 1){
    return verfier_capture_dame(jeu,numero1,numero2);
  }
  if(jeu.plateau[x1][y1].pion == 1 && jeu.plateau[x1][y1].dame == 0 ){
    if(abs(x2-x1) == 2 &&  abs(y2-y1) == 2) {
      while (x1 != x2 && y1 != y2)
      {
        if(x1 > x2 && y1 > y2){
          k = x1 - 1;
          l = y1 -1 ;
        }
         if(x1 > x2 && y1 < y2){
          k = x1 - 1;
          l = y1 + 1;
        }
         if(x1 < x2 && y1 > y2){
          k = x1 + 1;
          l = y1 - 1;
        }
         if(x1 < x2 && y1 < y2){
          k = x1 +1;
          l = y1 +1 ;
        }
        if(k == x2 && l == y2){
          return jeu.plateau[k][l].pion == 0;
        }

        if((jeu.plateau[k][l].pion == 1 && (jeu.plateau[x1][y1].couleur == jeu.plateau[k][l].couleur)) || jeu.plateau[k][l].pion == 0 ){
          return 0;
        }
        else if(jeu.plateau[k][l].pion == 1 && (jeu.plateau[x1][y1].couleur != jeu.plateau[k][l].couleur))
        {
          deplacer_pion (&jeu,x1,y1,k,l);
          x1 = k;
          y1 = l;
        }
     }
    }    
  }
  return 0;
}

void coord_numero(jeu_t jeu, int x, int y, int * numero){
  *numero = jeu.plateau[x][y].numero;
}

int pion_peut_capturer(jeu_t jeu, int numero, int * capture){
  int x, y,k,l;
  numero_coord(jeu, numero, &x, &y);
  int capture1, capture2, capture3, capture4;

  if(jeu.plateau[x][y].pion){
    coord_numero(jeu, x + 2, y - 2, &capture1);
    coord_numero(jeu, x + 2, y + 2, &capture2);
    coord_numero(jeu, x - 2, y - 2, &capture3);
    coord_numero(jeu, x - 2, y + 2, &capture4);
    if(verifier_capture(jeu, numero, capture1)){
      *capture = capture1;
      return 1;
    }
    else if(verifier_capture(jeu, numero, capture2)){
      *capture = capture2;
      return 1;
    }
    else if(verifier_capture(jeu, numero, capture3)){
      *capture = capture3;
      return 1;
    }
    else if(verifier_capture(jeu, numero, capture4)){
      *capture = capture4;
      return 1;
    }

  }

  return 0;
}

int capture_est_possible(jeu_t jeu, int * numero1, int * numero2,char * deplacement){
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
    choisir_capture(jeu, bourreaux, n, numero1,numero2,deplacement);
    return 1;
  }

  return 1;
}

int choisir_capture(jeu_t jeu, tabi_t bourreaux[], int taille, int * numero1,int *numero2,char * deplacement){
  //char choix[50];
  int poubelle;
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

int capture_appartient(jeu_t jeu, tabi_t bourreaux[], int taille, char capture[]){
  int numero1, numero2, poubelle1, poubelle2;
  for(int i = 0; i < taille; i++){
    sscanf(capture, "%dx%d", &numero1, &numero2);
    if(bourreaux[i].t[0] == numero1){
      return 1;
    }
  }
  return 0;
}


//PARTIE DAME



//on vérifie si la pièce est une dame ou non
int verifier_dame(jeu_t * jeu, int x, int y){
  if(jeu->plateau[x][y].pion == 1 && jeu->plateau[x][y].dame == 1)
    return 1;
  return 0;
}

//Transformer un pion en une dame
void faire_dames(jeu_t * jeu){
  int couleur = NOIR;
  int i = 9;
  int j = 0;
  for(;j<10;j+=2) {
    if(jeu->plateau[i][j].couleur == couleur)
      jeu->plateau[i][j].dame = 1;
  }
  couleur = BLANC;
  i = 0;
  j = 1;
  for(;j<10;j+=2) {
    if(jeu->plateau[i][j].couleur == couleur)
      jeu->plateau[i][j].dame = 1;
  }
}

//On vérifie si la dame peut aller à cette case
int peut_deplacer_dame(jeu_t jeu, int x1, int y1, int x2, int y2){
  //si ce n'est pas une dame
  if(jeu.plateau[x1][y1].dame != 1)
    return 0;
  //si la case de départ est vide
  if(jeu.plateau[x1][y1].pion == 0)
    return 0;
  //si la case d'arrivée n'est pas vide
  //si le coup n'est pas une diagonal
  //if(abs(x1-x2)!=abs(y1-y2))

  int i = x1;
  int j = y1 ;
  int k,l;
  // on parcourt toutes le cases de la case courante à la case destination
  while (x1 != x2 && y1 != y2)
  {
       if (x2 < i)
       {
         k =i-1;
       }
       else
       {
         k = i+1;
       }
       if (y2 < j)
       {
         l =j-1;
       }
       else
       {
         l = j+1;
       }


       if(jeu.plateau[k][l].pion == 1 ){
         return 0;
       }
       x1 = k;
       y1 = l;

  }

  return (jeu.plateau[x2][y2].pion == 0);
}


//On déplace la dame d'une case (x1,y1) à une case (x2,y2)
void deplacer_dame(jeu_t *jeu, int x1,int y1, int x2, int y2){
    jeu->plateau[x2][y2].dame =  jeu->plateau[x1][y1].dame;
    jeu->plateau[x1][y1].dame = 0;
    jeu->plateau[x2][y2].pion = jeu->plateau[x1][y1].pion;
    jeu->plateau[x1][y1].pion = 0;
    jeu->plateau[x2][y2].couleur = jeu->plateau[x1][y1].couleur;
  return;
}



//toute les conditions sont remplis pour que la dame capture
int dame_peut_capturer(jeu_t  jeu, int x1, int y1, int x2, int y2){
  return jeu.plateau[x2][y2].pion == 0;
}


//Dernière modif : penser à ajouter les déclarations dans le .h
//afficher les captures possibles de la dame
void capturer_avec_une_dame(jeu_t * jeu, int numero1, int numero2, int * x1, int * y1, int * x2, int * y2){
    int k,l;
     while (*x1 != *x2 && *y1 != *y2)
  {
     if(*x1 > *x2 && *y1 > *y2 ){
      k = *x1 - 1;
      l = *y1 - 1;
     }
    else if(*x1 > *x2 && *y1 < *y2 ){
      k = *x1 - 1;
      l = *y1 + 1;
    }
  
 
    else if( *x1 < *x2 && *y1 > *y2){
      k = *x1 + 1;
      l = *y1 - 1;
     
    }
    else if( *x1 < *x2 && *y1 < *y2){
      k = *x1 + 1;
      l = *y1 + 1;
    }
    deplacer_dame(jeu,*x1,*y1,k,l);
    *x1 = k;
    *y1 = l;
  }
    
}


// Signé Adbou Lahat
//Dernière modif : penser à ajouter les déclarations dans le .h
//afficher les captures possibles de la dame
int captures_dame_possibles(jeu_t * jeu, int x1, int  y1, tabi_t boureaux[],int *n,int *capture) {
  int hg,hd,bg,bd,res,n1;
  /*if(dame_peut_capturer(jeu, *x1, *y1, *x2, *y2)){*/
    coord_numero(*jeu,x1,y1,&n1);
    boureaux[*n].t[0]= n1;
    hg = verfier_haut_gauche(jeu,x1,y1,capture,n,boureaux,n1);
    if(hg == 1){
       boureaux[*n].t[1]= *capture;
      *n = *n +1;
    }
    boureaux[*n].t[0]= n1;
    hd = verfier_haut_droite(jeu,x1,y1,capture,n,boureaux,n1);
     if(hd == 1){
       boureaux[*n].t[1]= *capture;
      *n = *n +1;
    }
    boureaux[*n].t[0]= n1;
    bg = verfier_bas_gauche(jeu,x1,y1,capture,n,boureaux,n1);
     if(bg == 1){
       boureaux[*n].t[1]= *capture;
      *n = *n +1;
    }
    boureaux[*n].t[0]= n1;
    bd = verfier_bas_droite(jeu,x1,y1,capture,n,boureaux,n1);
     if(bd == 1){
       boureaux[*n].t[1]= *capture;
      *n = *n +1;
    }
    res = hg + hd + bg + bd;
    return  res;


}

int verfier_haut_gauche(jeu_t *jeu,int x1,int y1,int * capture, int *n,tabi_t boureaux[],int n1){
  int i = x1;
  int j = y1;
  int n2;
  i--;
  j--;
   while (i > 0 && j > 0)
    {
      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur == jeu->plateau[i][j].couleur ){
        return 0;
      }
      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur != jeu->plateau[i][j].couleur ){
        if(dame_peut_capturer(*jeu,x1,y1,i-1,j-1)){
         coord_numero(*jeu,i-1,j-1,&n2);
         printf("%dx%d\n",n1,n2);
         *capture = n2;
         return 1;
        }
        break;
      }
    i--;
    j--;

    }
    return 0;
}
int verfier_haut_droite(jeu_t *jeu,int x1,int y1,int * capture,int * n,tabi_t boureaux[],int n1){
  int i = x1;
  int j = y1;
  int n2;
   i--;
   j++;

   while (i > 0 && j < 10)
    {
      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur == jeu->plateau[i][j].couleur ){
        return 0;
      }
      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur != jeu->plateau[i][j].couleur){
        if(dame_peut_capturer(*jeu,x1,y1,i-1,j+1)){
         coord_numero(*jeu,i-1,j+1,&n2);
         printf("%dx%d\n",n1,n2);
         *capture = n2;
         return 1;
        }
        break;
      }

      i--;
      j++;

    }
    return 0;
}
int verfier_bas_gauche(jeu_t *jeu,int x1,int y1,int * capture,int * n,tabi_t boureaux[],int n1){
   int i = x1;
  int j = y1;
  int n2;
   i++;
   j--;
   while (i < 10 && j > 0)
    {

      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur == jeu->plateau[i][j].couleur ){
        return 0;
      }

      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur != jeu->plateau[i][j].couleur){
        if(dame_peut_capturer(*jeu,x1,y1,i+1,j-1)){
         coord_numero(*jeu,i+1,j-1,&n2);
         printf("%dx%d\n",n1,n2);
         *capture = n2;
         return 1;
        }
        break;
      }
      i++;
      j--;

    }
    return 0;
}
int verfier_bas_droite(jeu_t *jeu,int x1,int y1,int * capture,int * n,tabi_t boureaux[],int n1){
   int i = x1;
   int j = y1;
   int n2;
       i++;
       j++;

   while (i < 10 && j < 10)
    {
      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[x1][y1].couleur == jeu->plateau[i][j].couleur ){
        return 0;
      }

      if(jeu->plateau[i][j].pion == 1 && jeu->plateau[i][j].couleur != jeu->plateau[x1][y1].couleur){
        if(dame_peut_capturer(*jeu,x1,y1,i+1,j+1)){
         coord_numero(*jeu,i+1,j+1,&n2);
         printf("%dx%d\n",n1,n2);
         *capture = n2;
         return 1;
        }
        break;
      }
       i++;
       j++;

    }
    return 0;
}
//on veut le plus long chemin pour le bot
int verfier_capture_dame(jeu_t jeu,int num1,int num2){
  int k,l,x1,y1,x2,y2;
  numero_coord(jeu,num1,&x1,&y1);
  numero_coord(jeu,num2,&x2,&y2);
  while (x1 != x2 && y1 != x2)
  {
      if(x1 > x2 && y1 > y2){
          k = x1 - 1;
          l = y1 -1 ;
        }
        else if(x1 > x2 && y1 < y2){
          k = x1 - 1;
          l = y1 + 1;
        }
       else  if(x1 < x2 && y1 > y2){
          k = x1 + 1;
          l = y1 - 1;
        }
        else if(x1 < x2 && y1 < y2){
          k = x1 +1;
          l = y1 +1 ;
        }
      if(jeu.plateau[k][l].couleur == jeu.plateau[x1][y1].couleur){
        return 0;
      }
      else if (jeu.plateau[k][l].pion == 0 || jeu.plateau[k][l].couleur != jeu.plateau[x1][y1].couleur ) {
          deplacer_dame(&jeu,x1,y1,x2,y2);
      }
      x1 = k;
      y1 = l;  
  }
 return 1; 
}