#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**************************************************
*
*	D�claration des constantes de langue fran�aise
*
**************************************************/

// messages d'erreurs
#define MESSAGE_ERREUR_CHARGEMENT_PRODUIT "Une erreur de chargement c'est produite \n"
#define MESSAGE_ERREUR_CREATION_FACTURE "Erreur de cr�ation du fichier de facture\n"
#define MESSAGE_ERREUR_FICHIER_MAL_FORMATE "Le fichier est mal formatte"
#define MESSAGE_ERREUR_FICHIER_INNEXISTANT "Le fichier %s n'existe pas\n"
#define MESSAGE_ERREUR_CLIENT_REQUIS "Vous devez entrer un client d'abord \n"
#define MESSAGE_ERREUR_FONCTION_INVALIDE "Cette fonction n'existe pas \n"
#define MESSAGE_ERREUR_PRODUIT_DEPASSEMENT "Les %d derni�res lignes n'ont pas pues etre chargees"

// messages de saisie
#define MESSAGE_SAISIE_RECOMMENCER "Recommencer : "
#define MESSAGE_SAISIE_CMD "Saisir une commande: "
#define MESSAGE_SAISIE_NOM_CLIENT "Saisir le nom du client: "
#define MESSAGE_SAISIE_PRENOM "Saisir le pr�nom du client: "

// message concernants le produit
#define MESSAGE_PRODUIT_NO "Num�ro du produit � commander:"
#define MESSAGE_PRODUIT_COMMANDE "Produits commandes:\n"
#define MESSGAE_PRODUIT_INNEXISTANT "Ce num�ro de produit n'existe pas"
#define MESSAGE_PRODUIT_QT_COMMANDE "Quantit� � commander:"

// constantes de tableau des produit
#define CONST_PRODUIT_NO "No"
#define CONST_PRODUIT_MARQUE "Marque"
#define CONST_PRODUIT_REFERENCE "Ref"
#define CONST_PRODUIT_PRIX "Prix"
#define CONST_PRODUIT_QUANTITE "Nb"
#define CONST_PRODUIT_TOTAL "Total"

// Fonctions disponibles
#define MESSAGE_CMD_DISPO "Fonctions disponibles: \n\n"
#define MESSAGE_CMD0 "Sortir du programme"
#define MESSAGE_CMD1 "Saisir le nom du client"
#define MESSAGE_CMD2 "Passer une commande"
#define MESSAGE_CMD3 "Imprimer la commande"
#define MESSAGE_CMD4 "Creer la facture"

/**************************************************
*
*	D�claration des constantes de configuration
*
**************************************************/
#define FICHE_PRODUITS "produit.txt"
#define MAXCHAR 50
#define MAXENTIER 50
#define MAXTEXT 1000
#define MAX_PRODUITS 100
#define MAXPATH 150
#define NBRCMD 5
#define VRAI 1
#define FAUX 0
#define MAX_PRODUIT_CHARGEMENT_ERREUR 3
#define ERREUR_PRODUIT_CHARGEMENT 0
#define ERREUR_PRODUIT_CHARGEMENT_FORMAT 1
#define ERREUR_PRODUIT_CHARGEMENT_DEPASSEMENT 2

/* On d�finie un type String avec une taille de MAXCHAR */
typedef char String[MAXCHAR];

/* On d�finit un type Text avec une taille de MAXTEXT*/
typedef char Text[MAXTEXT];

/* On d�finit un type Path pour les chemins de fichiers */
typedef char Path[MAXPATH];

/* On d�finit un type Produit */
typedef struct{
	int noProduit;
	String marque;
	String reference;
	float prix;
	int quantite;
} Produit;

/* On d�finit un type client */
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
*	produits bas�e sur un fichier texte d'une
*	certaine structure.
*	pProduits: pointeur sur la liste des commandes
*			   et des quantit�es
*	pCheminduFichier: le chemin du fichier des
*					  produits � charger
*	Erreurs: le traitement des erreurs essaie
*			 de charger les produits tant qu'il 
*			 y arrive et avise l'utilisateur
*			 des erreurs en donnant les lignes
*			 Si l'erreur n'est pas r�cup�rable
*			 il retournera 0
*
*	Retour: Un entier du nombre de produits 
			charg�s
************************************************/
int chargerProduit(Produit *pProduits[MAX_PRODUITS], Path pCheminDuFichier);

