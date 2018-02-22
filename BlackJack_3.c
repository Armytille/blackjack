#include"BlackJack_3.h"

/**
<pre>
les variables utilisés:
	-::Paquet est tableau de structures Cartes
	-::indice_fin_Paquet est initialisé a NB_CARTES_MAX-1 ce qui correspond a l'indice de  fin du tableau Paquet
	-::NB_CARTES_MAX est la taille du tableau Paquet.
</pre>
**/
void initialisation_Paquet() {
    indice_fin_Paquet = NB_CARTES_MAX-1;
    int nb_carte,nb_couleur,nb_paquet;

	for(nb_paquet=0;nb_paquet<6;nb_paquet++) {//on crée 6 jeu de carte
		for(nb_carte=0;nb_carte<13;nb_carte++) {//13 cartes
		    for(nb_couleur=0;nb_couleur<4;nb_couleur++){//4 couleurs
		        Paquet[(nb_couleur+4*nb_carte)+(52*nb_paquet)].couleur = nb_couleur; //4 couleurs différentes.
		        Paquet[(nb_couleur+4*nb_carte)+(52*nb_paquet)].nom = nb_carte; //pour une seule valeur.
		        if(nb_carte > 9) Paquet[(nb_couleur+4*nb_carte)+(52*nb_paquet)].valeur = 10;
		        else Paquet[(nb_couleur+4*nb_carte)+(52*nb_paquet)].valeur = nb_carte+1;
		    }
		}
	}
}



/**
Cette fonction calcule la somme des champs Carte::valeur des structures Carte contenues dans le tableau Joueur::main du Joueur <b>player</b> passé en argument et stocke le résultat dans le champ Joueur::sommeMain du Joueur <b>player</b>. De plus elle permet de a l'utilisateur de choisir la valeur des As de sa main en rentrant la valeur sur l'entrée standard.
**/
int JoueurTotalCartes(Joueur* player) {
	int i, total_carte = 0;
	player->sommeMain = 0;
	for(i = 0; i<player->nb_Carte; i++){
		if(player->main[i].nom == 0) {//Ce if permet de demander au joueur s'il veux que son AS soit un 1 ou un 11
			int valAS = 0;//valAS prendra la valeur que on aura choisit pour l'AS
			do {
			  char choix[10];
				printf("Valeur de l'AS ? (1 ou 11) ");
				//scanf("%d",&valAS);
				fgets(choix,10,stdin);
				valAS = atoi(choix);
			} while(valAS != 1 && valAS != 11);
			player->main[i].valeur = valAS;
		}
		total_carte += player->main[i].valeur;//total_carte est la variable qui contiendra la somme des cartes
	}
	player->sommeMain = total_carte;
	return total_carte;
}




/**
Affiche le champ Carte::couleur ainsi que Carte::valeur des cartes de la main du Joueur <b>player</b> passé en paramètre sur la sortie standard.
 **/
void afficherMain(Joueur* player) {
	int i;
	for(i = 0; i<player->nb_Carte; i++)//Tant que i est inferieur au nb de carte affiche la couleur et la valeur de chaque carte une a une
       printf("%s DE %s\n", valeur[player->main[i].nom],couleur[player->main[i].couleur]);

	JoueurTotalCartes(player);



    printf("\n");

    if(player->sommeMain)
		printf("TOTAL: %d\n", player->sommeMain);
}


/**
Permet de remplir la main du Joueur <b>player</b> avec des Carte aléatoires tirées du tableau ::Paquet précédemment rempli par la fonction initialisation_Paquet(). Le tirage sans remise est assuré par la décrémentation de la variable ::indice_fin_Paquet.
**/
void distribuer(Joueur* player,int nb_Carte) {
    int i,indice;
    Carte tmp;

    for(i=0;i<nb_Carte;i++){
      if(indice_fin_Paquet) indice = rand()%indice_fin_Paquet;//Quand on fait rand()% et une variable par exemple g qui correspond ici a la fin du tableau cela va choisir un element du tableau entre le debut et la variable g
			else indice = 0;
		player->main[i] = Paquet[indice];

		if(indice != indice_fin_Paquet) {
			//RNG sans remise !
			tmp = Paquet[indice_fin_Paquet];
		    Paquet[indice_fin_Paquet] = Paquet[indice];
		    Paquet[indice] = tmp;
		    indice_fin_Paquet--;
		}
    }
    player->nb_Carte = nb_Carte;

    //blackjack(player);
}

