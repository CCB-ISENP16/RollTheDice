#include "jeu.h"

int lancer(FM *J1)
{
	int nb_alea;
	static int first;
	int n=0;
	if (first == 0)
	{
		first = 1;
		srand(time(NULL));
	}
	nb_alea = 0;
	nb_alea = (rand() % 6) + 1;
	J1->score = (char*) malloc(sizeof(int)+1);
	n=snprintf(J1->score, sizeof(int),"%d", nb_alea);
	J1->score[n]='\0';

	return nb_alea;
}



int affichage_fiche(FM *Joueur)
{ // retourne Total du Joueur
	int Total = 0;
	printf("\n Fiche de Jeu Yam's de %s \n (les cases remplies avec -1 sont à remplir) ", Joueur->nom);
	printf("\n 1 : %d ", Joueur->un);
	printf("\n 2 : %d", Joueur->deux);
	printf("\n 3 : %d", Joueur->trois);
	printf("\n 4 : %d", Joueur->quattre);
	printf("\n 5 : %d", Joueur->cinq);
	printf("\n 6 : %d", Joueur->six);
	printf("\n Total 1 : %d", Joueur->un + Joueur->deux + Joueur->trois + Joueur->quattre + Joueur->cinq + Joueur->six);
	Total = Joueur->un + Joueur->deux + Joueur->trois + Joueur->quattre + Joueur->cinq + Joueur->six;
	if (Joueur->un + Joueur->deux + Joueur->trois + Joueur->quattre + Joueur->cinq + Joueur->six >= 63)
	{
		printf("\n Total 1 + BONUS! : %d", Joueur->un + Joueur->deux + Joueur->trois + Joueur->quattre + Joueur->cinq + Joueur->six + 35);
		Total = Joueur->un + Joueur->deux + Joueur->trois + Joueur->quattre + Joueur->cinq + Joueur->six + 35;
	}
	printf("\n\n full : %d", Joueur->full);
	printf("\n chance : %d", Joueur->chance);
	printf("\n brelan : %d", Joueur->brelan);
	printf("\n carre : %d", Joueur->carre);
	printf("\n yam : %d", Joueur->yam);
	printf("\n Total 2 : %d", Joueur->full + Joueur->chance + Joueur->brelan + Joueur->carre + Joueur->yam);
	printf("\n\n TOTAL = %d\n", Total + Joueur->full + Joueur->chance + Joueur->brelan + Joueur->carre + Joueur->yam);

	return Total + Joueur->full + Joueur->chance + Joueur->brelan + Joueur->carre + Joueur->yam;
}

void clear_fiche(FM *Joueur)
{
	Joueur->un = -1;
	Joueur->deux = -1;
	Joueur->trois = -1;
	Joueur->quattre = -1;
	Joueur->cinq = -1;
	Joueur->six = -1;
	Joueur->full = -1;
	Joueur->chance = -1;
	Joueur->brelan = -1;
	Joueur->carre = -1;
	Joueur->yam = -1;
}

int uno(int Case, int de[])
{
	int i = 0;
	if (de[1] == Case)
		i++;
	if (de[2] == Case)
		i++;
	if (de[3] == Case)
		i++;
	if (de[4] == Case)
		i++;
	if (de[5] == Case)
		i++;
	return i;
}

int chance(int de[])
{
	return de[1] + de[2] + de[3] + de[4] + de[5];
}

int full(int de[])
{
	if (de[1] == de[2] && de[2] == de[3])
	{
		if (de[4] == de[5])
			return 30;
	}
	else if (de[1] == de[2] && de[2] == de[5])
	{
		if (de[4] == de[3])
			return 30;
	}
	else if (de[1] == de[2] && de[2] == de[4])
	{
		if (de[3] = de[5])
			return 30;
	}
	else if (de[1] == de[4] && de[4] == de[3])
	{
		if (de[2] == de[5])
			return 30;
	}
	else if (de[4] == de[2] && de[2] == de[3])
	{
		if (de[1] == de[5])
			return 30;
	}
	else if (de[5] == de[2] && de[2] == de[3])
	{
		if (de[4] == de[1])
			return 30;
	}
	else if (de[1] == de[5] && de[5] == de[3])
	{
		if (de[4] == de[2])
			return 30;
	}
	else if (de[4] == de[5] && de[5] == de[3])
	{
		if (de[1] == de[2])
			return 30;
	}
	else if (de[4] == de[1] && de[1] == de[5])
	{
		if (de[2] == de[3])
			return 30;
	}
	else if (de[4] == de[2] && de[2] == de[5])
	{
		if (de[1] == de[3])
			return 30;
	}
	else
		return 0;
}

