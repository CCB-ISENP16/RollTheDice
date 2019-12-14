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

void func()
{
    printf("synchronisation en cours\n");
}
void setup()
{
    unlink("joueur1W");
    mkfifo("joueur1W", 0666);

    unlink("joueur2W");
    mkfifo("joueur2W", 0666);

    unlink("joueur1R");
    mkfifo("joueur1R", 0666);

    unlink("joueur2R");
    mkfifo("joueur2R", 0666);

    signal(SIGUSR1, func);
}

void main()
{
    pid_t desc_Joueur1[2]; // ecriture en 0 et lecture en 1
    pid_t desc_Joueur2[2];
    FM joueur_table[2];
    char *buff;
    pid_t id;
    int n,taille;

    setup();
    id = getpid();

    desc_Joueur1[0] = open("joueur1W", O_WRONLY);
    desc_Joueur1[1] = open("joueur1R", O_RDONLY);
    desc_Joueur2[0] = open("joueur2W", O_WRONLY);
    desc_Joueur2[1] = open("joueur2R", O_RDONLY);

    write(desc_Joueur1[0], &id, sizeof(id));
    write(desc_Joueur2[0], &id, sizeof(id));

    printf("Attente des joueurs\n");

    n = read(desc_Joueur1[1], buff, 50);
    // printf("%d", n);
    // fflush(stdout);
    strcpy(&buff[n], "\0");
    printf("%s\n", buff);
    fflush(stdout);
    printf("Joueur1 connecté en attente de joueur2\n");

    n = read(desc_Joueur2[1], buff, 50);
    // printf("%d", n);
    // fflush(stdout);
    strcpy(&buff[n], "\0");
    printf("%s\n", buff);
    fflush(stdout);
    printf("joueur2 connecté. le jeu va débuter\n");

    clear_fiche(&joueur_table[0]);
    clear_fiche(&joueur_table[1]);

    for (int i = 0; i < 11; i++)
    {
        printf("tour %d\n", i + 1);

        pause();
        pause();
       
        readStructPipe( &joueur_table[0],desc_Joueur1[1]);
        printf("le joueur %s a jouée\n", joueur_table[0].nom);
       
        readStructPipe( &joueur_table[1],desc_Joueur2[1]);
        printf("le joueur %s a jouée\n", joueur_table[1].nom);
      
        writeStructPipe(&joueur_table[1],desc_Joueur1[0]);
        writeStructPipe(&joueur_table[0],desc_Joueur2[0]);

        clear_fiche(&joueur_table[0]);
        clear_fiche(&joueur_table[1]);
    }
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