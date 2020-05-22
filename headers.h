#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <string.h>

#define zero 0 //zero pouvant etre changé facilment pour pouvoir déplacer le damier si besoin (titre...)

#define dimcase 100 //dimension des cases du damier facilement modifiable pour pouvoir changer rapidement la taille du plateau de jeu

#define DELAY 500 //en milisec

#define DETAIL 0 //Mettre 1 si on souhaite obtenir plus de detail concernant le fonctionnement

typedef struct POSITION POSITION;

struct POSITION
{
	int x; //colonnes
	int y; //lignes
};

void REMPLISSAGE_ECHIQUIER(int TAB[8][8]);
void REMPLISSAGE_MATRICE(int TAB[64][64]);
void REMPLISSAGE_MARQUE(int marque[64]);
void REMPLISSAGE_predecesseur(int predecesseur[64]);

void AFFICHER_ECHIQUIER(int TAB[8][8]);
void AFFICHER_MAT(int TAB[64][64]);
void AFFICHER_TAB(int line, int TAB[]);

void FLOYD(int G[64][64], int L[64][64], int P[64][64]);
void GENERER_GRAPHE(int echiquier[8][8], int G[64][64]);
void ECHIQUIER_DEGRE(int G[64][64], int degre[64], int echiquier[8][8]);
void PLUS_COURT_CHEMIN(int P[64][64], int predecesseur[64], int depart, int arrivee);
void AFFICHER_PLUS_COURT_CHEMIN(int predecesseur[64]);
void viderBuffer();
void ANALYSE1();
void ANALYSE2();

POSITION CONVERTIR_CASE_POSITION(int cases, int TAB[8][8]);
void ECHIQUIER_DEGRES(int G[64][64], int degre[64], int echiquier[8][8]);
void REMPLISSAGE_VOISIN(int voisin[8]);
void PARCOURS(int G[64][64], int echiquier[8][8], int echiquier_degre[8][8], int chemin[64], int marque[64], int voisin[8], int depart);
void REMPLISSAGE_CHEMIN_ECHIQUIER(int echiquier[8][8], int chemin[64], int echiquier_chemin[8][8]);
void AFFICHER_CHEMIN(int chemin[64]);


/**********************  SDL ************************************************************/

void afficher_image(SDL_Surface *image, SDL_Surface *ecran, int x, int y);
//permet d'afficher une image aux coordonées choisies

void affiche_case(SDL_Surface *rect, SDL_Surface *ecran, int x, int y);
//afficher les cases noires du damier

void pause();
//permet à la fenêtre de restée afficher jusqu'a cliquer sur la croix de fermeture

void sdl_cheminLePlusCourt(SDL_Surface* ecran, int x, int y,int compt);
//permet d'afficher les cases du chemin comme parcourues

void sdl_toutParcourir (SDL_Surface* ecran,int x, int y, int compt);
//permet d'afficher les cases du parcours total comme parcourues
