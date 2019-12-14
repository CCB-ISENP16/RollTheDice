#include "dice.h" //"../../inc/dice.h"


void enregistrer(FM *t)
{
    int desc, r;
    //printf("Enregistrement dans un fichier\n");
    desc = open("stat.txt", O_WRONLY | O_CREAT, 0666);

    lseek(desc, 0, SEEK_END);

    if (desc == -1)
    {
        perror("Error when opening");
    }

    r = write(desc, &t->nom, sizeof(t->nom));
    if (r == -1)
    {
        perror("Error when writting");
    }

    r = write(desc, ",", sizeof(","));
    if (r == -1)
    {
        perror("Error when writting");
    }

    // for (int i = 0; i < 1; i++)
    //{
    r = write(desc, &t->score[0], sizeof(t->score[0]));
    if (r == -1)
    {
        perror("Error when writting");
    }

    r = write(desc, ",", sizeof(","));
    if (r == -1)
    {
        perror("Error when writting");
    }
    // }

    r = write(desc, "\n", sizeof("\n"));
    if (r == -1)
    {
        perror("Error when writting");
    }

    close(desc);
}
/*
int lancer(JOUEUR *J1){
	int nb_alea[1];
	//nb_alea[0] = NULL;
	srand(time(NULL));

    for (int i = 0; i < 1; i++)
    {
        nb_alea[i] = (rand() % 6) + 1;
        sprintf(&J1->score[i], "%d", nb_alea[i]);

        printf("%s a fait : %s \n", J1->name, &J1->score[i]);
    }
    enregistrer(J1);
    return nb_alea[0];
}
*/

int main(void)
{

    FM J1;
    int i = 0;

    bzero(J1.nom, sizeof(J1.nom));

    printf("Nom du joueur : ");
    scanf("%s", J1.nom);
    clear_fiche(&J1);
    //lancer(&J1); ça marche si tu veux
    while (i < 3)
    { //!!!!!!!!mettre 11!!!!!!!!!!
        i++;
        char buffer;
        getchar();
        printf("\ntaper sur n'importe quel caractère pour jouer au tour %d \n", i);
        scanf("%c", &buffer);
        tour_de_jeu(&J1);
        affichage_fiche(&J1);
    }

    return 0;
}
