#ifndef __DAMES__
#define __DAMES__

#define NOIR 0
#define BLANC 1
#define EGALITE 2

typedef struct{
  int pion;
  int couleur;
  int dame;
  int numero;
}case_t;

typedef struct{
  int ligne;
  int colonne;
}postion;

typedef struct{
  case_t plateau[10][10];
  int en_cours;
  int tour;
  int nb_coups;
} jeu_t;

void initialiser_jeu(jeu_t * jeu);
void verifier_dame(jeu_t * jeu);
void deplacer_pion (jeu_t * jeu ,int x1, int y1, int x2, int y2);
int compter_pions(int couleur,jeu_t *jeu);
void afficher_jeu(jeu_t jeu);
int saisir_deplacement(char* deplacement,int * x1, int * y1, int * x2, int * y2, int tour, jeu_t * jeu);
void numero_coord(jeu_t jeu, int numero, int * x, int * y);
void coord_numero(jeu_t jeu, int x, int y, int * numero);
int verifier_deplacement(jeu_t jeu, int numero1, int numero2);
int verifier_capture(jeu_t jeu, int numero1, int numero2, int affichage);
int pion_peut_capturer(jeu_t jeu, int numero, int * capture);
int capture_est_possible(jeu_t jeu, int * numero1, int * numero2);

#endif
