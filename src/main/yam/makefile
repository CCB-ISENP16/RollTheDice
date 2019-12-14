ESSAI:dice.o jeu.o
	gcc -g -Wall dice.o jeu.o -o ESSAI

serveur: serveur.o jeu.o 
	gcc -g -Wall serveur.o jeu.o  -o serveur

client: jeu.o client.o
	gcc -g -Wall client.o jeu.o -o client


client.o: client.c
	gcc -c client.c 

serveur.o: serveur.c 
	gcc -c serveur.c 

dice.o:dice.c 
	gcc -c dice.c 

jeu.o:jeu.c 
	gcc -c jeu.c 

 

clean:
	rm -f *.o 
	rm -f ESSAI
	rm -f serveur
	rm -f client
