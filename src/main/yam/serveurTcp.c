// AdvanSolar_Console.cpp�: d�finit le point d'entr�e pour l'application console.
//

#include <string.h>
#include <stdio.h>

#include <stdlib.h>
#include <stddef.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <unistd.h>
#define PORT 1100       /* the port client will be connecting to */
#define MAXDATASIZE 100 /* max number of bytes we can get at once */
#define TRUE 1
#include "jeu.h"

int serialrecfromserv(FM *OTHER, int sockfd);
int serialsendtoserv(FM *OTHER, int sockfd);

int main()
{
    int socket_desc, client_sock[5], c, read_size;
    int nb_player = 0, nb_tours = 0;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char client_message[2000];
    char buff[500];
    FM OTHER[5];
    int opt = TRUE;

    //Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
                   sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(1100);

    //Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) != 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    //Accept and incoming connection
    c = sizeof(struct sockaddr_in);
    listen(socket_desc, 5);

    while (1)
    {
        puts("Waiting for incoming connections...");
        if (nb_player < 5)
        {
            //accept connection from an incoming client
            client_sock[nb_player] = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c);
            if (client_sock[nb_player] >= 0)
            {
                puts("New player\n");
                nb_player++;
                printf("%d\n", nb_player);
            }
            if (client_sock < 0)
            {
                perror("accept failed");
                return 1;
            }
            puts("Connection accepted\n");
        }

        if (nb_player > 2)
        {
            printf("debut de la partie\n");
            for (int i = 0; i < 11; i++)
            {
                nb_tours++;
                printf("tour %d\n", i + 1);

                for (int i = 0; i < nb_player; i++)
                {
                   if (recv(client_sock[i], buff, MAXDATASIZE , 0) > 0)
                   {
                       printf("bonne réception des donnés");
                   }
                }
                for (int i = 0; i < nb_player; i++)
                {
                    printf("envoie des données aux autres joueurs\n");
                    for (int j = nb_player; j > 0; j--)
                    {
                        if (i != j)
                        {
                            serialsendtoserv(&OTHER[i], client_sock[i]);
                        }
                    }
                }

                for (int i = 0; i < nb_player; i++)
                {
                    clear_fiche(&OTHER[0]);
                }
            }
        }

        if (nb_tours == 11)
        {
            for (int i = 0; i < nb_player; i++)
            {
                close(client_sock[i]);
            }
            nb_player = 0;
            nb_tours = 0;
        }
    }

    return 0;
}

int serialsendtoserv(FM *OTHER, int sockfd)
{
    /*
    char nom[50];   char score[3];	int un; int deux;
	int trois;  int quattre; 	int cinq;   int six;	int yam;
	int carre;	int brelan; int chance;	int full;
    */
    char *buff;
    int size = 0;

    size += snprintf(buff + size, sizeof(OTHER->nom), "%s;", OTHER->nom);
    size += snprintf(buff + size, sizeof(OTHER->score), "%s;", OTHER->score);
    size += snprintf(buff + size, sizeof(OTHER->un), "%d;", OTHER->un);
    size += snprintf(buff + size, sizeof(OTHER->deux), "%d;", OTHER->deux);
    size += snprintf(buff + size, sizeof(OTHER->trois), "%d;", OTHER->trois);
    size += snprintf(buff + size, sizeof(OTHER->quattre), "%d;", OTHER->quattre);
    size += snprintf(buff + size, sizeof(OTHER->cinq), "%d;", OTHER->cinq);
    size += snprintf(buff + size, sizeof(OTHER->six), "%d;", OTHER->six);
    size += snprintf(buff + size, sizeof(OTHER->yam), "%d;", OTHER->yam);
    size += snprintf(buff + size, sizeof(OTHER->carre), "%d;", OTHER->carre);
    size += snprintf(buff + size, sizeof(OTHER->brelan), "%d;", OTHER->brelan);
    size += snprintf(buff + size, sizeof(OTHER->chance), "%d;", OTHER->chance);
    size += snprintf(buff + size, sizeof(OTHER->full), "%d;", OTHER->full);
    printf("%s", buff);
    fflush(stdout);

    if (send(sockfd, buff, sizeof(buff), 0) > 0)
    {
        printf("tout roule\n");
    }
    free(buff);

    return size;
}

int serialrecfromserv(FM *OTHER, int sockfd)
{
    char *buff = (char *)malloc(MAXDATASIZE);
    printf("debut réception\n");
    fflush(stdout);
    if (recv(sockfd, buff, MAXDATASIZE * 3, 0) > 0)
    {
        printf("%s\n", buff);
        printf("j'ai recu\n");
        fflush(stdout);
    }
    OTHER->nom = strtok(buff, ";");
    printf("%s",OTHER->nom);
    OTHER->score = strtok(NULL, ";");
    printf("%s",OTHER->score);
    OTHER->un = atoi(strtok(NULL, ";"));
    OTHER->deux = atoi(strtok(NULL, ";"));
    OTHER->trois = atoi(strtok(NULL, ";"));
    OTHER->quattre = atoi(strtok(NULL, ";"));
    OTHER->cinq = atoi(strtok(NULL, ";"));
    OTHER->six = atoi(strtok(NULL, ";"));
    OTHER->yam = atoi(strtok(NULL, ";"));
    OTHER->carre = atoi(strtok(NULL, ";"));
    OTHER->brelan = atoi(strtok(NULL, ";"));
    OTHER->chance = atoi(strtok(NULL, ";"));
    OTHER->full = atoi(strtok(NULL, ";"));
    free(buff);
    return 1;
}