#ifndef JEU
#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>



typedef struct FeuilleMatch {
	char nom[50];
	char score[3];
	int un;
	int deux;
	int trois;
	int quattre; 
	int cinq;
	int six;
	int yam;
	int carre;
	int brelan;
	int chance;
	int full;


}FM;

void clear_fiche(FM* Joueur);
int affichage_fiche(FM* Joueur);
int remplissage(FM *Joueur, int Case,int de[]);


int lancer(FM *J1);
void tour_de_jeu(FM *J1);

int uno(int Case,int de[]);
int chance(int de[]);
int full(int de[]);
int brelan(int de[]);
int yam(int de[]);
int carre(int de[]);

#endif