int brelan(int de[])
{
	if (de[1] == de[2] && de[2] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[1] == de[2] && de[2] == de[5])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[1] == de[2] && de[2] == de[4])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[1] == de[4] && de[4] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[2] == de[4] && de[4] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[5] == de[2] && de[2] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[5] == de[1] && de[1] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[5] == de[4] && de[4] == de[3])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[4] == de[1] && de[1] == de[5])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else if (de[4] == de[2] && de[2] == de[5])
		return de[1] + de[2] + de[3] + de[4] + de[5];
	else
		return 0;
}

int yam(int de[])
{
	if (de[1] == de[2] && de[2] == de[3] && de[3] == de[4] && de[4] == de[5])
		return 50;
	else
		return 0;
}

int carre(int de[])
{

	if (de[1] == de[2] && de[2] == de[3] && de[3] == de[4])
	{
		return 40;
	}
	else if (de[1] == de[2] && de[2] == de[3] && de[3] == de[5])
	{
		return 40;
	}
	else if (de[1] == de[2] && de[2] == de[5] && de[5] == de[4])
	{
		return 40;
	}

	else if (de[1] == de[5] && de[5] == de[3] && de[3] == de[4])
	{
		return 40;
	}
	else if (de[5] == de[2] && de[2] == de[3] && de[3] == de[4])
	{
		return 40;
	}
	else
		return 0;
}

int remplissage(FM *Joueur, int Case, int de[])
{
	if (Case == 1)
	{
		Joueur->un = uno(Case, de);
		//printf("vous avez mis %d dans la case 1 !\n",Joueur->un);
	}else if (Case == 2)
	{
		Joueur->deux = 2 * uno(Case, de);
	}
	else if (Case == 3)
	{
		Joueur->trois = 3 * uno(Case, de);
	}
	else if (Case == 4)
	{
		Joueur->quattre = 4 * uno(Case, de);
	}
	else if (Case == 5)
	{
		Joueur->cinq = 5 * uno(Case, de);
	}
	else if (Case == 6)
	{
		Joueur->six = 6 * uno(Case, de);
	}
	else if (Case == 7)
	{
		Joueur->yam = yam(de);
	}
	else if (Case == 8)
	{
		Joueur->carre = carre(de);
	}
	else if (Case == 9)
	{
		Joueur->brelan = brelan(de);
	}
	else if (Case == 10)
	{
		Joueur->full = full(de);
	}
	else if (Case == 11)
	{
		Joueur->chance = chance(de);
		//printf("vous avez mis %d dans la case Chance !\n",Joueur->chance);
	}
	else
		return 0;

	return 1;
}
void tour_de_jeu(FM *J1)
{
	int de[6];
	de[0] = 0;
	de[1] = lancer(J1);
	de[2] = lancer(J1);
	de[3] = lancer(J1);
	de[4] = lancer(J1);
	de[5] = lancer(J1);
	int a = 0;
	int choix = 0;
	int jet = 0;
	while (jet < 3)
	{
		int retrait = -1;
		jet++;
		printf("\n\n lancé n° %d : %d %d %d %d %d", jet, de[1], de[2], de[3], de[4], de[5]);
		while ((retrait != 0) && (jet != 3))
		{
			printf("\n quels dés voulez vous relancez? cites en un seul! exemple : 1 pour dé1, 0 pour aucun \n  ");
			scanf("%d", &retrait);
			if (1 <= retrait <= 6)
			{
				de[retrait] = lancer(J1);
			}
		}
	}

	printf("\n\n/////////////////////////////////////////////////////////////////\n");
	printf("\n\n/n/ Quel case voulez remplir grâce au montant de vos dès?  /n/\n");
	printf("/n/		écrire 1 à 6 pour les chiffres               /n/ \n");
	printf("/n/     7_Yam,8_Carré,9_Brelan,10_Full ou 11 pour la Chance! /n/ \n");
	printf("/n/    Attention vous ne pouvez pas remplir 2x la même case! /n/ \n\n");
	while (a == 0)
	{
		printf("votre choix (écrire un numero): ");
		scanf("%d", &choix);
		printf("\n/////////////////////////////////////////////////////////////////\n\n");
		a = remplissage(J1, choix, de); //met à jour le tableau des scores
	}
}
