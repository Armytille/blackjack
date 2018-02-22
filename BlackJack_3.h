#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>

#define NB_CARTES_MAX ((52)*(6))
#define NB_TAILLE_MAIN 12

///L'indice marquant la fin du paquet, utilisé pour séparer les cartes piochées et celle qui ne le sont pas lord de l'RNG san remise.
int indice_fin_Paquet;

///Un tableau stockant le nom de chaque valeur (utilisé pour l'affichage).
char ** valeur;

///Un tableau stockant le nom de chaque couleur (utilisé pour l'affichage).
char ** couleur;

enum {PIQUE,COEUR,CARREAU,TREFLE};
enum {AS,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,NEUF,DIX,VALET,REINE,ROI};
enum {/**1**/SAUTE=1, /**2**/BLACKJACK=2, /**3**/VINGTETUN=3};

///Structure correspondant a une carte, définie par une couleur, une valeur et un nom.
typedef struct Carte{
	///La couleur de la carte.
    int couleur;

    ///La valeur de la carte.
    int valeur;

    ///"L'apparence" de la carte, séparé de la valeur et utilisé pour l'affichage.
    int nom;
}Carte;

///Un tableau de Carte de taille ::NB_CARTES_MAX destiné a stocker les cartes à piocher.
Carte Paquet[NB_CARTES_MAX];

///Structure correspondant a un joueur, contenant sa main, le nombre de carte dans sa main, la somme de sa main, son nom et son score.
typedef struct Joueur{
	///Un tableau stockant chaque carte de la main du joueur.
    Carte main[NB_TAILLE_MAIN];

    ///Le nombre de cartes dans la main du joueur.
    int nb_Carte;

    ///La valeur totale de la main du joueur.
    int sommeMain;

    ///Le nom du joueur.
    char nom[30];

    ///La valeur totale des jetons du joueur (comme un score).
	int stack;
}Joueur;

///Cette fonction remplie le tableau ::Paquet avec 6 paquets de 52 cartes soit un total de 312 Cartes.
void initialisation_Paquet();

///Calcule la somme des cartes du Joueur <b>player</b>.
int JoueurTotalCartes(Joueur* player);

///Affiche la main du Joueur <b>player</b>.
void afficherMain(Joueur* player);

///Réinitialise la main du Joueur <b>player</b> et lui ajoute <b>nb_Carte</b> Carte.
void distribuer(Joueur* player,int nb_Carte);

///Ajoute un nombre de Carte <b>nb_Carte</b> à la main du Joueur <b>player</b>.
void draw(Joueur* player,int nb_Carte);

///Retourne une valeur correspondant au "status" du Joueur <b>player</b>.
char blackjack(Joueur* player,char print);

///Change le stack(alias score) du Joueur <b>player</b> en fonction du résultat du jeu précisé via l'argument <b>res</b>.
int mise(Joueur* player, int res);

///Fonction gérant la totalité du jeu.
void jeu(Joueur pTab[], Joueur* croupier, int nbP);
