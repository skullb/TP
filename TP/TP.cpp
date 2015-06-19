#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/**************************************************
*
*	Déclaration des constantes de langue française
*
**************************************************/

// Messages d'erreurs
#define MSG_ERR_CHARGEMENT_PROD "Une erreur de chargement s'est produite \n"
#define MSG_ERR_CREATION_FACTURE "Erreur de creation du fichier de facture\n"
#define MSG_ERR_FICHIER_MAL_FORMATE "Le fichier de produits est mal formate.\nLes lignes %s n'ont pas pu etre chargees\n"
#define MSG_ERR_FICHIER_INNEXISTANT "Le fichier %s n'existe pas\n"
#define MSG_ERR_CLIENT_REQUIS "Vous devez entrer un client d'abord \n"
#define MSG_ERR_FONCTION_INVALIDE "Cette fonction n'existe pas \n"
#define MSG_ERR_PROD_DEPASSEMENT "Les lignes %s du fichier de produit\n n'ont pas pu etre chargees\n"
#define MSG_ERR_COMMANDE_REQUISE "Une commande doit etre effectuee pour etre affichee\n"

// Message d'attention
#define MSG_ATT_CLIENT_NON_FACTURE "Le client %s %s a effectue une commande.\nElle n'a cependant pas ete facturee.\nSi vous continuez vous ecraserez ces donnees.\n"

// Messages de saisie
#define MSG_SAISIE_RECOMMENCER "Recommencer : "
#define MSG_SAISIE_CMD "Saisir une commande: "
#define MSG_SAISIE_NOM_CLIENT "Saisir le nom du client: "
#define MSG_SAISIE_PRENOM "Saisir le prenom du client: "
#define MSG_SAISIE_SUR "Etes-vous sur de vouloir continuer(o/n)? "

// Messages concernant le produit
#define MSG_PROD_NO "Numero du produit a commander:"
#define MSG_PROD_COMMANDE "Produits commandes:\n"
#define MSG_PROD_INNEXISTANT "Ce numero de produit n'existe pas\n"
#define MSG_PROD_QT_COMMANDE "Quantite a commander:"
#define MSG_PROD_DISPO "Produits disponibles:\n"
#define MSG_PROD_COMMANDE_DET "Commande de %d %s %s, prix unitaire : %.2f FS, prix total ; %.2f FS\n"
#define MSG_PROD_COMMANDE_DET_ANNULE "La commande de %s %s est annulee\n" 

// Constantes de tableau des produits
#define CONST_PROD_NO "No"
#define CONST_PROD_MARQUE "Marque"
#define CONST_PROD_REFERENCE "Ref"
#define CONST_PROD_PRIX "Prix"
#define CONST_PROD_QUANTITE "Nb"
#define CONST_PROD_TOTAL "Total"
#define CONST_SEPARATEUR "-"
#define CONST_CLIENT "Client"
#define CONST_FACTURE_DE "Facture de"

// Fonctions disponibles
#define MSG_CMD_DISPO "Fonctions disponibles: \n\n"
#define MSG_CMD0 "Sortir du programme"
#define MSG_CMD1 "Saisir le nom du client"
#define MSG_CMD2 "Passer une commande"
#define MSG_CMD3 "Imprimer la commande"
#define MSG_CMD4 "Creer la facture"

/**************************************************
*
*	Déclaration des constantes de configuration
*
**************************************************/
#define FICHE_PROD "produit.txt"
#define MAX_PROD_CAR 3
#define MAX_CHAINE 50
#define MAX_ENTIER 50
#define MAX_CELL 10
#define MAX_TEXT 1000
#define MAX_PROD 10
#define MAX_PATH 150
#define NBRCMD 5
#define VRAI 1
#define FAUX 0
#define MAX_PROD_CHARGEMENT_ERREUR 3
#define ERR_PROD_CHARGEMENT 0
#define ERR_PROD_CHARGEMENT_FORMAT 1
#define ERR_PROD_CHARGEMENT_DEPASSEMENT 2

/************************************************
*	String:
*	Définition d'un type String utilisé pour
*	toutes les entrées de caractère de taille 50 
************************************************/
typedef char String[MAX_CHAINE];

