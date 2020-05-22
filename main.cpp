#include "headers.h"

int main(int argc, char const *argv[])
{
	system("xdotool key Ctrl+0"); //A chaque lancement du programme, on reinitialise le zoom du terminal
	system("clear");//Permet d'effacer le terminal
	//system("xdotool key Ctrl+minus"); //Permet de reduire la police
	//system("xdotool key Ctrl+minus");
	system("resize -s 200 310"); //Permet de redimensionner le terminal

	//Declaration des variables
	int depart = -1;
	int arrivee = -1;

	int echiquier[8][8];
	int echiquier_degre[8][8];
	int mat_adjacence[64][64];
	int L[64][64];
	int P[64][64];
	int predecesseur[64];
	int degre[64];
	int marque[64];
	int voisin[8];
	int chemin[64];
	int echiquier_chemin[8][8];

	//Initialisation des tableaux
	REMPLISSAGE_ECHIQUIER(echiquier);
	REMPLISSAGE_ECHIQUIER(echiquier_degre);
	REMPLISSAGE_MATRICE(mat_adjacence);
	REMPLISSAGE_MATRICE(L);
	REMPLISSAGE_MATRICE(P);
	REMPLISSAGE_predecesseur(predecesseur);
	REMPLISSAGE_MARQUE(degre);
	REMPLISSAGE_MARQUE(marque);
	REMPLISSAGE_MARQUE(chemin);
	REMPLISSAGE_VOISIN(voisin);

	//Permet la conception de la matrice d'adjacence
	GENERER_GRAPHE(echiquier, mat_adjacence);

	//Algorithme de FLOYD-WARSHALL 
	//Permet d'obtenir la matrice L : des longueurs des plus courts chemins
	//Permet d'obtenir la matrice G : des predecesseurs pour une case de départ donnée
	FLOYD(mat_adjacence, L, P);

	if(DETAIL)
	{
		printf("\n- - - - - MATRICE D'ADJACENCE - - - - - \n");
		AFFICHER_MAT(mat_adjacence);

		printf("\n\t\t\t\t\t\t\t\t\t- - - - - MATRICE DES LONGUEURS DES PLUS COURTS CHEMINS - - - - - \n");
		AFFICHER_MAT(L);

		printf("\n\t\t\t\t\t\t\t\t\t- - - - - MATRICE DES PREDECESSEURS - - - - - \n");
		AFFICHER_MAT(P);

		printf("\n- - - - - TABLEAU PREDECESSEUR - - - - - \n");
		AFFICHER_TAB(64, predecesseur);
	}

//Menu d'affichage
	int choix = 0;
	printf("\n1.Plus court chemin\n2.Tour du cavalier\n");
	printf("Quel est votre choix ? (1/2) : ");

	scanf("%d", &choix);

	printf("\n- - - - - ECHIQUIER - - - - - \n");
	AFFICHER_ECHIQUIER(echiquier);
	
	if (choix == 1)//l'utilisateur a chosis la partie "Plus court chemin"
	{
		//Demande à l'utilisateur de saisir au clavier la case de départ
		while (depart < 0 || depart > 63)
		{
			printf("\nCase de depart ? : ");
			scanf("%d", &depart);
			//Si l'utilisateur entre une valeur incorrecte, on lui demande à nouveau
			if (depart < 0 || depart > 63)
				printf("ERREUR : Entrez une valeur comprise entre 0 et 63\n");
			//Permet de vider le buffer pour scanf();
			viderBuffer();
		}

		//De la même manière que pour le départ
		while (arrivee < 0 || arrivee > 63)
		{
			printf("\nCase d'arrivee ? : ");
			scanf("%d", &arrivee);
			if (arrivee < 0 || arrivee > 63)
				printf("ERREUR : Entrez une valeur comprise entre 0 et 63\n");
			viderBuffer();
		}

//Affichage du résultat
		printf("\n- - - - - PARTIE 1- - - - - \n");
		printf("\n1. GENERATION DU GRAPHE\n");
		printf("\n\t\t\t\t\t\t\t\t\t- - - - - MATRICE D'ADJACENCE - - - - - \n");
		AFFICHER_MAT(mat_adjacence);


		printf("\n2. DEPLACER LE CAVALIER EN UN MINIMUM DE COUPS\n");
		//Permet de déterminer le plus court chemin à partir d'un sommet depart jusqu'au sommet arrivee
		PLUS_COURT_CHEMIN(P, predecesseur, depart, arrivee);

		if (DETAIL)
		{
			printf("\n- - - - - TABLEAU PREDECESSEUR - - - - - \n");
			AFFICHER_TAB(64, predecesseur);
		}
		printf("\n- - - - - PLUS COURT CHEMIN DE %d à %d  - - - - - \n", depart, arrivee);
		AFFICHER_PLUS_COURT_CHEMIN(predecesseur);

		ANALYSE1();
		ECHIQUIER_DEGRE(mat_adjacence, degre, echiquier_degre);
		printf("\n- - - - - ECHIQUIER DEGRE - - - - - \n");
		AFFICHER_ECHIQUIER(echiquier_degre);
	
		ANALYSE2();
		printf("\n\t\t\t\t\t\t\t\t\t- - - - - MATRICE L - - - - - \n");
		AFFICHER_MAT(L);
	}
	else if (choix == 2)//l'utilisateur a choisis la partie "Parcours de toutes les cases"
	{
		printf("\n- - - - - PARTIE 2- - - - - \n");
		printf("\n1. PARCOURS DU CAVALIER\n");
		while (depart < 0 || depart > 63)
		{
			printf("\nCase de depart ? : ");
			scanf("%d", &depart);
			if (depart < 0 || depart > 63)
				printf("ERREUR : Entrez une valeur comprise entre 0 et 63\n");
			viderBuffer();
		}

		//Permet d'obtenir en sortie une matrice echiquier_degre qui a chaque case de l'echiquier, correspond aux degrés du sommet de la case en question
		ECHIQUIER_DEGRES(mat_adjacence, degre, echiquier_degre);
		if(DETAIL)
		{
			printf("\n- - - - - ECHIQUIER DEGRES - - - - - \n");
			AFFICHER_ECHIQUIER(echiquier_degre);
		}

		//Début du parcours du cavalier en débutant par la case "depart"
		printf("\n////////////// PARCOURS //////////////\n");
		PARCOURS(mat_adjacence, echiquier, echiquier_degre, chemin, marque, voisin, depart);

		REMPLISSAGE_CHEMIN_ECHIQUIER(echiquier, chemin, echiquier_chemin);

		if(DETAIL)
		{
			printf("\n////////////// FIN PARCOURS //////////////\n");
		}

		printf("\n- - - - - CHEMIN - - - - - \n");
		AFFICHER_CHEMIN(chemin);
		printf("\n- - - - - ECHIQUIER - - - - - \n");
		AFFICHER_ECHIQUIER(echiquier);

		printf("\n- - - - - ECHIQUIER CHEMIN - - - - - \n");
		AFFICHER_ECHIQUIER(echiquier_chemin);
		printf("ECHIQUIER CHEMIN nous permet de voir le chemin que le cavalier a pris sur l'echiquier\n");

		printf("\n- - - - - ECHIQUIER DEGRE - - - - - \n");
		AFFICHER_ECHIQUIER(echiquier_degre);
		printf("Pour pouvoir verifier si le cavalier est bien passe sur chaque case, l'echiquier_degre doit etre une matrice nulle. \nSi l'echiquier_degre possede encore des valeurs differentes de 0, cela signifie que le cavalier n'a pas pu terminer son parcours correctement\n\n");
		
	

	}
	
	
				
/***************************   SDL   *****************************************************/

/************** CHARGEMENT SDL  ********************************************************/
//gestion des erreurs de chargement SDL
	    if (SDL_Init(SDL_INIT_VIDEO) == -1)
	    {
		fprintf(stderr, "Erreur d'initialisation de la SDL");
		exit(EXIT_FAILURE);
	    }
	    
    
/********* ECRAN DE BASE ***************************************************************/ 
	
	SDL_Surface *ecran = NULL; // Le pointeur qui va stocker la surface de l'écran
	ecran = SDL_SetVideoMode(1600, 1600, 32, SDL_HWSURFACE);// largeur, hauteur, nb couleur (max=36), options --> voir haut page
	
	
	SDL_WM_SetCaption(" * Cavalier * ", NULL);//titre de la fenêtre, options inutiles
    
    
//gestion des erreurs de l'écran
	if (ecran == NULL)
	{
		fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}
	
/*********  REMPLIR AVEC UNE COULEUR UNIE  LE FOND  *******************************************/	

//création d'une couleur RGB
	Uint32 couleurfond = SDL_MapRGB(ecran->format,0, 255, 255);//toujours mettre pointeur "ecran"-->format, R, G, B

//remplissage du fond de l'écran 	
	SDL_FillRect(ecran, NULL, couleurfond);//pointeur la ou on veut remplir, la partie de la surface (null=tout), couleur stockée dans un nombre de typeUint32

//rafraichissement de l'écran	
	SDL_Flip(ecran); 
	
	
/********* CREATION D'UN RECTANGLE ****************************************************/
	
// initialisation des cases noires du damier
	SDL_Surface *rect1 = NULL,*rect2 = NULL, *rect3 = NULL,*rect4 = NULL; 
	SDL_Surface *rect5 = NULL, *rect6 = NULL,*rect7 = NULL,*rect8 = NULL; 
	SDL_Surface *rect9 = NULL, *rect10 = NULL,*rect11 = NULL,*rect12 = NULL; 
	SDL_Surface *rect13 = NULL, *rect14 = NULL,*rect15 = NULL,*rect16 = NULL; 
	SDL_Surface *rect17 = NULL, *rect18 = NULL,*rect19 = NULL,*rect20 = NULL; 
	SDL_Surface *rect21 = NULL, *rect22 = NULL,*rect23 = NULL,*rect24 = NULL; 
	SDL_Surface *rect25 = NULL, *rect26 = NULL,*rect27 = NULL,*rect28 = NULL; 
	SDL_Surface *rect29 = NULL, *rect30 = NULL,*rect31 = NULL,*rect32 = NULL; 

//initialisation du fond blanc du damier
	SDL_Surface *fond_plateau=NULL;

//affichage du fond blanc à l'écran
	fond_plateau = SDL_CreateRGBSurface(SDL_HWSURFACE, 8*dimcase, 8*dimcase, 32, 0, 0, 0, 0);
	SDL_FillRect(fond_plateau, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));

	SDL_Rect position;
	position.x = zero;
	position.y = zero;
	
	SDL_BlitSurface(fond_plateau, NULL, ecran, &position);
	
	
