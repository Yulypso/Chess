#include "headers.h"
//Permet de vider le buffer pour l'utilisation du scanf();
void viderBuffer()
{
  int c;
  //Recupere les entrees du clavier dans la variable c tant qu'on n'a pas atteint le '\n'
  while((c=getchar())!= '\n');
}

void ANALYSE1()
{
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ANALYSE 1 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - \n");
	printf("Enonce : ");
	printf("\nEn vous appuyant sur les resultats fournis par votre graphe,\n");
	printf("Quelle serait la zone de jeu optimale pour le cavalier afin qu'il puisse couvrir ");
	printf("l'ensemble de l'echiquier en un nombre minimal de coups ?\n");
	printf("Experimenter plusieurs fois des positions initiales pour vous en rendre compte.\n");
	printf("\nMa reponse : ");
	printf("\nD'après la matrice ECHIQUIER DEGRE qui représente pour chaque case de l'échiquier, le nombre de possibilités de déplacement en 1 coups, \n");
	printf("les zones optimales pour le cavalier sont les cases : \n");
	printf("[18], [19], [20], [21], [26], [27], [28], [29], [34], [35], [36], [37], [42], [43], [44], [45]\n");
}

void ANALYSE2()
{
	printf("\n- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ANALYSE 2 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -\n");
	printf("Enonce : ");
	printf("\nExiste t-il un chemin minimal de 7 coups entre deux cases de l'echiquier ? Justifier.\n");
	printf("\nMa reponse : ");
	printf("\nD'après la matrice L des longueurs des plus courts chemins (FLOYD-WARSHALL), le maximum des chemins les plus courts entre 2 cases est 6. \n");
	printf("Par exemple, on lit : la longueur du plus court chemin depuis le sommet 0 jusqu'à les autres sommets et le maximum parmi les longueurs est 6.\n");
	printf("C'est à dire depuis le sommet 0 jusqu'au sommmet 63\n");
	printf("La matrice peut se lire ligne-colonne ou colonne-ligne, car matrice symétrique.\n");
}

//Permet d'initialiser une matrice de taille 64x64
void REMPLISSAGE_MATRICE(int TAB[64][64])
{
	for(int i=0; i<64; i++)
	{
		for(int j=0; j<64; j++) 
		{
			TAB[i][j] = 0;
		}
	}
}

//Permet d'initialiser un tableau des sommets marques de taille 64
//0 : non marque
//1 : est marque
void REMPLISSAGE_MARQUE(int marque[64])
{
	for(int i=0; i<64; i++)
	{
		marque[i] = 0;
	}
}

//Permet d'initialiser un tableau des predecesseurs de taille 64
//Il permet le stockage du chemin le plus court entre deux sommets
//On l'affichera en sens oppose pour obtenir le chemin avec des successeurs
void REMPLISSAGE_predecesseur(int predecesseur[64])
{
	for(int i=0; i<64; i++)
	{
		predecesseur[i] = -1;
	}
}

//Permet d'initialiser une matrice de taille 8x8
//Utilise pour echiquier et echiquier_degre
void REMPLISSAGE_ECHIQUIER(int TAB[8][8])
{
	int cpt = 0;

	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			TAB[i][j]= cpt;
			cpt++;
		}
	}
}

//Permet l'affichage d'un tableau avec ses indices de taille "line"
void AFFICHER_TAB(int line, int TAB[])
{
	//affichage des indices
	printf("      ");	
	for(int i=0;i<line;i++)
	{
		//Un decalage de 3 espaces entre chaque indice
		printf("%3d", i);
	}

	printf("\n");
	printf("      ");	

	//affichage de la separation
	for(int k=0;k<line;k++)
	{
		printf("---");
	}

	printf("\n");
	printf("      ");

	//affichage des valeurs contenues dans le tableau TAB
	for(int j=0; j<line; j++)
	{
		printf("%3d", TAB[j]);
	}
	printf("\n\n");
}