/************************************************
*	saisieClient:
*	Fonction de saisie du Client
*
*	Retour: le pointeur du client saisie
************************************************/
Client *saisieClient();

/************************************************
*	saisieCommande:
*	Fonction de saisie de l'operation demand�e par
*	l'utilisateur
*	pListe: pointeur sur la liste des commandes
*			   et des quantit�es
*	nbProduits: nombre de produits charg�s en
*				m�moire
*
*	Retour: void
************************************************/
void saisieCommande(Produit *pListe[MAX_PRODUITS], int nbProduits);

/************************************************
*	creerFacture:
*	Fonction de cr�ation d'un fichier de facture en html.
*	pCommande: pointeur sur la liste des commandes
*			   et des quantit�es
*	pClient: pointeur sur le client qui fait la
*			 commande
*	nbProduits: nombre de produits charg�s en
*				m�moire
*
*	Retour: void
************************************************/
void creerFacture(Produit *pCommande[MAX_PRODUITS], Client *pClient, int nbProduits);

/************************************************
*	tableauDeBord:
*	Fonction qui affiche un tableau de bord des
*	commandes disponibles du programme, et
*	les traitent.
*	Liste des commandes:
*		1) Saisir le nom du client
*		2) Passer une commande
*		3) Imprimer la commande
*		4) Creer la facture
*		0) Sortir du programme
*
*	Retour: void (int�ligence du programme)
************************************************/
void tableauDeBord();

/************************************************
*	afficherCommandes:
*	Fonction d'affichage des commandes mises �
*	disposition par le programme:
*	Liste des commandes:
*		1) Saisir le nom du client
*		2) Passer une commande
*		3) Imprimer la commande
*		4) Creer la facture
*		0) Sortir du programme
*	pCmdDisponibles: tableau des commandes �
*					 afficher
*
*	Retour: void (affiche en console)
************************************************/
void afficherCommandes(String pCmdDisponibles[NBRCMD]);

/************************************************
*	printCommande:
*	Fonction d'affichage des commandes faites
*	par le client
*	ptrProduits: pointeur sur la liste des
*				 produits avec la quantit�
*	pNbProduits: Nombre de produits
*
*
*	Retour: void
************************************************/
void printCommande(Produit *ptrProduits[MAX_PRODUITS], int pNbProduits);

/*Fonction main*/
void main() {
	// lancement de l'application
	tableauDeBord();
}
/*Fonction tableauDeBord*/
void tableauDeBord(){
	int cmd, totalCommande, i, nbProduits = -1;
	String cmdDisponibles[NBRCMD] = { MESSAGE_CMD0, MESSAGE_CMD1, MESSAGE_CMD2, MESSAGE_CMD3, MESSAGE_CMD4 };
	Client *client = NULL;
	Produit *produits[MAX_PRODUITS] = {};
	// chargement des produits
	nbProduits = chargerProduit(produits, FICHE_PRODUITS);

	afficherCommandes(cmdDisponibles);
	printf(MESSAGE_SAISIE_CMD);
	cmd = saisieInt();

	while (cmd != 0 && nbProduits > 0)
	{
		switch (cmd){
		case 1:
			// saisie du client
			client = saisieClient();
			break;
		case 2:
			if (NULL != client){	
				// saisir la commande du client
				saisieCommande(produits, nbProduits);
			}
			else {
				printf(MESSAGE_ERREUR_CLIENT_REQUIS);
			}
			break;
		case 3:
			// imprimer la commande
			printCommande(produits, nbProduits);
			break;
		case 4:
			// cr�er un fichier de factures
			creerFacture(produits, client, nbProduits);
			break;
		default:
			printf(MESSAGE_ERREUR_FONCTION_INVALIDE);
			break;
		}

		// Saisir une nouvelle commande
		printf(MESSAGE_SAISIE_CMD);
		cmd = saisieInt();
	}

	if (nbProduits == 0){
		// erreur de chargement des produits
		printf(MESSAGE_ERREUR_CHARGEMENT_PRODUIT);
	} else {
		// lib�rer la m�moire du client
		free(client);
		// lib�rer les produits
		nbProduits = sizeof(produits) / sizeof(Produit);
		for (i = 0; i < nbProduits; i++) {
			free(produits[i]);
		}
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
		printf(MESSAGE_SAISIE_RECOMMENCER);
		fgets(ligne, MAXCHAR + 1, stdin);
		n = sscanf(ligne, "%s", &val);
	}

	pointeur = (String *)malloc(strlen(val) + 1);
	strcpy(*pointeur, val);

	return pointeur;
}

