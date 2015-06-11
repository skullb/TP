#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FICHE_PRODUITS "produit.txt"
#define MAXCHAR 50
#define MAXTEXT 1000
#define MAXP_RODUITS 100
#define MAXPATH 150
#define NBRCMD 5
#define MESSAGE_SAISIE_CMD "Saisir une commande: "
#define MESSAGE_SAISIE_CMD_INVALIDE "Cette commande n'existe pas \n"
#define MESSAGE_CLIENT_REQUIS "Vous devez entrer un client d'abord \n"
#define MESSAGE_RECOMMENCER "Recommencer : "
#define MESSAGE_ERREUR_CHARGEMENT_PRODUIT "Une erreur de chargement c'est produite \n"
#define MESSAGE_SAISIE_NOM_CLIENT "Saisir le nom du client: "
#define VRAI 1
#define FAUX 0

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
int chargerProduit(Produit *pProduits[MAXP_RODUITS], Path pCheminDuFichier);

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
void saisieCommande(Produit *pListe[MAXP_RODUITS], int nbProduits);

/************************************************
*	creerFacture:
*	Fonction de création d'un fichier de facture en html.
*	pCommande: pointeur sur la liste des commandes
*			   et des quantitées
*
*	Retour: void
************************************************/
void creerFacture(Produit *pCommande[MAXP_RODUITS], Client *pClient, int nbProduits);

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

/************************************************
*	printCommande:
*	Fonction d'affichage des commandes faites
*	par le client
*	ptrProduits: pointeur sur la liste des
*				 produits avec la quantité
*	pNbProduits: Nombre de produits
*
*
*	Retour: void
************************************************/
void printCommande(Produit *ptrProduits[MAXP_RODUITS], int pNbProduits);