//Permet d'afficher une matrice de taille 8x8
//Utilise pour echiquier et echiquier_degre
void AFFICHER_ECHIQUIER(int TAB[8][8])
{
	for(int i=0; i<8; i++)
	{
		for(int j=0; j<8; j++)
		{
			printf("%2d ", TAB[i][j]);

			//Dès qu'on arrive à la 8eme case du tableau, on retourne à la ligne
			if((j+1)%8==0)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
}

//Permet d'afficher une matrice de taille 64x64
//Utilise pour la matrice d'adjacence, matrice L et matrice P
void AFFICHER_MAT(int TAB[64][64])
{
	printf("      ");	
	for(int i=0;i<64;i++)
	{
		printf("%3d", i);
	}

	printf("\n");
	printf("      ");	
	for(int j=0;j<64;j++)
	{
		printf("---");
	}
	printf("\n");


	for(int i=0; i<64; i++)
	{
		printf(" %3d |", i);

		for(int j=0; j<64; j++)
		{
			printf("%3d", TAB[i][j]);

			if((j+1)%64==0)
			{
				printf("\n");
			}
		}
	}
	printf("\n");
}

//A partir d'une position initiale donnee (y,x), on determine les deplacements possible en 1 coup du cavalier
//8 positions à tester
void GENERER_GRAPHE(int echiquier[8][8], int G[64][64])
{
	int val_case=0; 		int val_case_Haut_Gauche=0; 	int val_case_Haut_Droite=0;
	int val_case_Gauche_Haut=0; 	int val_case_Gauche_Bas=0; 	int val_case_Droite_Haut=0;
	int val_case_Droite_Bas=0; 	int val_case_Bas_Gauche=0; 	int val_case_Bas_Droite=0;

	for(int x=0; x<8; x++)
	{
		for(int y=0; y<8; y++)
		{
			//permet de stocker la valeur de la case correspondant aux coordonnes (y,x)
			val_case = echiquier[y][x];

			//Pour acceder à la case (y-2, x-1)
			if(y-2 >= 0 && x-1 >= 0)
			{
				//Si la case existe, alors on stocke la valeur correspondant a la case (y-2, x-1)
				val_case_Haut_Gauche = echiquier[y-2][x-1];

				//Dans la matrice d'adjacence, on va se placer à la ligne correspondant à la valeur de la case position initiale
				//et on va se placer à la colonone correspondant à la valeur de la case existante 
				//A l'emplacement definie par la ligne et la colonne, on va placer la valeur [1] dans la matrice d'adjacence,
				//afin de dire que la case de position initiale est bien adjacente à la case existante testee.
				G[val_case][val_case_Haut_Gauche] = 1;
				G[val_case_Haut_Gauche][val_case] = 1;
			}

			//même chose pour les 7 autres tests

			//Pour acceder à la case (y-2, x+1)
			if(y-2 >= 0 && x+1 <= 7)
			{
				val_case_Haut_Droite = echiquier[y-2][x+1];

				G[val_case][val_case_Haut_Droite] = 1;
				G[val_case_Haut_Droite][val_case] = 1;
			}

			//Pour acceder à la case (y-1, x-2)
			if(y-1 >= 0 && x-2 >= 0)
			{
				val_case_Gauche_Haut = echiquier[y-1][x-2];

				G[val_case][val_case_Gauche_Haut] = 1;
				G[val_case_Gauche_Haut][val_case] = 1;
			}

			//Pour acceder à la case (y+1, x-2)
			if(y+1 <= 7 && x-2 >= 0)
			{
				val_case_Gauche_Bas = echiquier[y+1][x-2];

				G[val_case][val_case_Gauche_Bas] = 1;
				G[val_case_Gauche_Bas][val_case] = 1;
			}

			//Pour acceder à la case (y-1, x+2)
			if(y-1 >= 0 && x+2 <= 7)
			{
				val_case_Droite_Haut = echiquier[y-1][x+2];
		
				G[val_case][val_case_Droite_Haut] = 1;
				G[val_case_Droite_Haut][val_case] = 1;
			}

			//Pour acceder à la case (y+1, x+2)
			if(y+1 <= 7 && x+2 <= 7)
			{
				val_case_Droite_Bas = echiquier[y+1][x+2];

				G[val_case][val_case_Droite_Bas] = 1;
				G[val_case_Droite_Bas][val_case] = 1;
			}

			//Pour acceder à la case (y+2, x-1)
			if(y+2 <= 7 && x-1>= 0)
			{
				val_case_Bas_Gauche = echiquier[y+2][x-1];
		
				G[val_case][val_case_Bas_Gauche] = 1;
				G[val_case_Bas_Gauche][val_case] = 1;
			}

			//Pour acceder à la case (y+2, x+1)
			if(y+2 <= 7 && x+1 <= 7)
			{
				val_case_Bas_Droite = echiquier[y+2][x+1];

				G[val_case][val_case_Bas_Droite] = 1;
				G[val_case_Bas_Droite][val_case] = 1;
			}
		}
	}
}

//Algorithme de FLOYD-WARSHALL
//Permet d'avoir en sortie une matrice P (predecesseurs) et une matrice L (longueur des plus courts chemins)
void FLOYD(int G[64][64], int L[64][64], int P[64][64])
{	
	//Initialisation des matrices P et L pour l'algorithme de FLOYD-WARSHALL
	for(int a=0; a<64; a++)
	{
		for(int b=0; b<64; b++)
		{
			if(a == b)
			{
				//La diagonale de la matrice est la longueur des plus courts chemins entre un sommet A vers un sommet A, la distance est nulle.
				L[a][b] = 0;
			}
			else if(G[a][b]==1)
			{	
				//Si deux sommets sont adjacents alors la longueur des plus courts chemins entre ces deux sommets vaut 1
				L[a][b]=1;
			}
			else
			{	//Ici j'ai choisi 9 qui est considere comme infini, car c'est une valeur de longueur des plus courts chemins impossible
				L[a][b]=9;
			}
			//Permet d'initialiser la matrice P des predecesseurs
			P[a][b]=a;
		}
	}

	//Parcours de l'algorithme de FLOYD-WARSHALL
	//On cherche à savoir, si en passant par le sommet k, on peut trouver une plus court chemin quelque soit le couple(i,j)
	//ici, on va tester pour k allant de 0 à 63 inclus sommets k.
	for(int k=0; k<64; k++)
	{
		for(int i=0; i<64; i++)
		{
			for(int j=0; j<64; j++)
			{
				//Si on ne se situe pas sur une diagonale et que si on a bien un chemin de i vers j passant par j plus court que le chemin de i vers j direct
				if((i!=j) && ((L[i][k]+L[k][j])<L[i][j]))
				{	
					//La longueur du plus court chemin devient la longueur du chemin passant par k 
					L[i][j]=L[i][k]+L[k][j];
					//Le predecesseur de ce chemin est alors le chemin passant par k 
					P[i][j]=P[k][j];
				}

				//Si on a des longueurs negatives, alors on a un circuit absorbant qui est intraitable avec FLOYD-WARSHALL
				if((i==j)&&(L[i][k]+L[k][j])<0)
				{
					printf("Circuit absorbant. Termine\n");
				}
			}
		}
	}
}

//Permet d'obtenir le tableau du plus court chemin/des predecesseurs à l'envers à partir de la matrice P des predecesseurs de FLOYD-WARSHALL
void PLUS_COURT_CHEMIN(int P[64][64], int predecesseur[64], int depart, int arrivee)
{
	//La premiere case est donc
	predecesseur[0] = arrivee;

	for(int i=1; i<64; i++)
	{
		if(arrivee != depart)
		{
			//en parcourant la matrice P 
			//On vient se placer sur la ligne correspondant au départ
			//Puis on remonte à partir de l'arrivee les predecesseurs
			predecesseur[i] = P[depart][arrivee];

			//la valeur arrivee prend la valeur du predecesseurs
			//cela nous permet de remonter jusqu'a obtenir le predecesseur avant la case depart
			arrivee = P[depart][arrivee];
		}
	}
}

//Permet d'afficher le plus court chemin entre 2 sommets en utilisant le tableau des predecesseurs
void AFFICHER_PLUS_COURT_CHEMIN(int predecesseur[64])
{
	//on parcours le tableau des predecesseurs à l'envers pour pouvoir afficher les sommets dans l'ordre du deplacement à partir du départ jusqu'à l'arrivee
	for(int i=63; i>=0; i--)
	{
		if(predecesseur[i]!= -1)
		{
			printf(" %d ", predecesseur[i]);

			if(i!=0)
			{
				printf(" ==> ");
			}
		}
	}
	printf("\n");
}

//Permet d'obtenir en sortie une matrice echiquier_degre qui a chaque case de l'echiquier, correspond aux degrés du sommet de la case en question
void ECHIQUIER_DEGRE(int G[64][64], int degre[64], int echiquier_degre[8][8])
{	
	int cpt = 0;
	int m=0;

	//on parcours la matrice G d'adjacence, puis on 
	for(int i=0; i<64; i++)
	{
		for(int j=0; j<64; j++)
		{
			if(G[i][j] == 1)
			{
				cpt++;
			}
		}
		//on insere dans le tableau degre de 0 à 63, la valeur correspondant au degré de l'indice de la case
		degre[i]=cpt;
		cpt=0;
	}

	//on parcours echiquier degre, et a chaque case d'indice i de l'echiquier_degre est associé le degre contenu dans le tableau d'indice i
	for(int k=0; k<8; k++)
	{
		for(int l=0; l<8; l++)
		{
			echiquier_degre[k][l]=degre[m];
			m++;
		}
	}
}

void REMPLISSAGE_VOISIN(int voisin[8])
{
	//initialisation du tableau des voisins à -1
	for (int i = 0; i < 8; i++)
	{
		voisin[i] = -1;
	}
}

//Permet de convertir une case de l'echiquier en position (y,x) et de récupérer en sortie une variable de type POSITION
POSITION CONVERTIR_CASE_POSITION(int cases, int TAB[8][8])
{
	POSITION position;
	position.x = 0;
	position.y = 0;

	//on parcours l'echiquier qui possede des cases allant de 0 à 63
	for (int i=0; i < 8; i++)
	{
		for (int j=0; j < 8; j++)
		{
			//si la case correspond à la case sur l'echiquier, on recupere les indices i et j qui forment le couple de coordonnees de la position de la case
			if (TAB[i][j] == cases)
			{
				position.x = j;
				position.y = i;
			}
		}
	}
	return position;
}

//permet d'afficher le chemin du cavalier contenant l'ordre de 64 cases sous forme d'un tableau allant de 0 à 63
void AFFICHER_CHEMIN(int chemin[64])
{
	for (int i = 0; i < 64; i++)
	{
		printf(" %d ", chemin[i]);

		if (i != 63)
		{
			printf(" > ");
		}
	}
	printf("\n\n");
}

//permet d'initialiser la matice echiquier_degre avec la valeur des degres de chaque cases de l'echiquier
void ECHIQUIER_DEGRES(int G[64][64], int degre[64], int echiquier_degre[8][8])
{
	int cpt = 0;
	int m = 0;

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			//On parcours la matrice d'adjacence pour pouvoir coonnaitre les voisins de chaque cases
			if (G[i][j] == 1)
			{
				//si pour la case i, on a un voisin, alors le compteur incremente, il nous permettra de definir le degre de la case i
				cpt++;
			}
			//on rempli le premier tableau unidimensionnel degre qui va nous permettre d'associer chaque case de l'echiquier a son degre
			degre[i] = cpt;
		}
		//reinitialisation du compteur
		cpt = 0;
	}

	//on parcours maintenant la matrice echiquier_degre
	for (int k = 0; k < 8; k++)
	{
		for (int l = 0; l < 8; l++)
		{
			//et on rempli l'echiquier_degre avec la valeur en degree de chaque cases correspondante du tableau degre
			echiquier_degre[k][l] = degre[m];
			m++;
		}
	}
}

