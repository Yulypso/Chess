#include <SDL/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "headers.h"

void sdl_cheminLePlusCourt (SDL_Surface* ecran,int x, int y, int compt)
{
//permet d'afficher les cases du chemin comme parcourures

	SDL_Surface *image=NULL;//déclaration de l'image
	
	switch(compt)//permet de choisir quelle image on veut afficher
	{
		case 0://premiere case du chemin
			image=SDL_LoadBMP("0.bmp");
			break;
		case 1://deuxieme case du chemin
			image=SDL_LoadBMP("1.bmp");
			break;
		case 2://troisieme case du chemin
			image=SDL_LoadBMP("2.bmp");
			break;
		case 3://quatrieme case du chemin
			image=SDL_LoadBMP("3.bmp");
			break;
		case 4://cinquieme case du chemin
			image=SDL_LoadBMP("4.bmp");
			break;
		case 5://sixieme case du chemin
			image=SDL_LoadBMP("5.bmp");
			break;
		
			
		default://en cas de soucis, si compt ne comprends aucune des valeurs entre 0 et 5
			image=SDL_LoadBMP("cavalier.bmp");//on affcihe le cavalier ( et non pas une case à afficher) pour montrer l'erreur
			break;
	}
	
	afficher_image(image, ecran, x, y);//appel de la fonction pour afficher l'image à l'écran en (x,y)
	
}

void sdl_toutParcourir (SDL_Surface* ecran,int x, int y, int compt)
{
//permet d'afficher les cases du parcours totales comme parcourues
	SDL_Surface *image=NULL;// déclaration de l'image
	
	switch(compt)//permet de choisir quele image on souhaite afficher
	{
		case 1://premiere case du parcours
			image=SDL_LoadBMP("Image1.bmp");
			break;
		case 2://deucieme case du parcours 
			image=SDL_LoadBMP("Image2.bmp");
			break;
		case 3:
			image=SDL_LoadBMP("Image3.bmp");
			break;
		case 4:
			image=SDL_LoadBMP("Image4.bmp");
			break;
		case 5:
			image=SDL_LoadBMP("Image5.bmp");
			break;
		case 6:
			image=SDL_LoadBMP("Image6.bmp");
			break;
		case 7:
			image=SDL_LoadBMP("Image7.bmp");
			break;
		case 8:
			image=SDL_LoadBMP("Image8.bmp");
			break;
		case 9:
			image=SDL_LoadBMP("Image9.bmp");
			break;
		case 10:
			image=SDL_LoadBMP("Image10.bmp");
			break;
		case 11:
			image=SDL_LoadBMP("Image11.bmp");
			break;
		case 12:
			image=SDL_LoadBMP("Image12.bmp");
			break;
		case 13:
			image=SDL_LoadBMP("Image13.bmp");
			break;
		case 14:
			image=SDL_LoadBMP("Image14.bmp");
			break;
		case 15:
			image=SDL_LoadBMP("Image15.bmp");
			break;
		case 16:
			image=SDL_LoadBMP("Image16.bmp");
			break;
		case 17:
			image=SDL_LoadBMP("Image17.bmp");
			break;
		case 18:
			image=SDL_LoadBMP("Image18.bmp");
			break;
		case 19:
			image=SDL_LoadBMP("Image19.bmp");
			break;
		case 20:
			image=SDL_LoadBMP("Image20.bmp");
			break;
		case 21:
			image=SDL_LoadBMP("Image21.bmp");
			break;
		case 22:
			image=SDL_LoadBMP("Image22.bmp");
			break;
		case 23:
			image=SDL_LoadBMP("Image23.bmp");
			break;
		case 24:
			image=SDL_LoadBMP("Image24.bmp");
			break;
		case 25:
			image=SDL_LoadBMP("Image25.bmp");
			break;
		case 26:
			image=SDL_LoadBMP("Image26.bmp");
			break;
		case 27:
			image=SDL_LoadBMP("Image27.bmp");
			break;
		case 28:
			image=SDL_LoadBMP("Image28.bmp");
			break;
		case 29:
			image=SDL_LoadBMP("Image29.bmp");
			break;
		case 30:
			image=SDL_LoadBMP("Image30.bmp");
			break;
		case 31:
			image=SDL_LoadBMP("Image31.bmp");
			break;
		case 32:
			image=SDL_LoadBMP("Image32.bmp");
			break;
		case 33:
			image=SDL_LoadBMP("Image33.bmp");
			break;
		case 34:
			image=SDL_LoadBMP("Image34.bmp");
			break;
		case 35:
			image=SDL_LoadBMP("Image35.bmp");
			break;
		case 36:
			image=SDL_LoadBMP("Image36.bmp");
			break;
		case 37:
			image=SDL_LoadBMP("Image37.bmp");
			break;
		case 38:
			image=SDL_LoadBMP("Image38.bmp");
			break;
		case 39:
			image=SDL_LoadBMP("Image39.bmp");
			break;
		case 40:
			image=SDL_LoadBMP("Image40.bmp");
			break;
		case 41:
			image=SDL_LoadBMP("Image41.bmp");
			break;
		case 42:
			image=SDL_LoadBMP("Image42.bmp");
			break;
		case 43:
			image=SDL_LoadBMP("Image43.bmp");
			break;
		case 44:
			image=SDL_LoadBMP("Image44.bmp");
			break;
		case 45:
			image=SDL_LoadBMP("Image45.bmp");
			break;
		case 46:
			image=SDL_LoadBMP("Image46.bmp");
			break;
		case 47:
			image=SDL_LoadBMP("Image47.bmp");
			break;
		case 48:
			image=SDL_LoadBMP("Image48.bmp");
			break;
		case 49:
			image=SDL_LoadBMP("Image49.bmp");
			break;
		case 50:
			image=SDL_LoadBMP("Image50.bmp");
			break;
		case 51:
			image=SDL_LoadBMP("Image51.bmp");
			break;
		case 52:
			image=SDL_LoadBMP("Image52.bmp");
			break;
		case 53:
			image=SDL_LoadBMP("Image53.bmp");
			break;
		case 54:
			image=SDL_LoadBMP("Image54.bmp");
			break;
		case 55:
			image=SDL_LoadBMP("Image55.bmp");
			break;;
		case 56:
			image=SDL_LoadBMP("Image56.bmp");
			break;
		case 57:
			image=SDL_LoadBMP("Image57.bmp");
			break;
		case 58:
			image=SDL_LoadBMP("Image58.bmp");
			break;
		case 59:
			image=SDL_LoadBMP("Image59.bmp");
			break;
		case 60:
			image=SDL_LoadBMP("Image60.bmp");
			break;
		case 61:
			image=SDL_LoadBMP("Image61.bmp");
			break;
		case 62:
			image=SDL_LoadBMP("Image62.bmp");
			break;
		case 63:
			image=SDL_LoadBMP("Image63.bmp");
			break;
			
		default://en cas de soucis, si compt ne comprends aucune des valeurs entre 1 et 63
			image=SDL_LoadBMP("cavalier.bmp");//on affcihe le cavalier ( et non pas une case à afficher) pour montrer l'erreur
			break;
	}
	
	afficher_image(image, ecran, x, y);//on appel la fonction qui affiche l'image choisies sur limgae "ecran" aux coordonees (x,y)
	
}