/**
Rajoute une Carte du tableau ::Paquet dans la main du Joueur <b>player</b> et assure qu'elle ne sera plus disponible à la pioche pendant la partie en cours. Voir fonction distribuer() pour le fonctionnement.
**/
void draw(Joueur* player,int nb_Carte){
	int i,indice;
	Carte tmp;

	if(nb_Carte <= indice_fin_Paquet){
		for(i=0;i<nb_Carte;i++){
		    if(indice_fin_Paquet)
		       indice = rand()%indice_fin_Paquet;
        	else indice = 0;
		    player->main[player->nb_Carte] = Paquet[indice];
		    player->nb_Carte++;

			if(indice != indice_fin_Paquet) {
		          /* RNG sans remise ! */
			  tmp = Paquet[indice_fin_Paquet];///On interchange les cartes la derniere valeur du tableau ::Paquet remplace la carte que l'on vient de tirer et la carte que l'on vient de tirer prend la place de la derniere carte et on deplace l'indice fin de paquet sur la gauche pour ne plus reprendre la carte
				Paquet[indice_fin_Paquet] = Paquet[indice];
				Paquet[indice] = tmp;
				indice_fin_Paquet--;
			}
        }
		//afficherMain(player);
		//JoueurTotalCartes(player);
		//blackjack(player);
    }
}

/**
<pre>
L'argument <b>print</b> est utilisé pour savoir s'il l'on veut aficher ou non le résultat.

Les valeurs retournées sont:
	::BLACKJACK si la somme de la main du Joueur <b>player</b> est égale à 21 et que sa main est composée de 2 Carte.
	::VINGTETUN si la somme de la main du Joueur <b>player</b> est égale à 21 et que sa et composée de plus de 2 Carte.
	::SAUTE si la somme de la main du Joueur <b>player</b> est supérieur à 21.
	autrement la valeur retournée est 0.
</pre>
**/
char blackjack(Joueur* player,char print) {
    if(player->sommeMain == 21 && player->nb_Carte == 2) {
		if(print) printf("BLACKJACK!\n\n");
    	return BLACKJACK;
	}
    if(player->sommeMain == 21 && player->nb_Carte > 2) {
		if(print) printf("21!\n\n");
    	return VINGTETUN;
	}
    if(player->sommeMain > 21) {
		if(print) printf("SAUTE!\n\n");
    	return SAUTE;
	}
    return 0;
}

/**
<pre>
Les valeur de <b>res</b> corespondent a:
	<b>0</b> veut dire que le joueur a perdu sa mise.
	<b>1</b> veut dire que le joueur a gagné.
	<b>2</b> veut dire que le joueur est a égalité avec le croupier.
	<b>3</b> veut dire que le joueur a doublé et gagné.
	<b>4</b> veut dire que le joueur a doublé mais a perdu.
</pre>
**/
int mise(Joueur* player, int res){//res est egale au resultat du joueur qui est soit gagner soit egalité soit perdu

  int new_stack=player->stack;//new stack correspond a la pile de jeton du joueur
  if(res==0){
    new_stack=player->stack-100;
  }
  if(res==1){// 1 etant gagner
    new_stack=player->stack+100;
  }
 if(res==2){// 2 etant egaliter
    new_stack=player->stack;
  }
 if(res==3){//3 etant gagner et a doubler
   new_stack=player->stack+200;
 }
  if(res==4){//4 etant perdu et a doubler
   new_stack=player->stack+-200;
 }
 return new_stack;

}

///tableau qui prend le resultat du choix entre 2,1 ou 0
int tab_choix[5];