/*Fonction main*/
void main() {
	// lancement de l'application
	tableauDeBord();
}
/*Fonction tableauDeBord*/
void tableauDeBord(){
	int cmd, totalCommande, i, nbProduits = -1;
	String cmdDisponibles[NBRCMD] = { "0) Sortir du programme", "1)", "2)", "3)", "4" };
	Client *client = NULL;
	Produit *produits[MAXP_RODUITS] = {};
	// chargement des produits
	nbProduits = chargerProduit(produits, FICHE_PRODUITS);

	afficherCommandes(cmdDisponibles);
	printf(MESSAGE_SAISIE_CMD);
	cmd = saisieInt();

	while (cmd != 0)
	{
		switch (cmd){
		case 1:
			client = saisieClient();
			printf("Client %s %s \n", client->nom, client->prenom);
			break;
		case 2:
			if (NULL != client){				
				if (NULL != produits) {
					saisieCommande(produits, nbProduits);
				}
				else {
					printf(MESSAGE_ERREUR_CHARGEMENT_PRODUIT);
				}
			}
			else {
				printf(MESSAGE_CLIENT_REQUIS);
			}
			break;
		case 3:
			// imprimer la commande
			printCommande(produits, nbProduits);
			break;
		case 4:
			// créer un fichier de factures
			creerFacture(produits, client, nbProduits);
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
	// libérer la mémoire du client
	free(client);
	// libérer les produits
	nbProduits = sizeof(produits) / sizeof(Produit);
	for (i = 0; i < nbProduits; i++) {
		free(produits[i]);
	}
}

/* saisieString */
String *saisieString(){

	String val;
	String ligne;
	String *pointeur;
	int n;

	fgets(ligne, MAXCHAR + 1, stdin);
	n = sscanf(ligne, "%s", &val);

	while (n != 1) {
		printf(MESSAGE_RECOMMENCER);
		fgets(ligne, MAXCHAR + 1, stdin);
		n = sscanf(ligne, "%s", &val);
	}

	pointeur = (String *)malloc(strlen(val) + 1);
	strcpy(*pointeur, val);

	return pointeur;
}

/*Fonction chargerProduit*/
int chargerProduit(Produit *pProduits[MAXP_RODUITS], Path pCheminDuFichier){

	FILE *entree;
	Produit *res;
	Text ligne;
	int n, nbProduits = 0;
	// Ouverture des fichiers
	entree = fopen(pCheminDuFichier, "r");
	if (entree == NULL) {
		printf("Le fichier %s n'existe pas\n", pCheminDuFichier);
	}
	else {
		fgets(ligne, MAXTEXT, entree);
		// Lecture du fichier entree ligne par ligne
		while (!feof(entree)) {
			pProduits[nbProduits] = (Produit *)malloc(sizeof(Produit));
			n = sscanf(ligne, "%3d	%s	%s	%f", &pProduits[nbProduits]->noProduit, &pProduits[nbProduits]->marque, &pProduits[nbProduits]->reference, &pProduits[nbProduits]->prix);
			pProduits[nbProduits]->quantite = 0;

			if (n != 4){
				printf("Le fichier est mal formatté");
			}
			// lecture de la ligne suivannte
			fgets(ligne, MAXTEXT, entree);
			// incrémentation du nombre de produits
			nbProduits++;
		}
	}

	fclose(entree);

	return nbProduits;
}

/*Fonction saisieClient*/
Client *saisieClient(){
	Client *client = (Client *)malloc(sizeof(Client));
	String *nom, *prenom;
	printf(MESSAGE_SAISIE_NOM_CLIENT);
	nom = saisieString();
	strcpy(client->nom, *nom);
	free(nom);
	printf("\n Saisir le prénom du client: ");
	prenom = saisieString();
	strcpy(client->prenom, *prenom);
	free(prenom);

	return client;
}

/*Fonction saisieCommande*/
void saisieCommande(Produit *pListe[MAXP_RODUITS], int nbProduits){
	int i, noProduit, qt, trouve = FAUX, index, inventaireQt;
	index = -1;
	printf("Numéro du produit à commander:");
	noProduit = saisieInt();
	for (i = 0; i < nbProduits && !trouve; i++){
		if (pListe[i]->noProduit == noProduit){
			trouve = VRAI;
			index = i;
		}
	}
	while (!trouve)
	{
		printf("Ce numéro de produit n'existe pas");
		printf("Numéro du produit à commander:");
		noProduit = saisieInt();

		for (i = 0; i < nbProduits && !trouve; i++){
			if (pListe[i]->noProduit == noProduit){
				trouve = VRAI;
				index = i;
			}
		}
	}

	printf("Quantité à commander:");
	qt = saisieInt();

	if (index > -1){
		inventaireQt = pListe[index]->quantite + qt;
		if (qt == 0 || inventaireQt < 0){
			pListe[index]->quantite = 0;
		}
		else {
			pListe[index]->quantite = inventaireQt;
		}
	}
}

/*Fonction printCommande*/
void printCommande(Produit *ptrProduits[MAXP_RODUITS], int pNbProduits){
	int i, prixTotal;
	printf("Produit commandés:\n");
	for (i = 0; i < pNbProduits; i++){
		if (ptrProduits[i]->quantite > 0){
			printf("%3d	%s	%s	%f %d \n", ptrProduits[i]->noProduit, ptrProduits[i]->marque, ptrProduits[i]->reference, ptrProduits[i]->prix, ptrProduits[i]->quantite);
		}
	}
}

/*Fonction creerFacture*/
void creerFacture(Produit *pCommande[MAXP_RODUITS], Client *pClient, int nbProduits){
	Path facture;
	String nomPrenom;
	FILE *out;
	int i;
	float subTotal;
	float total = 0;
	
	// création du nom de fichier
	strcpy(facture, pClient->nom);
	strcat(facture, pClient->prenom);
	strcat(facture, ".html");

	// création de la concaténation de Nom Prénom
	strcpy(nomPrenom, pClient->nom);
	strcat(nomPrenom, " ");
	strcat(nomPrenom, pClient->prenom);

	out = fopen(facture, "w");

	if (NULL == out){
		printf("Erreur d'accès au fichier de facture");
	} else {
		
		fprintf(out,"<html>\n");
		fprintf(out, "\t<head>\n");
		// titre de la page
		fprintf(out, "\t\t<title>%s</title>\n", nomPrenom);
		fprintf(out, "\t</head>\n");
		fprintf(out, "\t<body>\n");
		// création de la table avec 
		// le header du tableau
		fprintf(out, "\t\t<table border=\"1px\">\n");
		fprintf(out, "\t\t\t<tr bgcolor=\"yellow\">\n");
		fprintf(out, "\t\t\t\t<th>No de produit</th>\n");
		fprintf(out, "\t\t\t\t<th>Marque</th>\n");
		fprintf(out, "\t\t\t\t<th>No de série</th>\n");
		fprintf(out, "\t\t\t\t<th>Quantité</th>\n");
		fprintf(out, "\t\t\t\t<th>Prix</th>\n");
		fprintf(out, "\t\t\t</tr>\n");
		
		// itération sur les produits
		for (i = 0; i < nbProduits; i++){

			// afficher que ceux dont la quantité est
			// supérieure à 0
			if (pCommande[i]->quantite > 0){
				// calcul du sous total et total
				subTotal = pCommande[i]->quantite * pCommande[i]->prix;
				total += subTotal;
				// création des lignes du  tableau
				fprintf(out, "\t\t\t<tr>\n");
				fprintf(out, "\t\t\t\t<td>%d</td>\n", &pCommande[i]->noProduit);
				fprintf(out, "\t\t\t\t<td>%s</td>\n", &pCommande[i]->marque);
				fprintf(out, "\t\t\t\t<td>%s</td>\n", &pCommande[i]->reference);
				fprintf(out, "\t\t\t\t<td>%d</td>\n", &pCommande[i]->quantite);
				fprintf(out, "\t\t\t\t<td>%f</td>\n", subTotal);
				fprintf(out, "\t\t\t</tr>\n");
			}
		}

		// ajout du pieds avec le total
		fprintf(out, "\t\t\t<tr>\n");
		fprintf(out, "\t\t\t\t<td><td>\n");
		fprintf(out, "\t\t\t\t<td><td>\n");
		fprintf(out, "\t\t\t\t<td><td>\n");
		fprintf(out, "\t\t\t\t<td>%f<td>\n", total);
		fprintf(out, "\t\t\t</tr>\n");
		fprintf(out, "\t\t</table>\n");
		fprintf(out, "\t</body>\n");
		fprintf(out, "</html>\n");
	}
	// sauver dans le fichier
	fclose(out);
}

/* saisie d'entiers*/
int saisieInt() {
	int val, n;
	char ligne[MAXCHAR];

	fgets(ligne, MAXCHAR, stdin),
		n = sscanf(ligne, "%d", &val);
	while (n != 1) {
		printf("Recommencer : ");
		fgets(ligne, MAXCHAR, stdin),
			n = sscanf(ligne, "%d", &val);
	}
	return val;
}

/* Fonction afficherCommande */
void afficherCommandes(String pCmdDisponibles[NBRCMD]){
	int i;
	int sousTotal = 0;
	printf("Commandes disponibles: \n");
	for (i = 0; i < NBRCMD; i++){
		printf("%s \n", pCmdDisponibles[i]);
	}
}