/************************************************
*	Text:
*	Définition d'un type Text pour lire les 
*	lignes d'un fichier 
************************************************/
typedef char Text[MAX_TEXT];

/************************************************
*	Path:
*	Définition d'un type Path utilisé pour
*	les chemins de fichiers
************************************************/
typedef char Path[MAX_PATH];

/************************************************
*	Produit:
*	Définition d'un type Produit contenant le
*	numéro du produit, la marque, la réference,  
*	le prix et la quatité
************************************************/
typedef struct{
	int noProduit;
	String marque;
	String reference;
	float prix;
	int quantite;
} Produit;

/************************************************
*	Client:
*	Définition du type client contenant le nom et
*	le prénom du client
************************************************/
typedef struct{
	String nom;
	String prenom;
} Client;

/************************************************
*	saisieEntier:
*	Fonction de saisie d'un nombre entier
*	Retour: l'entier saisie par l'utilisateur
************************************************/
int saisieEntier();

/************************************************
*	saisieChaine:
*	Fonction de saisie d'un String d'une taille
*	de MAX_CHAINE. Avec un filtre de caractères
*	pour couper dès l'entrée d'un chiffre ou
*	autres caractères ne faisant pas partie
*	de la classe [a-zA-z ] les espaces sont
*	autorisés.
*	Retour: le String saisie d'une taille de
*			MAX_CHAINE
************************************************/
String *saisieChaine();

/************************************************
*	etesVousSur:
*	Qui demande si l'utilisateur est sur
*	de vouloir continuer
*	Retour: 1 si oui sinon 0
************************************************/
int etesVousSur();

/************************************************
*	chargerProduit:
*	Fonction de chargement de la liste des
*	produits basée sur un fichier texte d'une
*	certaine structure.
*	pProduits: pointeur sur la liste des commandes
*			   et des quantitées
*	pCheminduFichier: le chemin du fichier des
*					  produits à charger
*	Erreurs: le traitement des erreurs essaie
*			 de charger les produits tant qu'il 
*			 y arrive et avise l'utilisateur
*			 des erreurs en donnant les lignes
*			 Si l'erreur n'est pas récupérable
*			 il retournera 0
*
*	Retour: Un entier du nombre de produits 
			chargés
************************************************/
int chargerProduit(Produit *pProduits[MAX_PROD], Path pCheminDuFichier);

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
*	pListe: pointeur sur la liste des commandes
*			   et des quantitées
*	nbProduits: nombre de produits chargés en
*				mémoire
*
*	Retour: void
************************************************/
void saisieCommande(Produit *pListe[MAX_PROD], int nbProduits);

/************************************************
*	creerFacture:
*	Fonction de création d'un fichier de facture en html.
*	pCommande: pointeur sur la liste des commandes
*			   et des quantitées
*	pClient: pointeur sur le client qui fait la
*			 commande
*	nbProduits: nombre de produits chargés en
*				mémoire
*
*	Retour: void
************************************************/
void creerFacture(Produit *pCommande[MAX_PROD], Client *pClient, int nbProduits);

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
*	Retour: void (intéligence du programme)
************************************************/
void tableauDeBord();

/************************************************
*	afficherFonctionsDisponibles:
*	Fonction d'affichage des fonctions mises à
*	disposition par le programme:
*	Liste des commandes:
*		1) Saisir le nom du client
*		2) Passer une commande
*		3) Imprimer la commande
*		4) Creer la facture
*		0) Sortir du programme
*	pCmdDisponibles: tableau des commandes à
*					 afficher
*
*	Retour: void (affiche en console)
************************************************/
void afficherFonctionsDisponibles(String pCmdDisponibles[NBRCMD]);

/************************************************
*	imprimerProduits:
*	Fonction d'affichage des produits passés en
*	paramêtre
*	ptrProduits: pointeur sur la liste des
*				 produits avec la quantité
*	pNbProduits: Nombre de produits
*	pMontrerCommandes: 1 pour montrer quantité
*					   et prix et 0 que les 
*					   produits
*
*	Retour: void
************************************************/
void imprimerProduits(Produit *ptrProduits[MAX_PROD], int pNbProduits, int pMontrerCommandes);

