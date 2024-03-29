#include "../../inc/dice.h"

void enregistrer(JOUEUR *t)
{
    int desc, r;
    printf("Enregistrement dans un fichier\n");
    desc = open("stat.txt", O_WRONLY | O_CREAT, 0666);

    lseek(desc, 0, SEEK_END);

    if (desc == -1)
    {
        perror("Error when opening");
    }

    r = write(desc, &t->name, sizeof(t->name));
    if (r == -1)
    {
        perror("Error when writting");
    }

    r = write(desc, ",", sizeof(","));
    if (r == -1)
    {
        perror("Error when writting");
    }

    for (int i = 0; i < 2; i++)
    {
        r = write(desc, &t->score[i], sizeof(t->score[i]));
        if (r == -1)
        {
            perror("Error when writting");
        }

        r = write(desc, ",", sizeof(","));
        if (r == -1)
        {
            perror("Error when writting");
        }
    }

    r = write(desc, "\n", sizeof("\n"));
    if (r == -1)
    {
        perror("Error when writting");
    }

    close(desc);
}

int main(void)
{
    int nb_alea[2];
    JOUEUR J1;

    bzero(J1.name, sizeof(J1.name));

    printf("Nom du joueur : ");
    scanf("%s", J1.name);

    srand(time(NULL));

    for (int i = 0; i < 2; i++)
    {
        nb_alea[i] = (rand() % 6) + 1;
        sprintf(&J1.score[i], "%d", nb_alea[i]);

        printf("%s a fait : %s \n", J1.name, &J1.score[i]);
    }
    enregistrer(&J1);

    return 0;
}