//appel de la fonction qui affiche les cases noires du damier pour chacune d'entre elles avec les bonnes coordonées d'affichage 
	affiche_case(rect1, ecran, zero, zero);
	//premiere ligne (haut)
	affiche_case(rect3, ecran, zero + 2*dimcase, zero);
	affiche_case(rect4, ecran, zero + 4*dimcase, zero);
	affiche_case(rect5, ecran, zero + 6*dimcase, zero);
	//première colonne
	affiche_case(rect8, ecran, zero, zero + 2*dimcase);
	affiche_case(rect9, ecran, zero, zero + 4*dimcase);
	affiche_case(rect10, ecran, zero, zero + 6*dimcase);
	//digonale centrale
	affiche_case(rect12, ecran, zero + dimcase, zero + dimcase);
	affiche_case(rect13, ecran, zero + 2*dimcase, zero + 2*dimcase);
	affiche_case(rect14, ecran, zero + 3*dimcase, zero + 3*dimcase);
	affiche_case(rect15, ecran, zero + 4*dimcase, zero + 4*dimcase);
	affiche_case(rect16, ecran, zero + 5*dimcase, zero + 5*dimcase);
	affiche_case(rect17, ecran, zero + 6*dimcase, zero + 6*dimcase);
	affiche_case(rect18, ecran, zero + 7*dimcase, zero + 7*dimcase);
	//diagonale centrale +1
	affiche_case(rect20, ecran, zero + dimcase, zero + 3*dimcase);
	affiche_case(rect21, ecran, zero + 2*dimcase, zero + 4*dimcase);
	affiche_case(rect22, ecran, zero + 3*dimcase, zero + 5*dimcase);
	affiche_case(rect23, ecran, zero + 4*dimcase, zero + 6*dimcase);
	affiche_case(rect24, ecran, zero + 5*dimcase, zero + 7*dimcase);
	//diagonale centrale -2
	affiche_case(rect25, ecran, zero + dimcase, zero + 5*dimcase);
	affiche_case(rect26, ecran, zero + 2*dimcase, zero + 6*dimcase);
	affiche_case(rect27, ecran, zero + 3*dimcase, zero + 7*dimcase);
	//diagonale centrale -3
	affiche_case(rect28, ecran, zero + dimcase, zero + 7*dimcase);
	//diagonale centrale -1
	affiche_case(rect29, ecran, zero + 3*dimcase, zero + dimcase);
	affiche_case(rect30, ecran, zero + 4*dimcase, zero + 2*dimcase);
	affiche_case(rect31, ecran, zero + 5*dimcase, zero + 3*dimcase);
	affiche_case(rect32, ecran, zero + 6*dimcase, zero + 4*dimcase);
	affiche_case(rect19, ecran, zero + 7*dimcase, zero + 5*dimcase);
	//diagonale centrale +2
	affiche_case(rect11, ecran, zero + 5*dimcase, zero + dimcase);
	affiche_case(rect6, ecran, zero + 6*dimcase, zero + 2*dimcase);
	
	affiche_case(rect2, ecran, zero+7*dimcase, dimcase);
	affiche_case(rect7, ecran, zero+ 7*dimcase, 3*dimcase);