void PARCOURS(int G[64][64], int echiquier[8][8], int echiquier_degre[8][8], int chemin[64], int marque[64], int voisin[8], int depart)
{
	int cpt = 0;
	int val_test = 0;
	int val_save = 0;
	int val_decrementation = 0;

	POSITION pos_c = CONVERTIR_CASE_POSITION(depart, echiquier);
	POSITION test = CONVERTIR_CASE_POSITION(depart, echiquier);
	POSITION save = CONVERTIR_CASE_POSITION(depart, echiquier);
	POSITION decrementation = CONVERTIR_CASE_POSITION(depart, echiquier);

	int courant = depart;

	for (int i = 0; i < 64; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//on reinitialise toutes les cases du tableau voisin a -1 pour chaque i
			voisin[j] = -1;
		}

		//On marque la case courante, car si la case est marquee, cela signifie que le cavalier est déjà passe dessus !
		marque[courant] = 1;
		//On sauvegarde la case où le cavalier est situe dans le tableau chemin cela nous permettra de connaître le chemin complet
		chemin[i] = courant;

		//On convertis la case où le cavalier est situé sous forme de coordonnees (y,x), cela nous permet de modifier les valeurs de echiquier_degre par la suite par les coordonnees
		pos_c = CONVERTIR_CASE_POSITION(courant, echiquier);

		//on met 0 à echiquier_degre au niveau de la case courante grace à sa position, cela signifie que le cavalier est bien passe par cette case
		echiquier_degre[pos_c.y][pos_c.x] = 0;

		for (int k = 0; k < 64; k++)
		{
			//On parcours la matrice d'adjacence pour connaitre tous les voisins de la case où est situé le cavalier
			if (G[courant][k] == 1)
			{
				//On verifie si les voisins de la case du cavalier ne sont pas deja marque
				//s'ils le sont, alors les cases ne sont pas des voisins de la case actuelle ou est situe le cavalier 
				if (marque[k] != 1)
				{
					//On insere dans le tableau des voisins la valeur des voisins de la case où est situe le cavalier
					voisin[cpt] = k;
					cpt++;
				}
			}
		}
		//On reinitialise le compteur pour la prochaine boucle i
		cpt = 0;

		if (DETAIL)
		{
			printf("\n- - - - - VOISIN DE %d - - - - - \n", courant);
			AFFICHER_TAB(8, voisin);
		}

		//On va maintenant parcourir le tableau des voisins contenant les voisins de la case ou est situe le cavalier
		for (int l = 0; l < 8; l++)
		{
			//si la case ne vaut pas la valeur d'initialisation qui est : -1, cela signifie qu'il existe des cases voisines
			if (voisin[l] != -1)
			{	
				//si l vaut 0, pour le cas de la premiere boucle, on ne fait que enregistrer la valeur du premier voisin de la case ou est situe le cavalier
				//cela nous permettra par la suite de comparer sa valeur en degree avec les autres valeurs en degree des voisins
				if (l == 0)
				{
					val_save = voisin[l];
					save = CONVERTIR_CASE_POSITION(val_save, echiquier);
				}
				else
				{
					//val_test recupere la valeur du voisin suivant du tableau des voisins 
					val_test = voisin[l];
					//On convertis chaque valeur du voisin test en position afin de pouvoir utiliser la matrice echiquier_degree
					test = CONVERTIR_CASE_POSITION(val_test, echiquier);

					//cas particulier pour les cases 24, 27 et 49, la condition du test doit etre : <=
					//ce n'est qu'une question de choix dans le chemin parmi les voisins de meme degree
					if (depart == 24 || depart == 27 || depart == 49)
					{
						//si le degre de la case testee est inferieure au degre de la case sauvegardee
						if (echiquier_degre[test.y][test.x] <= echiquier_degre[save.y][save.x])
						{
							//On compare les valeurs en fonction des positions sur echiquier_degre et on garde la plus petite (sous forme de position)
							//On sauvegarde les coordonnes de la case de plus petite valeur
							save.y = test.y;
							save.x = test.x;
						}
					}
					else
					{
						//de même pour toutes les autres cases 
						if (echiquier_degre[test.y][test.x] < echiquier_degre[save.y][save.x])
						{
							//On compare les valeurs en fonction des positions sur echiquier_degre et on garde la plus petite (sous forme de position)
							//case courante = case de plus petite valeur echiquier_degre
							save.y = test.y;
							save.x = test.x;
						}
					}
				}
			}
		}

		//On a maintenant determine la case la plus optimale pour le prochain deplacement du cavalier,
		//c'est a dire une case voisine possedant le degre le plus faible.
		//en effet, plus le degre le plus faible d'un voisin revient a dire que cette case est une case prioritaire
		courant = echiquier[save.y][save.x];

		//Pour pouvoir faire le deplacement du cavalier, on parcours la matrice des voisins
		for (int m = 0; m < 8; m++)
		{	
			//si la valeur de voisin est different de -1(valeur d'initialisation), cela signifie qu'il existe un voisin
			if (voisin[m] != -1)
			{
				//Si le voisin n'est pas encore marqué
				if (marque[voisin[m]] != 1)
				{
					//On va decrementer les valeurs de tous les voisins de la case ou est situe le cavalier
					//car chaque fois que le cavalier va avancer, il va marquer une case
					//et marquer une case revient a dire que chaque voisin de cette case perdront un voisin (qui est la case ou est situe le cavalier)

					//on recupere la case d'un voisin
					val_decrementation = voisin[m];
					//on le convertis en coordonnee pour pouvoir travailler avec l'echiquier_degree
					decrementation = CONVERTIR_CASE_POSITION(val_decrementation, echiquier);
					//on decremente de 1 pour chaque voisin de la case ou est situe le cavalier
					echiquier_degre[decrementation.y][decrementation.x]--;
				}
			}
		}
		if (DETAIL)
		{
			//Si DETAIL = 1 est activé, 

			//CHEMIN nous permet de voir l'avancement du cavalier cases par cases jusqu'a obtenir le chemin complet
			printf("\n- - - - - CHEMIN - - - - - \n");
			AFFICHER_TAB(64, chemin);

			//MARQUE nous permet de voir les cases marquees liees a l'avancement du cavalier cases par cases
			printf("\n- - - - - MARQUE - - - - - \n");
			AFFICHER_TAB(64, marque);

			//ECHIQUIER DEGRES nous permet de voir les degres des voisins du cavalier decrementer de 1 a chaque avancement cases par cases
			//Et d'attribuer la valeur de 0 lorsque le cavalier est deja passe sur la case
			printf("\n- - - - - ECHIQUIER DEGRES - - - - - \n");
			AFFICHER_ECHIQUIER(echiquier_degre);

			//Pour pouvoir verifier si le cavalier est bien passe sur chaque case, l'echiquier_degre doit etre une matrice nulle.
			//Si l'echiquier_degre possede encore des valeurs differentes de 0, cela signifie que le cavalier n'a pas pu terminer son parcours correctement
		}
	}
}

//Permet de remplir l'echiquier' representant le parcours du cavalier
void REMPLISSAGE_CHEMIN_ECHIQUIER(int echiquier[8][8], int chemin[64], int echiquier_chemin[8][8])
{
	int cpt = 0;
	POSITION c = CONVERTIR_CASE_POSITION(0, echiquier); //initialisation de la variable c de type POSITION

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			//c prend la valeur de la position de la case cpt du chemin (cpt allant de 0 à 64 sans debordemement)
			c = CONVERTIR_CASE_POSITION(chemin[cpt], echiquier);
			//on remplis la matrice echiquier_chemin avec le compteur cpt qui va incrementer pour pouvoir connaitre l'ordre des cases du parcours sur l'echiquier
			echiquier_chemin[c.y][c.x] = cpt;
			cpt++;
		}
	}
}