/************************************************
*	effacerCommande:
*	Fonction qui parcours les produit et 
*	remet à 0 les quantités différentes de 0
*	ptrProduits: pointeur sur la liste des
*				 produits avec la quantité
*	pNbProduits: Nombre de produits
*
*	Retour: void
************************************************/
void effacerCommande(Produit *ptrProduits[MAX_PROD], int pNbProduits);

/*Fonction main*/
void main() {
	
	// lancement de l'application
	tableauDeBord();
	system("Pause");
}
/*Fonction tableauDeBord*/
void tableauDeBord(){
	
	int cmd;
	int produitsAffiches;
	int commandeEffectuee;
	int commandeFacturee;
	int totalCommande;
	int i, nbProduits, n, initialiser;
	String cmdDisponibles[NBRCMD] = { MSG_CMD0, MSG_CMD1, MSG_CMD2, MSG_CMD3, MSG_CMD4 };
	Client *client = NULL;
	Produit *produits[MAX_PROD] = {};

	nbProduits = -1;
	initialiser = FAUX;
	commandeEffectuee = FAUX;
	commandeFacturee = FAUX;

	// chargement des produits
	nbProduits = chargerProduit(produits, FICHE_PROD);

	//le nombre de produits > 0 
	if (nbProduits > 0){

		// affichage des fonctions disponibles
		afficherFonctionsDisponibles(cmdDisponibles);

		// demander de saisir une fonction
		printf(MSG_SAISIE_CMD);
		cmd = saisieEntier();

		// tant que la cmd n'est pas 0 
		while (cmd != 0)
		{
			if (!initialiser){
			
				if (commandeEffectuee || commandeFacturee){
					// on efface la commande précédente
					effacerCommande(produits, nbProduits);
				}
				// chaque nouveau client on veux afficher les produits
				produitsAffiches = FAUX;

				// réinitialiser la commandeEffectuée à FAUX
				commandeEffectuee = FAUX;

				// réinitialiser la commande facturée
				commandeFacturee = FAUX;

				// l'application est réinitialisée
				initialiser = VRAI;
			}

			switch (cmd){
			case 1:
			
				// si le client n'est pas saisie ou qu'aucune commande n'est efféctuée
				// ou que la commande précédent est facturée
				if (client == NULL || !commandeEffectuee || commandeFacturee){
				
					// saisie du client sans poser de question
					client = saisieClient();

					// réinitialiser
					initialiser = FAUX;
				}
				else {
				
					// le traitement des autres cas n'es pas utile
					// car la commande ne peut etre effectuée si le client
					// est NULL donc seul le cas commande effectuée
					// et non facturée passera par ici
					printf(MSG_ATT_CLIENT_NON_FACTURE, client->nom, client->prenom);

					// si la réponse est o ou O on saisie le client
					// sinon le programme continue
					if (etesVousSur()){
					
						// on demande la saisie du client
						client = saisieClient();

						// réinitialiser
						initialiser = FAUX;
					}
				}
				break;
			case 2:
				if (NULL != client){	

					// montrer que la première fois
					if (!produitsAffiches){
					
						// imprimer le nom du client
						printf("%s: %s %s\n", CONST_CLIENT, client->nom, client->prenom);

						// montrer les produits disponibles
						imprimerProduits(produits, nbProduits, FAUX);

						// pour ne plus afficher
						produitsAffiches = VRAI;
					}

					// saisir la commande du client
					saisieCommande(produits, nbProduits);

					// si et seulement si des produits sont 
					// commandés on affecte vrai à commandeEffectuee
					commandeEffectuee = FAUX;
					for (i = 0; i < nbProduits && !commandeEffectuee; i++){
						if (produits[i]->quantite > 0){
							commandeEffectuee = VRAI;
						}
					}
				}
				else {

					// affichage de l'erreur
					printf(MSG_ERR_CLIENT_REQUIS);
				}
				break;
			case 3:
				// On imprime la commande si et seulement
				// si une commande est effectuée
				if (commandeEffectuee){
				
					// imprimer la commande
					imprimerProduits(produits, nbProduits, VRAI);
				}
				else {
					
					// afficher l'erreur
					printf(MSG_ERR_COMMANDE_REQUISE);
				}
				break;
			case 4:
				// si et seulement si une commande est faite 
				if (commandeEffectuee){
					
					// créer un fichier de factures
					creerFacture(produits, client, nbProduits);
					commandeFacturee = VRAI;
				}
				else{

					// affichage de l'erreur
					printf(MSG_ERR_COMMANDE_REQUISE);
				}
				break;
			default:

				// fonction non valide
				printf(MSG_ERR_FONCTION_INVALIDE);
				break;
			}

			// Saisir une nouvelle commande
			printf(MSG_SAISIE_CMD);
			cmd = saisieEntier();
		}

		// libérer la mémoire du client
		if (NULL != client){
			free(client);
		}
		
		// libérer les produits
		for (i = 0; i < nbProduits; i++) {
			if (NULL != produits[i]){
				free(produits[i]);
			}
		}	
	}
	else {

		// erreur de chargement des produits
		printf(MSG_ERR_CHARGEMENT_PROD);
	}
}