//pour afficher le cavalier sur la case de départ 
	SDL_Surface *image_cavalier=NULL;//déclaration et initialisation de l'image
	image_cavalier=SDL_LoadBMP("cavalier.bmp");//chargement de l'image
	//bonnes coordonées en fonction du numéro de case selectionnée par l'utilisateur
	int cavalier_x=depart%8;
	int cavalier_y=depart/8;
	afficher_image(image_cavalier, ecran, cavalier_x,cavalier_y);//afficahge de l'image


//le plus court chemin

	int STOCK[7];
	int i=0;
	int j=0;
	//recupération du parcours dans un tbl plus facilement exploitable
	for(i=0; i<63; i++)
	{
		printf("%d, ", chemin[i]);
		if(predecesseur[i]!=-1 && predecesseur[i]!=depart)
		{
			STOCK[j]=predecesseur[i];
			j++;
		}
	}
	printf("\n");
 
	//affichage
	int compt=0;
	if(choix==1)
	{
		for(i=6;i>=0;i--)
		{
					
			if(STOCK[i]!=0)
			{
				cavalier_x=predecesseur[i]%8;
				cavalier_y=predecesseur[i]/8;

				sdl_cheminLePlusCourt(ecran, cavalier_x, cavalier_y, compt);
				compt++;
				SDL_Delay(DELAY);
				SDL_Flip(ecran);
			}
		}
	}
	else if(choix==2)
	{
		for(i=1;i<64;i++)
		{
			cavalier_x=chemin[i]%8;
			cavalier_y=chemin[i]/8;
				
			sdl_toutParcourir(ecran, cavalier_x, cavalier_y, i);
			SDL_Delay(DELAY);
			SDL_Flip(ecran);
			
		}
	}
		
