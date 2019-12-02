#include "../../inc/player.h"

int main(void)
{
    PLAYER P1;
    int desc;
    int pidServer;
    char Key;

    bzero(P1.name, sizeof(P1.name));

    printf("Nom du joueur : ");
    scanf("%s", P1.name);

    desc = open("../../pipe/Player1", O_RDWR);
    if (desc == -1)
    {
        perror("Error with Pipe1 trying with Pipe2");
        desc = open("../../pipe/Player2", O_RDWR);
    }
    write(desc, &P1.name, sizeof(P1.name));
    if (desc == -1)
    {
        perror("Error while writting in pipe");
    }
    close(desc);

    printf("Press \"Enter\" to roll the dice\n");
    scanf("%c", &Key);
    // kill(pidServer, SIGUSR1);
}