/* saisieChaine */
String *saisieChaine(){

	String val;
	String valide = "";
	String ligne;
	String *pointeur = NULL;


	int n, i, j = 0;

	fgets(ligne, MAX_CHAINE + 1, stdin);
	n = sscanf(ligne, "%[^\n]", &val);

	while (n != 1) {
		printf(MSG_SAISIE_RECOMMENCER);
		fgets(ligne, MAX_CHAINE + 1, stdin);
		n = sscanf(ligne, "%[^\n]", &val);
	}

	// on enlève les caractères non désirés 
	// on admet les lettres de l'alphabets et les
	// espaces et les é, è et ë
	for (i = 0; i < strlen(val); i++){
		if (isalpha((unsigned char)val[i]) 
			|| val[i] == ' ' 
			|| val[i] == 'é'
			|| val[i] == 'è'
			|| val[i] == 'ë'){
			valide[j] = val[i];
			j++;
		}
	}

	pointeur = (String *)malloc(strlen(valide) + 1);

	if (NULL != pointeur){
		strcpy(*pointeur, valide);
	}

	return pointeur;
}

/*Fonction chargerProduit*/
int chargerProduit(Produit *pProduits[MAX_PROD], Path pCheminDuFichier){

	int i, j, n;
	
	// pseudo booléens
	int erreurFormat;
	int erreurDepassement;
	int erreurChargement;

	// index des erreurs
	int indexErreurForm = 0; 
	int indexErreurDep = 0;
	int nbProduits = 0;
	int noLigne = 1;

	FILE *entree;
	Text ligne;
	String lignesErr = "";
	String noLigneErr = "";
	String separateur = "";
	String format;
	String formatter = "%%%dd	%%%ds	%%%ds	%%f";
	
	int lignesNonChargees[MAX_PROD_CHARGEMENT_ERREUR][MAX_PROD] = {};

	erreurDepassement = FAUX;
	erreurFormat = FAUX;
	erreurChargement = FAUX;

	// définition du format dynamique pour sscanf
	sprintf(format, formatter,MAX_PROD_CAR, MAX_CHAINE-1, MAX_CHAINE-1);
	
	// Ouverture des fichiers
	entree = fopen(pCheminDuFichier, "r");
	if (entree == NULL) {
		erreurChargement = VRAI;
		lignesNonChargees[ERR_PROD_CHARGEMENT][0] = 1;
	}
	else {
		fgets(ligne, MAX_TEXT, entree);
		
		// Lecture du fichier entree ligne par ligne
		while (!feof(entree)) {

			// contrôle de dépassement de tableau
			if (erreurDepassement || nbProduits == MAX_PROD){
				
				// première erreur de dépassement
				// il faut ajuster nbProduits
				if (!erreurDepassement){
					
					// ajuster nbProduits
					nbProduits = nbProduits - 1;

					// il y a une erreur de dépassement
					erreurDepassement = VRAI;
				}

				
				lignesNonChargees[ERR_PROD_CHARGEMENT_DEPASSEMENT] [indexErreurDep] = noLigne;
				indexErreurDep++;

			} else {
				pProduits[nbProduits] = (Produit *)malloc(sizeof(Produit));
				if (NULL != pProduits){
					n = sscanf(ligne, format, &pProduits[nbProduits]->noProduit,
						&pProduits[nbProduits]->marque, &pProduits[nbProduits]->reference,
						&pProduits[nbProduits]->prix);
					pProduits[nbProduits]->quantite = 0;

					if (n != 4){
						erreurFormat = VRAI;
						lignesNonChargees[ERR_PROD_CHARGEMENT_FORMAT][indexErreurForm] = noLigne;
						indexErreurForm++;
					}
					else {
						// incrémentation du nombre de produits
						nbProduits++;
					}
				}
			}

			// lecture de la ligne suivante
			fgets(ligne, MAX_TEXT, entree);
			noLigne++;
		}

		fclose(entree);
	}

	

	// Afficher les erreurs diverses selon les problèmes rencontrés
	// l'erreur n'interompt pas le programme autant que possible
	// mais signale les lignes non chargées. Seul le fichier innexistant 
	// est bloquant pour l'application
	if (erreurChargement || erreurFormat || erreurDepassement) {
		
		if (lignesNonChargees[ERR_PROD_CHARGEMENT][0] == 1){
			printf(MSG_ERR_FICHIER_INNEXISTANT, pCheminDuFichier);
		}
		else {
			// Si il y a des erreurs de formatage
			if (indexErreurForm > 0){
				// On itère à quelles lignes
				// et on concatène en format lisible
				for (i = 0; i < indexErreurForm; i++){
					sprintf(noLigneErr, "%d", lignesNonChargees[ERR_PROD_CHARGEMENT_FORMAT][i]);
					strcat(lignesErr, separateur);
					strcat(lignesErr, noLigneErr);
					strcpy(separateur, ", ");
				}
				// On affiche l'erreur avec les lignes auxquels les
				// erreurs sont détéctées
				printf(MSG_ERR_FICHIER_MAL_FORMATE, lignesErr);
			}

			// Si il y a dépassement
			if (indexErreurDep > 0) {
				// On itère à quelles lignes
				// et on concatène en format lisible
				strcpy(separateur, "");
				strcpy(lignesErr, "");
				for (j = 0; j < indexErreurDep; j++) {
					sprintf(noLigneErr, "%d", lignesNonChargees[ERR_PROD_CHARGEMENT_DEPASSEMENT][j]);
					strcat(lignesErr, separateur);
					strcat(lignesErr, noLigneErr);
					strcpy(separateur, ", ");
				}
				// On affiche l'erreur avec les lignes auxquels les
				// erreurs sont détéctées
				printf(MSG_ERR_PROD_DEPASSEMENT, lignesErr);
			}
		}
	}

	// car jusqu'ici c'était l'index
	nbProduits = nbProduits + 1;

	return nbProduits;
}

