#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include "jeu.h"

void readStructPipe(FM*OTHER, pid_t desc);
void writeStructPipe(FM*OTHER, pid_t desc);


void affichageAutreJoueur(pid_t desc, char *argv);

void main(int argc, char *argv[])
{
    pid_t desc[2];//0 ecriture et 1 lecture
    char *buff;
    int id;
    FM J1;
    int n;

    bzero(J1.nom, sizeof(J1.nom));

    printf("Nom du joueur : ");
    scanf("%s", J1.nom);
    clear_fiche(&J1);

    if (!strcmp(argv[1], "joueur1"))
    {
        desc[1] = open("joueur1W", O_RDONLY);
        desc[0] = open("joueur1R", O_WRONLY);

        read(desc[1], &id, sizeof(id));
        printf("%d\n", id);
        fflush(stdout);  

        n=write(desc[0], J1.nom, sizeof(J1.nom));
        printf("je suis joueur1\n");
    }
    else
    {
        desc[1] = open("joueur2W", O_RDONLY);
        desc[0] = open("joueur2R", O_WRONLY);

        read(desc[1], &id, sizeof(id));
        printf("pid = %d\n", id);
        fflush(stdout);

        n=write(desc[0], J1.nom, sizeof(J1.nom));
        printf("je suis joueur2\n");
    }

    for (int i = 0; i < 11; i++)
    {
        char buffer;
        getchar();
        printf("\ntaper sur n'importe quel caractère pour jouer au tour %d \n", i);
        scanf("%c", &buffer);
        tour_de_jeu(&J1);
        affichage_fiche(&J1);
        writeStructPipe(&J1,desc[0]);
        kill(id, SIGUSR1);
        affichageAutreJoueur(desc[1], argv[1]);

    };
}

void affichageAutreJoueur(pid_t desc, char *argv)
{
    FM *OTHER;
    printf("l'autre joueur a choisis :");
    readStructPipe(OTHER,desc);
    affichage_fiche(OTHER);
}

void writeStructPipe(FM*OTHER, pid_t desc)
{
    /*
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
    */

    write(desc, OTHER->nom, sizeof( OTHER->nom));
    write(desc, OTHER->score, sizeof( OTHER->score));
    write(desc, &OTHER->un, sizeof( OTHER->un));
    write(desc, &OTHER->deux, sizeof( OTHER->deux));
    write(desc, &OTHER->trois, sizeof( OTHER->trois));
    write(desc, &OTHER->quattre, sizeof( OTHER->quattre));
    write(desc, &OTHER->cinq, sizeof( OTHER->cinq));
    write(desc, &OTHER->six, sizeof( OTHER->six));
    write(desc, &OTHER->yam, sizeof( OTHER->yam));
    write(desc, &OTHER->carre, sizeof( OTHER->carre));
    write(desc, &OTHER->brelan, sizeof( OTHER->brelan));
    write(desc, &OTHER->chance, sizeof( OTHER->chance));
    write(desc, &OTHER->full, sizeof( OTHER->full));
}

void readStructPipe(FM*OTHER, pid_t desc)
{
    read(desc, OTHER->nom, sizeof( OTHER->nom));
    read(desc, OTHER->score, sizeof( OTHER->score));
    read(desc, &OTHER->un, sizeof( OTHER->un));
    read(desc, &OTHER->deux, sizeof( OTHER->deux));
    read(desc, &OTHER->trois, sizeof( OTHER->trois));
    read(desc, &OTHER->quattre, sizeof( OTHER->quattre));
    read(desc, &OTHER->cinq, sizeof( OTHER->cinq));
    read(desc, &OTHER->six, sizeof( OTHER->six));
    read(desc, &OTHER->yam, sizeof( OTHER->yam));
    read(desc, &OTHER->carre, sizeof( OTHER->carre));
    read(desc, &OTHER->brelan, sizeof( OTHER->brelan));
    read(desc, &OTHER->chance, sizeof( OTHER->chance));
    read(desc, &OTHER->full, sizeof( OTHER->full));

}