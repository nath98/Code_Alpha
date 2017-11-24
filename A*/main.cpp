#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <math.h>


#define XM 100
#define YM 100

struct noeud
{
        unsigned short x, y , C, H; //C:cout(nombre de pas depuis la base) H:heuristique(distance à l'objectif)        
};

void Astar(unsigned short* matrice, struct noeud obj, struct noeud depart);
void ajouter_liste_autour_noeud(struct noeud* liste, struct noeud N, unsigned short *indice);

int main (int argc, char *argv[])
{
	unsigned short matrice[XM][YM];
	struct noeud objectif, depart;
	objectif.x = 3;
	objectif.y = 3;
	depart.x = 4;
	depart.y = 4;
	
	Astar(*matrice, objectif, depart);
        return 0;
}

void Astar(unsigned short* matrice, struct noeud obj, struct noeud depart)
{
	struct noeud* closedlist[YM*XM], openlist[YM*XM];
	struct noeud grille[XM][YM];//matrice de noeuds
	unsigned short openlist_i=0, closedlist_i=0; //indice des listes
	unsigned short i, y;

	for (i=0; i<XM; i++)
	{
		for (y=0; y<YM; y++)
		{
			grille[i][y].x=i+1;
			grille[i][y].y=y+1;

			grille[i][y].H=abs(grille[i][y].x-obj.x)+abs(grille[i][y].x-obj.x);
		}
	}

	openlist[openlist_i]=depart;
	openlist_i ++;

	ajouter_liste_autour_noeud(openlist, depart, &openlist_i);
	std::cout << grille[50][50].H << std::endl;
	
}

void ajouter_liste_autour_noeud(struct noeud* liste, struct noeud N, unsigned short *indice)
{

}

char compare_noeuds(struct noeud N1, struct noeud N2)
{
        char retour;

        if(N1.H<N2.H)
        {
		retour =  1;
        }
	else if (N1.H==N2.H)
	{	
		retour = 0;
	}
	else 
	{
		retour = -1;
	}
	return retour;
}



