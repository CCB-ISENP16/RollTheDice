#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "fcntl.h"

#include "string.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

typedef struct Joueur {

char name[50];
int score;

}joueur;

void ajouterLancer(joueur *t){// 
    int fichier;
    if (    fichier = open ("valeur_des.txt", O_WRONLY|O_CREAT,0666)==-1){
    printf("test");
    }
    
    if (write(fichier, t->name, sizeof(t->name))==-1){
        printf("test2");
    }

    if (write(fichier, ",", sizeof(",") )==-1){ 
    printf("test3");
    }

    if(write(fichier, &t->score, sizeof(int))==-1){
    printf("test4");
    }
    if(write(fichier, "\n", sizeof("\n"))==-1){
    printf("test5");
    }
    

    if(close(fichier)==-1)
    printf("test6");
}


void recup_base_donnees(joueur *t){
        int fichier;
        fichier = open ("valeur_des.txt", O_APPEND,750);
        char ligne[100];
        char*token;
        int index_ligne = 0;



        while ((read(fichier,ligne,100) ) != 0) {


            token = strtok(ligne,",");
            strcpy(t[index_ligne].name,token);

            token = strtok(NULL,",");
            //strcpy(t[index_ligne].score,token);
            t[index_ligne].score= atoi(token);

            
        }
        close(fichier);
}

int main(void)
{
    int nb_alea[2];
    FILE * fichier;
    joueur J1 ;
    printf("joueur name : \n");
    scanf("%s",J1.name);

    //int pid;    
    
    srand(time(NULL));//initialisation fonctions rand
    
    for(int i = 0; i <2 ; i++){
    J1.score = (rand()%6)+1 ;//jet de dés

    printf("jet de dés : %d \n", J1.score);
    
    
    }
    ajouterLancer(&J1);
    recup_base_donnees( &J1);
    //pipe(nb_alea);



}