/**
<pre>
Cette fonction gère le jeu en plusieurs étapes:
    Initialisation du paquet de cartes.
    Distribution des cartes au joueurs dans <b>pTab</b> et au croupier.
    Une boucle chargée d'afficher la main du croupier et des joueurs ainsi que de demander si les joueurs veulentdoubler, tirer ou rester.
    Une boucle servant "d'IA" au croupier.
    Un affichage du resultat du jeu pour chaque joueur.
    Finalement, le joueur est demandé s'il veut continuer à jouer.
</pre>
<b>Arguments:</b>
pTab est un tableau de Joueur contenant tous les joueurs participant au jeu.
croupier est un Joueur utilisé en tant que le croupier du jeu.
nbP est le nombre de joueurs participant au jeu.
**/
void jeu(Joueur pTab[], Joueur* croupier, int nbP){
    char in[10];
    int i;
debut :
    initialisation_Paquet();
    distribuer(croupier,1);
    for(i = 0; i < nbP; i++)
      distribuer(&pTab[i],2);

    for(i = 0; i < nbP; i++) {
      if(system("clear")) system("cls");
      printf("Main du croupier : \n");
      afficherMain(croupier);
      printf("\nMain du joueur \"%s\" : \n",pTab[i].nom);
      afficherMain(&pTab[i]);
      while(!blackjack(&pTab[i],1)){
	printf("Voulez doubler ? 2, tirer ? 1, 0 pour rester. \n");
	fgets(in,10,stdin);
	if(atoi(in)==2){
	  tab_choix[i]=2;
	  draw(&pTab[i],1);
	  afficherMain(&pTab[i]);
	  break;
	}
	if(atoi(in)==1){
	  tab_choix[i]=1;
	  draw(&pTab[i],1);
			afficherMain(&pTab[i]);
	}
	else{
	  tab_choix[i]=0;
	  break;}
      }
    }
  	//if(system("clear")) system("cls");

	while(!blackjack(croupier,0)){
		if(croupier->sommeMain > 16) break;
			draw(croupier,1);
			JoueurTotalCartes(croupier);
	}
	printf("\nMain du croupier : \n");
	afficherMain(croupier);
	printf("\n");
for(i = 0; i < nbP; i++) {
  if((((pTab[i].sommeMain > croupier->sommeMain) &&(pTab[i].sommeMain<=21)) || ((croupier->sommeMain > 21)&&(pTab[i].sommeMain<=21)) )&& tab_choix[i]==2){
	    pTab[i].stack=mise(&pTab[i],3);//gagner et a doubler
	    printf("%s gagne %d contre %d et a gagner 200 euros\t total stack:%d\n",pTab[i].nom, pTab[i].sommeMain, croupier->sommeMain,pTab[i].stack);
	    continue;
	  }
	  else if((pTab[i].sommeMain > 21&& tab_choix[i]==2) ||(((pTab[i].sommeMain < croupier->sommeMain)&&(pTab[i].sommeMain<21)&&(croupier->sommeMain<21)) && (tab_choix[i]==2))){
	    pTab[i].stack=mise(&pTab[i],4);//perdu et doubler
	      printf("%s a perdu avec %d et a perdu sa mise\t total stack:%d\n", pTab[i].nom, pTab[i].sommeMain,pTab[i].stack);
	      continue;
	    }

	  else if ((pTab[i].sommeMain > croupier->sommeMain &&(pTab[i].sommeMain<=21)) || ((croupier->sommeMain > 21) && (pTab[i].sommeMain<=21)) || (pTab[i].sommeMain==21&&(croupier->sommeMain<21||croupier->sommeMain>21))){
	    pTab[i].stack=mise(&pTab[i],1);//gagner
	    printf("%s gagne %d contre %d et a gagner 100 euros\t total stack:%d\n",pTab[i].nom, pTab[i].sommeMain, croupier->sommeMain,pTab[i].stack);
	  }

	  else if((pTab[i].sommeMain > 21 )|| ((pTab[i].sommeMain < croupier->sommeMain)&& (croupier->sommeMain<21))){
	    pTab[i].stack=mise(&pTab[i],0);//perdu
	    printf("%s a perdu avec %d et a perdu sa mise\t total stack:%d\n", pTab[i].nom, pTab[i].sommeMain,pTab[i].stack);
	  }

	  else if(pTab[i].sommeMain == croupier->sommeMain){
	    pTab[i].stack=mise(&pTab[i],2);//egalite
	    printf("%s est a egalite avec le croupier avec %d et a regagner sa mise\t total stack:%d\n", pTab[i].nom, pTab[i].sommeMain,pTab[i].stack);
	  }
	}
	printf("\n");
	printf("Voulez vous rejouer ? 0 pour non, 1 pour oui !");
	fgets(in, 10, stdin);
	i = atoi(in);
	if (i)
		goto debut;

}