//rafraichissement de l'écran	
	SDL_Flip(ecran); 


	
	pause(); // Mise en pause du programme
   
/***********  FERMETURE ******************************************************************/
	SDL_FreeSurface(rect1);
	SDL_FreeSurface(rect2);
	SDL_FreeSurface(rect3);
	SDL_FreeSurface(rect4);
	SDL_FreeSurface(rect5);
	SDL_FreeSurface(rect6);
	SDL_FreeSurface(rect7);
	SDL_FreeSurface(rect8);
	SDL_FreeSurface(rect9);
	SDL_FreeSurface(rect10);
	SDL_FreeSurface(rect11);
	SDL_FreeSurface(rect12);
	SDL_FreeSurface(rect13);
	SDL_FreeSurface(rect14);
	SDL_FreeSurface(rect15);
	SDL_FreeSurface(rect16);
	SDL_FreeSurface(rect17);
	SDL_FreeSurface(rect18);
	SDL_FreeSurface(rect19);
	SDL_FreeSurface(rect20);
	SDL_FreeSurface(rect21);
	SDL_FreeSurface(rect22);
	SDL_FreeSurface(rect23);
	SDL_FreeSurface(rect24);
	SDL_FreeSurface(rect25);
	SDL_FreeSurface(rect26);
	SDL_FreeSurface(rect27);
	SDL_FreeSurface(rect28);
	SDL_FreeSurface(rect29);
	SDL_FreeSurface(rect30);
	SDL_FreeSurface(rect31);
	SDL_FreeSurface(rect32);
	
//SDL_FreeSurface(ecran); inutile car pour l'écran se ferme automatiquement en quittant la SDL
	
	SDL_Quit();
	
	return 0;
}