/*Fonction chargerProduit*/
int chargerProduit(Produit *pProduits[MAX_PRODUITS], Path pCheminDuFichier){

	FILE *entree;
	Produit *res;
	Text ligne;
	String lignesErr = "";
	String noLigneErr = "";
	String separateur = "";
	String formatD;
	String format="%3d	";
	int i,erreurFormat, erreurDepassement, erreurChargement, n, indexErreurForm =0,indexErreurDep = 0, nbProduits = 0;
	int lignesNonChargees[MAX_PRODUIT_CHARGEMENT_ERREUR][MAX_PRODUITS] = {};

	erreurDepassement = FAUX;
	erreurFormat = FAUX;
	erreurChargement = FAUX;

	// d�finition du format dynamique pour sscanf
	sprintf(formatD, "%%%ds	%%%ds", MAXCHAR-1, MAXCHAR-1);
	strcat(format, formatD);
	strcat(format, "	%f");
	
	// Ouverture des fichiers
	entree = fopen(pCheminDuFichier, "r");
	if (entree == NULL) {
		erreurChargement = VRAI;
		lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT][0] = 1;
	}
	else {
		fgets(ligne, MAXTEXT, entree);
		// Lecture du fichier entree ligne par ligne
		while (!feof(entree)) {
			// contr�le de d�passement de tableau
			if (erreurFormat || nbProduits > MAX_PRODUITS){
				erreurFormat = VRAI;
				lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT_DEPASSEMENT] [indexErreurDep] = nbProduits + 1;

			} else {
				pProduits[nbProduits] = (Produit *)malloc(sizeof(Produit));
				n = sscanf(ligne, format, &pProduits[nbProduits]->noProduit, &pProduits[nbProduits]->marque, &pProduits[nbProduits]->reference, &pProduits[nbProduits]->prix);
				pProduits[nbProduits]->quantite = 0;

				if (n != 4){
					nbProduits = 0;
					erreurFormat = VRAI;
					lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT_FORMAT][indexErreurForm] = nbProduits + 1;
					indexErreurForm++;
				}
				else {
					// incr�mentation du nombre de produits
					nbProduits++;
				}
				// lecture de la ligne suivannte
				fgets(ligne, MAXTEXT, entree);
			}
		}
	}

	fclose(entree);

	// Afficher l'erreur pour le d�passement de tableau
	// l'erreur n'interompt pas le programme mais signale les lignes
	// non charg�es
	if (erreurChargement || erreurFormat || erreurDepassement) {
		
		if (lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT][0] == 1){
			printf(MESSAGE_ERREUR_FICHIER_INNEXISTANT);
		}
		else {
			// Si il y a des erreurs de formatage
			if (indexErreurForm > 0){
				// On it�re � quelles lignes
				// et on concat�ne en format lisible
				for (i = 0; i < indexErreurForm; i++){
					sprintf(noLigneErr, "%d", lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT_FORMAT][i]+1);
					strcat(lignesErr, separateur);
					strcat(lignesErr, noLigneErr);
					strcpy(separateur, ", ");
				}
				// On affiche l'erreur avec les lignes auxquels les
				// erreurs sont d�t�ct�es
				printf(MESSAGE_ERREUR_FICHIER_MAL_FORMATE, lignesErr);
			}

			// Si il y a d�passement
			if (indexErreurDep > 0) {
				// On it�re � quelles lignes
				// et on concat�ne en format lisible
				for (i = 0; i < indexErreurDep; i++) {
					sprintf(noLigneErr, "%d", lignesNonChargees[ERREUR_PRODUIT_CHARGEMENT_DEPASSEMENT][i] + 1);
					strcat(lignesErr, separateur);
					strcat(lignesErr, noLigneErr);
					strcpy(separateur, ", ");
				}
				// On affiche l'erreur avec les lignes auxquels les
				// erreurs sont d�t�ct�es
				printf(MESSAGE_ERREUR_PRODUIT_DEPASSEMENT, lignesErr);
			}
		}
	}

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
	printf(MESSAGE_SAISIE_PRENOM);
	prenom = saisieString();
	strcpy(client->prenom, *prenom);
	free(prenom);

	return client;
}

