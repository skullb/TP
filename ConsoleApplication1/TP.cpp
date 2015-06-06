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
Produit **chargerProduit(Path pCheminDuFichier);

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
	Produit **produits = NULL;
	
	afficherCommandes(cmdDisponibles);
	printf("Saisir une commande:");
	cmd = saisieInt();

	while (cmd != 0)
	{
		switch (cmd){
		case 1:
			client = saisieClient();
			printf("Client %s %s", client->nom, client->prenom);
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
			//int i;
			
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
String *saisieString(int pMaxSize){

	String val;
	String ligne;
	String *pointeur;
	int n;

	fgets(ligne, MAXCHAR + 1, stdin);
	n = sscanf(ligne, "%s", &val);

	while (n != 1) {
		printf("Recommencer : ");
		fgets(ligne, MAXCHAR + 1, stdin);
		n = sscanf(ligne, "%s", &val);
	}

	pointeur = (String *) malloc(strlen(val) + 1);
	strcpy(*pointeur, val);

	return pointeur;
}

Produit *donneProduit(Text *pLigneExtraire){
	Produit *produit;
	return produit;
}

Produit **chargerProduit(Path pCheminDuFichier){
	Produit *produit[MAXCHAR];
	FILE *entree;
	Text ligne;
	Text *ligneReelle;
	int nbProduits = 0;
	// Ouverture des fichiers
	entree = fopen(pCheminDuFichier, "r");
	if (entree == NULL) {
		printf("Le fichier %s n'existe pas\n", pCheminDuFichier);
	}
	else {
		fgets(ligne, MAXTEXT, entree);
		// Lecture du fichier entree ligne par ligne
		while (!EOF) {
			// allocation de la taille réelle
			ligneReelle = (Text *) malloc(strlen(ligne) + 1);
			// copie dans le pointeur
			strcpy(*ligneReelle, ligne);
			// stockage du produit dans le tableau
			produit[nbProduits] = donneProduit(ligneReelle);
			// lecture de la ligne suivannte
			fgets(ligne, MAXTEXT, entree);
			// incrémentation du nombre de produits
			nbProduits++;
		}
	}
	
	fclose(entree);

	return produit;
}


Client *saisieClient(){
	Client *client = (Client *)malloc(sizeof(Client));
	String *nom, *prenom;
	printf("\n Saisir le nom du client: ");
	nom = saisieString();
	strcpy(client->nom, *nom);
	printf("\n Saisir le prénom du client: ");
	prenom = saisieString();
	strcpy(client->prenom, *prenom);
	return client;
}

void saisieCommande(Produit **pListe){
}

void creerFacture(Produit *pCommande){
}

int saisieInt(int pMaxSize) {
	int val, n;
	char ligne[20];

	fgets(ligne, 20, stdin),
		n = sscanf(ligne, "%d", &val);
	while (n != 1) {
		printf("Recommencer : ");
		fgets(ligne, 20, stdin),
			n = sscanf(ligne, "%d", &val);
	}
	return val;
}

void afficherCommandes(String pCmdDisponibles[NBRCMD]){
	int i;
	int sousTotal = 0;
	printf("Commande disponibles: \n");
	for (i = 0; i < MAXTEXT; i++){
		printf("%s", pCmdDisponibles[i]);
	}
}