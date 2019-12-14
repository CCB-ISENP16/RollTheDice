#ifndef DICE

#include <stdio.h>
#include <time.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "jeu.h"

typedef struct Joueur
{
    char name[50];
    char score[3];
} JOUEUR;


void enregistrer(FM *t);

#endif