/*Fonction saisieCommande*/
void saisieCommande(Produit *pListe[MAX_PRODUITS], int nbProduits){
	int i, noProduit, qt, trouve = FAUX, index, inventaireQt;
	index = -1;
	printf(MESSAGE_PRODUIT_NO);
	noProduit = saisieInt();
	for (i = 0; i < nbProduits && !trouve; i++){
		if (pListe[i]->noProduit == noProduit){
			trouve = VRAI;
			index = i;
		}
	}
	while (!trouve)
	{
		printf(MESSGAE_PRODUIT_INNEXISTANT);
		printf(MESSAGE_PRODUIT_NO);
		noProduit = saisieInt();

		for (i = 0; i < nbProduits && !trouve; i++){
			if (pListe[i]->noProduit == noProduit){
				trouve = VRAI;
				index = i;
			}
		}
	}

	printf(MESSAGE_PRODUIT_QT_COMMANDE);
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
void printCommande(Produit *ptrProduits[MAX_PRODUITS], int pNbProduits){
	int i, prixTotal;
	String format;

	//d�finition du format dynamique
	sprintf(format,"%3d	%%%ds	%%%ds	%f %%%dd \n", MAXCHAR-1, MAXCHAR-1, MAXCHAR-1);

	printf(MESSAGE_PRODUIT_COMMANDE);
	for (i = 0; i < pNbProduits; i++){
		// seulement si un produit est command�
		if (ptrProduits[i]->quantite > 0){
			printf(format, ptrProduits[i]->noProduit, ptrProduits[i]->marque, ptrProduits[i]->reference, ptrProduits[i]->prix, ptrProduits[i]->quantite);
		}
	}
	puts("");
}

/*Fonction creerFacture*/
void creerFacture(Produit *pCommande[MAX_PRODUITS], Client *pClient, int nbProduits){
	Path facture;
	String nomPrenom;
	FILE *out;
	int i;
	float subTotal;
	float total = 0;
	
	// cr�ation du nom de fichier
	strcpy(facture, pClient->nom);
	strcat(facture, pClient->prenom);
	strcat(facture, ".html");

	// cr�ation de la concat�nation de Nom Pr�nom
	strcpy(nomPrenom, pClient->nom);
	strcat(nomPrenom, " ");
	strcat(nomPrenom, pClient->prenom);

	out = fopen(facture, "w");

	if (NULL == out){
		printf(MESSAGE_ERREUR_CREATION_FACTURE);
	} else {
		
		fprintf(out,"<html>\n");
		fprintf(out, "\t<head>\n");
		// titre de la page
		fprintf(out, "\t\t<title>%s</title>\n", nomPrenom);
		fprintf(out, "\t</head>\n");
		fprintf(out, "\t<body>\n");
		// cr�ation de la table avec 
		// le header du tableau
		fprintf(out, "\t\t<table border=\"1px\">\n");
		fprintf(out, "\t\t\t<tr bgcolor=\"yellow\">\n");
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PRODUIT_NO);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PRODUIT_MARQUE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PRODUIT_REFERENCE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n",CONST_PRODUIT_QUANTITE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PRODUIT_PRIX);
		fprintf(out, "\t\t\t</tr>\n");
		
		// it�ration sur les produits
		for (i = 0; i < nbProduits; i++){

			// afficher que ceux dont la quantit� est
			// sup�rieure � 0
			if (pCommande[i]->quantite > 0){
				// calcul du sous total et total
				subTotal = pCommande[i]->quantite * pCommande[i]->prix;
				total += subTotal;
				// cr�ation des lignes du  tableau
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
		fprintf(out, "\t\t\t\t<td>%s</td>\n", CONST_PRODUIT_TOTAL);
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td>%f</td>\n", total);
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
	char ligne[MAXENTIER];

	fgets(ligne, MAXENTIER, stdin),
		n = sscanf(ligne, "%d", &val);
	while (n != 1) {
		printf(MESSAGE_SAISIE_RECOMMENCER);
		fgets(ligne, MAXENTIER, stdin),
			n = sscanf(ligne, "%d", &val);
	}
	return val;
}

/* Fonction afficherCommande */
void afficherCommandes(String pCmdDisponibles[NBRCMD]){
	int i;
	int sousTotal = 0;
	printf(MESSAGE_CMD_DISPO);
	for (i = 0; i < NBRCMD; i++){
		printf("\t%1d) %s \n", i,pCmdDisponibles[i]);
	}
	puts("");
}