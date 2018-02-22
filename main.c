#include "BlackJack_3.h"

int main(){

    valeur  = (char**)malloc(13 * sizeof (*valeur));
    couleur = (char**)malloc(4  * sizeof (*couleur));
	assert(valeur);
	assert(couleur);

    valeur[0] = "AS";
    valeur[1] = "DEUX";
    valeur[2] = "TROIS";
    valeur[3] = "QUATRE";
    valeur[4] = "CINQ";
    valeur[5] = "SIX";
    valeur[6] = "SEPT";
    valeur[7] = "HUIT";
    valeur[8] = "NEUF";
    valeur[9] = "DIX";
    valeur[10] = "VALET";
    valeur[11] = "REINE";
    valeur[12] = "ROI";

    couleur[0] = "PIQUE";
    couleur[1] = "COEUR";
    couleur[2] = "CARREAU";
    couleur[3] = "TREFLE";

    srand(time(NULL));
	
	Joueur croupier;
	
    /*Joueur jTab[2];
	strcpy(jTab[0].nom,"Dan");
	strcpy(jTab[1].nom,"Ari");*/
	int i;
	char s[10];
	int nb_de_joueur;
	printf("combien de joueurs etes vous ?");
	fgets(s, 10, stdin);
	nb_de_joueur = atoi(s);
	if (nb_de_joueur > 5 || nb_de_joueur < 2)
	  {
	    printf("Nb de joueur doit etre compris entre 2 et 5");
	    return (0);
	  }
	Joueur* jTab = (Joueur*)malloc(nb_de_joueur * sizeof (*jTab));
	strcpy(jTab[0].nom,"Dan");
	strcpy(jTab[1].nom,"Harry");
	if (nb_de_joueur > 2)
	  strcpy(jTab[2].nom,"Rym");
	if (nb_de_joueur > 3)
	  strcpy(jTab[3].nom,"Yanis");
	if (nb_de_joueur > 4)
	  strcpy(jTab[4].nom,"Sylvain");

	for(i=0;i<nb_de_joueur;i++){
	  jTab[i].stack=1000;
	}

    jeu(jTab, &croupier, nb_de_joueur);
    
	/*int choix=1;
	
	for(;choix==1;){
	  
	  printf("Continuer 1 ou quitter 2");
	  scanf("%d",&choix);
	  }*/
	
	//free(jTab);
    free(valeur);
    free(couleur);
    getchar();
    return 0;
}