/*Fonction saisieClient*/
Client *saisieClient(){
	
	Client *client = (Client *)malloc(sizeof(Client));
	String *nom, *prenom;

	// On demande le nom du client
	printf(MSG_SAISIE_NOM_CLIENT);
	nom = saisieChaine();
	
	// On stocke le prénom que si le pointeur est 
	// valide. Puis on le libère
	if (NULL != nom){
		strcpy(client->nom, *nom);
		free(nom);
	}
	
	// on demande le prénom du client
	printf(MSG_SAISIE_PRENOM);
	prenom = saisieChaine();
	
	// On stocke le prénom que si le pointeur est 
	// valide. Puis on le libère
	if (NULL != prenom){
		strcpy(client->prenom, *prenom);
		free(prenom);
	}

	return client;
}

/*Fonction saisieCommande*/
void saisieCommande(Produit *pListe[MAX_PROD], int nbProduits){
	int i, noProduit, qt, trouve = FAUX, index, inventaireQt;
	float total;
	index = -1;
	printf(MSG_PROD_NO);
	noProduit = saisieEntier();
	for (i = 0; i < nbProduits && !trouve; i++){
		if (pListe[i]->noProduit == noProduit){
			trouve = VRAI;
			index = i;
		}
	}
	while (!trouve)
	{
		printf(MSG_PROD_INNEXISTANT);
		printf(MSG_PROD_NO);
		noProduit = saisieEntier();

		for (i = 0; i < nbProduits && !trouve; i++){
			if (pListe[i]->noProduit == noProduit){
				trouve = VRAI;
				index = i;
			}
		}
	}

	printf(MSG_PROD_QT_COMMANDE);
	qt = saisieEntier();

	if (index > -1){
		inventaireQt = pListe[index]->quantite + qt;
		if (qt == 0 || inventaireQt < 0){
			pListe[index]->quantite = 0;
		}
		else {
			pListe[index]->quantite = inventaireQt;
		}
	}

	// Si la quantité est sup à 0
	if (0 < pListe[index]->quantite){
		// calculer le total
		total = pListe[index]->quantite * pListe[index]->prix;
		printf(MSG_PROD_COMMANDE_DET, pListe[index]->quantite,
			pListe[index]->marque, pListe[index]->reference, pListe[index]->prix, total);
	}
	else {
		printf(MSG_PROD_COMMANDE_DET_ANNULE, pListe[index]->marque, pListe[index]->reference);
	}
}

