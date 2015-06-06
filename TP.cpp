#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXCHAR 50
#define MAXTEXT 1000
#define MAXPATH 150
#define NBRCMD 5
#define MESSAGE_SAISIE_CMD "Saisir une commande: "
#define MESSAGE_SAISIE_CMD_INVALIDE "Cette commande n'existe pas /n"

/* On définie un type String avec une taille de MAXCHAR */
typedef char String[MAXCHAR];
/* On définit un type Text avec une taille de MAXTEXT*/
typedef char Text[MAXTEXT];
/* On définit un type Path pour les chemins de fichiers */
typedef char Path[MAXPATH];
/* On définit un type Produit */
typedef struct{
	int noProduit;
	String marque;
	String reference;
	float prix;
	int quantite;
} Produit;
/* On définit un type client */
typedef struct{
	String nom;
	String prenom;
} Client;

/************************************************	
*	saisieInt:
*	Fonction de saisie d'un nombre entier
*	Retour: l'entier saisie par l'utilisateur
************************************************/
int saisieInt();

/************************************************
*	saisieString:
*	Fonction de saisie d'un String d'une taille
*	de MAXCHAR.
*	Retour: le String saisie d'une taille de 
*			MAXCHAR
************************************************/
String *saisieString();

/************************************************
*	saisieFloat:
*	Fonction de saisie d'un nombre flottant
*	Retour: le nombre flottant saisie par 
*   INUTILE
************************************************/
float saisieFloat();

/************************************************
*	chargerProduit:
*	Fonction de de chargement de la liste des
*	produits basée sur un fichier texte d'une
*	certaine structure.
*
*	pCheminduFichier: le chemin du fichier des
*					  produits à charger
*
*	Retour: Un pointeur sur un tableau de 
*			produits
************************************************/
Produit *chargerProduit(Path pCheminDuFichier);

/************************************************
*	saisieClient:
*	Fonction de saisie du Client
*
*	Retour: le pointeur du client saisie
************************************************/
Client *saisieClient();

/************************************************
*	saisieCommande:
*	Fonction de saisie de l'operation demandée par
*	l'utilisateur
*
*	Retour: void
************************************************/
void saisieCommande(Produit *pListe);

/************************************************
*	creerFacture:
*	Fonction de création d'un fichier de facture en html.
*	pCommande: pointeur sur la liste des commandes
*			   et des quantitées
*
*	Retour: void
************************************************/
void creerFacture(Produit *pCommande);

/************************************************
*	tableauDeBord:
*	Fonction qui affiche un tableau de bord des
*	commandes disponibles du programme, et 
*	les traitent.
*
*	Liste des commandes:
*		1)
*		2)
*		3)
*		4)
*		0) Sortir du programme
*	
*
*	Retour: void
************************************************/
void tableauDeBord();

/************************************************
*	afficherCommandes:
*	Fonction d'affichage des commandes mises à 
*	disposition par le programme
*	pCmdDisponibles: tableau des commandes à
*					 afficher
*
*	Retour: void
************************************************/
void afficherCommandes(String pCmdDisponibles[NBRCMD]);


void main() {
	// lancement de l'application
	tableauDeBord();
}

void tableauDeBord(){
	int cmd, totalCommande;
	String cmdDisponibles[NBRCMD] = { "0) Sortir du programme", "1)", "2)", "3)", "4" };
	Client *client = NULL;
	Produit *produits = NULL;
	
	afficherCommandes(cmdDisponibles);
	printf("Saisir une commande:");
	cmd = saisieInt();

	while (cmd != 0)
	{
		switch (cmd){
		case 1:
			client = saisieClient();
			break;
		case 2:
			if (client != NULL){
				produits = chargerProduit("Produits.txt");
				if (NULL != produits) {
					saisieCommande(produits);
				}
				else {
					printf("Une de chargement c'est produite");
				}
			}
			else {
				printf("Vous devez entrer un client d'abord");
			}
			break;
		case 3:
			// imprimer la commande
			int i;
			
			break;
		case 4:
			// créer un fichier de factures
			break;
		default:
			printf(MESSAGE_SAISIE_CMD_INVALIDE);
			break;
		}

		// afficher les commandes disponibles
		afficherCommandes(cmdDisponibles);
		// Saisir une nouvelle commande
		printf(MESSAGE_SAISIE_CMD);
		cmd = saisieInt();
	}
}

/* saisieString */
String *saisieString(){

	String val;
	String ligne;
	String *pointeur;
	int n;

	fgets(ligne, 20, stdin),
		n = sscanf(ligne, "%s", &val);

	while (n != 1) {
		printf("Recommencer : ");
		fgets(ligne, 20, stdin),
			n = sscanf(ligne, "%s", &val);
	}

	pointeur = (String *) malloc(strlen(val) + 1);
	strcpy(*pointeur, val);

	return pointeur;
}