void afficher_image(SDL_Surface *image, SDL_Surface *ecran, int x, int y)
{
//on définit la position où l'on veut afficher l'image	
	SDL_Rect position;
	position.x=zero +(dimcase*x);//zero est dynamique pour pouvoir décaler le plateau si besoin, dimacse est dynamique pour pouvoir changer la taille des cases du damier si besoin
	position.y= zero + (dimcase*y);
	
//on enlève le background de l'image (utile pour l'image du cavalier qui a un fond blanc)
	SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 255,255,255));//(0,0,0)=couleur qui doit etre rendue transparente
	
//on colle l'image sur le fond (ecran)
	SDL_BlitSurface(image, NULL, ecran, &position);
		
}

void affiche_case(SDL_Surface *rect, SDL_Surface *ecran, int x, int y)//x horizontal, y vertical
{
//permet d'afficher les cases noires du damier

	rect = SDL_CreateRGBSurface(SDL_HWSURFACE, dimcase, dimcase, 32, 0, 0, 0, 0);// option vidéo, largeur, hauteur, nb couleur, (la ou il y a 0 = parametre inutiles pour ce qu'on veut faire ici)
	
	SDL_FillRect(rect, NULL, SDL_MapRGB(ecran->format, 0, 0, 0));//remplir tout le rectangle en noir
	
//choix des coordonées où l'on veut afficher l'image
	SDL_Rect position;
	position.x = x;
	position.y = y;
	
	SDL_BlitSurface(rect, NULL, ecran, &position); //pour coller l'image sur l'image "écran" aux coordonées (x,y) (NULL pour coller l'image en entier)
}

void pause()
{
//permet à l'écran de rester afficher et de pouvoir fermer avec la croix
    int continuer = 1;
    SDL_Event event;

    while (continuer)//condition d'arret = continuer=0 <=> l'utilisateur a cliquer sur la croix rouge de la fenetre
    {
        SDL_WaitEvent(&event);
     
        switch(event.type)
        {
            case SDL_QUIT://si on a cliqué sur la croix rouge de la fenetre
                continuer = 0;
        }
    }
}








 
