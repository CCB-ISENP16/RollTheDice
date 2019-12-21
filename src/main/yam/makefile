install: serveur.o jeu.o client.o dice.o serveurTcp.o clientTcp.o
	rm -f ESSAI
	rm -f serveur
	rm -f client
	
	gcc -g -Wall serveur.o jeu.o  -o serveur
	gcc -g -Wall client.o jeu.o -o client
	gcc -g -Wall dice.o jeu.o -o ESSAI
	gcc -g -Wall clientTcp.o jeu.o -o clientTCP
	gcc -g -Wall serveurTcp.o jeu.o -o serveurTCP

	rm -f *.o 



client.o: client.c
	gcc -c client.c 

serveur.o: serveur.c 
	gcc -c serveur.c 

dice.o:dice.c 
	gcc -c dice.c 

jeu.o:jeu.c 
	gcc -c jeu.c 

clientTcp.o : clientTcp.c
	gcc -c clientTcp.c

serveurTcp.o: serveurTcp.c
	gcc -c serveurTcp.c



clean:
	rm -f *.o 
	rm -f ESSAI
	rm -f serveur
	rm -f client