/*Fonction imprimerProduits*/
void imprimerProduits(Produit *ptrProduits[MAX_PROD], int pNbProduits, int pMontrerCommandes){
	int i, j, tailleSepar;
	float prixTotal = 0, sousTotal = 0;
	char *separator;
	String format;
	String formatEnTete;
	String formatPied;
	String formaterEnTete = "%%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%-%ds\n";
	String formaterPied = "%%-%ds %%-%ds %%-%ds %%-%ds %%-%ds %%%d.2f\n";
	String formaterEnTeteSans = "%%-%ds %%-%ds %%-%ds %%-%ds\n";
	String formatter = "%%-%dd %%-%ds %%-%ds %%-%d.2f %%-%dd %%%d.2f\n";
	String formatterSans = "%%-%dd %%-%ds %%-%ds %%-%d.2f\n";

	//définition du format dynamique
	if (pMontrerCommandes){
		
		// on prend le formatter avec le total et la quantitée
		sprintf(format, formatter, MAX_PROD_CAR, MAX_CELL, MAX_CELL,
			MAX_CELL, MAX_CELL, MAX_CELL);
		sprintf(formatEnTete, formaterEnTete, MAX_PROD_CAR, MAX_CELL,
			MAX_CELL, MAX_CELL, MAX_CELL, MAX_CELL);
		sprintf(formatPied, formaterPied, MAX_CELL, MAX_CELL-(MAX_CELL-MAX_PROD_CAR),
			MAX_CELL, MAX_CELL, MAX_CELL, MAX_CELL);
		printf(MSG_PROD_COMMANDE);
		
		// En tête pour l'impression avec les commandes
		printf(formatEnTete, CONST_PROD_NO, CONST_PROD_MARQUE, CONST_PROD_REFERENCE,
			CONST_PROD_PRIX, CONST_PROD_QUANTITE, CONST_PROD_TOTAL);
	}
	else {
		
		// sinon on montre que les produits
		sprintf(format, formatterSans, MAX_PROD_CAR, MAX_CELL, MAX_CELL, MAX_CELL);
		sprintf(formatEnTete, formaterEnTeteSans, MAX_PROD_CAR, MAX_CELL, MAX_CELL, MAX_CELL);
		printf(MSG_PROD_DISPO);
		
		// En tête pour l'impression sans les commandes
		printf(formatEnTete, CONST_PROD_NO, CONST_PROD_MARQUE, CONST_PROD_REFERENCE,
			CONST_PROD_PRIX);
	}
	
	
	for (i = 0; i < pNbProduits; i++){
		
		// cas ou on veut montrer les commandes
		if (pMontrerCommandes){
			
			// seulement si un produit est commandé
			if (ptrProduits[i]->quantite > 0){
				sousTotal = ptrProduits[i]->quantite * ptrProduits[i]->prix;
				prixTotal += sousTotal;
				printf(format, ptrProduits[i]->noProduit, ptrProduits[i]->marque,
					ptrProduits[i]->reference, ptrProduits[i]->prix,
					ptrProduits[i]->quantite, sousTotal);
			}
		}
		else {
			printf(format, ptrProduits[i]->noProduit, ptrProduits[i]->marque,
				ptrProduits[i]->reference, ptrProduits[i]->prix);
		}
	}

	// si on montre la commande on ajoute la ligne total
	if (pMontrerCommandes){
		
		// calculer la taille du tableau + 5 espaces
		tailleSepar = MAX_PROD_CAR + (5 * MAX_CELL)+5;

		// calcul de la taille du séparateur
		separator = (char *) malloc(tailleSepar+1);

		// contrôler que malloc soit différent de NULL
		if (NULL != separator){
			for (j = 0; j < (tailleSepar); j++){
				strcpy(&separator[j], CONST_SEPARATEUR);
			}

			printf("%s\n",separator);
			free(separator);
		}
		printf(formatPied, CONST_PROD_TOTAL, "", "", "", "", prixTotal);
		
	}

	puts("");
}

