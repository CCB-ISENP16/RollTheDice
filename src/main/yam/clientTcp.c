/***************************************************************************/
/*                                                                         */
/* Client program which gets as parameter the server name or               */
/*     address and tries to send the data into non-blocking server.        */
/*                                                                         */
/* The message is sent after 5 seconds of wait                             */
/*                                                                         */
/*                                                                         */
/* based on Beej's program - look in the simple TCp client for further doc.*/
/*                                                                         */
/*                                                                         */
/***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "jeu.h"

#define PORT 1100 /* the port client will be connecting to */

#define MAXDATASIZE 100 /* max number of bytes we can get at once */
void rectoserv(FM *OTHER, int sockfd);
void affichageAutreJoueur(int sockfd);
void sendtoserv(FM *OTHER, int sockfd);
int serialsendtoserv(FM *OTHER, int sockfd);
int serialrecfromserv(FM *OTHER, int sockfd);

int main(int argc, char *argv[])
{
    int sockfd, numbytes;
    int n=0;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */
    FM J1;

    if (argc != 2)
    {
        fprintf(stderr, "usage: client hostname\n");
        exit(1);
    }

    if ((he = gethostbyname(argv[1])) == NULL)
    { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        perror("socket");
        exit(1);
    }

    their_addr.sin_family = AF_INET;   /* host byte order */
    their_addr.sin_port = htons(PORT); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)he->h_addr);
    bzero(&(their_addr.sin_zero), 8); /* zero the rest of the struct */

    if (connect(sockfd, (struct sockaddr *)&their_addr,
                sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }

    bzero(J1.nom, sizeof(J1.nom));

    printf("Nom du joueur : ");
    n=scanf("%s", J1.nom);
    J1.nom[n]='\0';
    clear_fiche(&J1);

    for (int i = 0; i < 11; i++)
    {
        char buffer;
        getchar();
        printf("\ntaper sur n'importe quel caractère pour jouer au tour %d \n", i+1);
        scanf("%c", &buffer);
        printf("début du tour de jeu\n");
        fflush(stdout);
        tour_de_jeu(&J1);
        fflush(stdout);
        affichage_fiche(&J1);
        serialsendtoserv(&J1, sockfd);
        affichageAutreJoueur(sockfd);
    };


    close(sockfd);

    return 0;
}
void affichageAutreJoueur(int sockfd)
{
    FM *OTHER;
    printf("l'autre joueur a choisis :");
    serialrecfromserv(OTHER, sockfd);
    affichage_fiche(OTHER);
}


int serialsendtoserv(FM *OTHER, int sockfd)
{
    /*
    char nom[50];   char score[3];	int un; int deux;
	int trois;  int quattre; 	int cinq;   int six;	int yam;
	int carre;	int brelan; int chance;	int full;
    */
    char * buff= (char *)malloc(MAXDATASIZE);
    int size=0;
    printf("envoie des donnés\n");
    fflush(stdout);

    size+=snprintf(buff+size,sizeof(OTHER->nom)+1,"%s;",OTHER->nom);
    size+=snprintf(buff+size,sizeof(OTHER->score)+1,"%s;",OTHER->score);
    size+=snprintf(buff+size,sizeof(OTHER->un)+1,"%d;",OTHER->un);
    size+=snprintf(buff+size,sizeof(OTHER->deux)+1,"%d;",OTHER->deux);
    size+=snprintf(buff+size,sizeof(OTHER->trois)+1,"%d;",OTHER->trois);
    size+=snprintf(buff+size,sizeof(OTHER->quattre)+1,"%d;",OTHER->quattre);
    size+=snprintf(buff+size,sizeof(OTHER->cinq)+1,"%d;",OTHER->cinq);
    size+=snprintf(buff+size,sizeof(OTHER->six)+1,"%d;",OTHER->six);
    size+=snprintf(buff+size,sizeof(OTHER->yam)+1,"%d;",OTHER->yam);
    size+=snprintf(buff+size,sizeof(OTHER->carre)+1,"%d;",OTHER->carre);
    size+=snprintf(buff+size,sizeof(OTHER->brelan)+1,"%d;",OTHER->brelan);
    size+=snprintf(buff+size,sizeof(OTHER->chance)+1,"%d;",OTHER->chance);
    size+=snprintf(buff+size,sizeof(OTHER->full)+1,"%d;",OTHER->full);

    printf("%s\n %ld",buff,sizeof(buff));
    fflush(stdout);
    
    if(send(sockfd,buff,MAXDATASIZE,0) > 0)
    {
        printf("tout roule\n");
        fflush(stdout);
    }

    return size;
}

int serialrecfromserv(FM *OTHER, int sockfd)
{
    char * buff;
    if(recv(sockfd,buff,MAXDATASIZE,0)>0)
    {
        printf("%s",buff);
        printf("j'ai recu\n");
        fflush(stdout);
    }
    OTHER->nom= strtok(buff,";");
    OTHER->score = strtok(NULL,";");
    OTHER->un=atoi(strtok(NULL,";"));
    OTHER->deux=atoi(strtok(NULL,";"));
    OTHER->trois=atoi(strtok(NULL,";"));
    OTHER->quattre=atoi(strtok(NULL,";"));
    OTHER->cinq=atoi(strtok(NULL,";"));
    OTHER->six=atoi(strtok(NULL,";"));
    OTHER->yam=atoi(strtok(NULL,";"));
    OTHER->carre=atoi(strtok(NULL,";"));
    OTHER->brelan=atoi(strtok(NULL,";"));
    OTHER->chance=atoi(strtok(NULL,";"));
    OTHER->full=atoi(strtok(NULL,";"));
}