/*Fonction creerFacture*/
void creerFacture(Produit *pCommande[MAX_PROD], Client *pClient, int nbProduits){
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
		printf(MSG_ERR_CREATION_FACTURE);
	} else {
		
		fprintf(out,"<html>\n");
		fprintf(out, "\t<head>\n");
		
		// titre de la page
		fprintf(out, "\t\t<title>%s</title>\n", nomPrenom);
		fprintf(out, "\t</head>\n");
		fprintf(out, "\t<body>\n");

		// Ajout du nom du client
		fprintf(out, "\t\t<h1>%s %s %s</h1>", CONST_FACTURE_DE, pClient->nom, pClient->prenom);
		
		// création de la table avec 
		// le header du tableau
		fprintf(out, "\t\t<table border=\"1px\">\n");
		fprintf(out, "\t\t\t<tr bgcolor=\"yellow\">\n");
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PROD_NO);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PROD_MARQUE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PROD_REFERENCE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n",CONST_PROD_QUANTITE);
		fprintf(out, "\t\t\t\t<th>%s</th>\n", CONST_PROD_PRIX);
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
				fprintf(out, "\t\t\t\t<td>%d</td>\n", pCommande[i]->noProduit);
				fprintf(out, "\t\t\t\t<td>%s</td>\n", &pCommande[i]->marque);
				fprintf(out, "\t\t\t\t<td>%s</td>\n", &pCommande[i]->reference);
				fprintf(out, "\t\t\t\t<td>%d</td>\n", pCommande[i]->quantite);
				fprintf(out, "\t\t\t\t<td>%.2f</td>\n", subTotal);
				fprintf(out, "\t\t\t</tr>\n");
			}
		}

		// ajout du pieds avec le total
		fprintf(out, "\t\t\t<tr>\n");
		fprintf(out, "\t\t\t\t<td>%s</td>\n", CONST_PROD_TOTAL);
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td></td>\n");
		fprintf(out, "\t\t\t\t<td>%.2f</td>\n", total);
		fprintf(out, "\t\t\t</tr>\n");
		fprintf(out, "\t\t</table>\n");
		fprintf(out, "\t</body>\n");
		fprintf(out, "</html>\n");
	}
	
	// sauver dans le fichier
	fclose(out);
}

/* saisie d'entiers*/
int saisieEntier() {
	int val, n;
	char ligne[MAX_ENTIER];

	fgets(ligne, MAX_ENTIER, stdin),
		n = sscanf(ligne, "%d", &val);
	while (n != 1) {
		printf(MSG_SAISIE_RECOMMENCER);
		fgets(ligne, MAX_ENTIER, stdin),
			n = sscanf(ligne, "%d", &val);
	}
	puts("");
	return val;
}

/* Fonction afficherCommande */
void afficherFonctionsDisponibles(String pCmdDisponibles[NBRCMD]){
	int i;
	int sousTotal = 0;
	printf(MSG_CMD_DISPO);
	for (i = 0; i < NBRCMD; i++){
		printf("\t%1d) %s \n", i,pCmdDisponibles[i]);
	}
	puts("");
}

/* Fonction etesVousSur */
int etesVousSur() {
	int sur = FAUX;
	char saisie;
	
	printf(MSG_SAISIE_SUR);
	saisie = getchar();
	if (saisie == 'o' || saisie == 'O'){
		sur = VRAI;
	}

	// enlever les caractères parasites
	while (getchar() != '\n');

	return sur;
}

/* Fonction effacerCommande */
void effacerCommande(Produit *ptrProduits[MAX_PROD], int pNbProduits) {
	int i;
	for (i = 0; i < pNbProduits; i++){
		if (ptrProduits[i]->quantite > 0){
			ptrProduits[i]->quantite = 0;
		}
	}
}