#ifndef BOT_H_INCLUDED
#define BOT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "dllScripting.h"

#define NBRTACHES 10000
#define NBRIMAGES 1000
#define NBRFENETREAOUVRIR   1
#define LGMSGERR 200

#define AJOUTER_TACHE                                           0
#define INITIALISER_FENETRE                                     1
#define RANGER_FENETRE                                          2
#define TEST_CONNEXION_MENU                                     3
#define CONNEXION                                               4
#define VERIFICATION_CONNEXION                                  5
#define VERIFICATION_CONNEXION_SERVEUR                          6
#define VERIFICATION_FILE_ATTENTE                               7
#define VERIFICATION_ETAT_APRES_FILE_ATTENTE                    8
#define CONNEXION_SERVEUR                                       9
#define VERIFICATION_FILE_ATTENTE_SERVEUR                       10
#define VERIFICATION_ETAT_APRES_FILE_ATTENTE_SERVEUR            11
#define ATTENTE_PERSONNAGE_CONNECTE                             12
#define INITIALISATION_PERSONNAGE                               13
#define ALLEZFAUCHER                                            14
#define VERIFICATION_CHANGEMENT_CARTE                           15
#define COMBAT                                                  16
#define CLIC_BLE                                                17
#define DECONNEXION                                             18
#define CHECK_LIST                                              19
#define VIDER_COFFRE                                            20
#define ENLEVER_NO_UPDATER                                      21
#define SE_DEPLACER												22
#define ENLEVER_PODS_ETAPE_1									23
#define ENLEVER_PODS_ETAPE_2									24
#define ENLEVER_PODS_ETAPE_3									25
#define ENLEVER_PODS_ETAPE_4									26
#define ENLEVER_PODS_ETAPE_5									27
#define ALLER_MAISON                                            28
#define ENTRER_MAISON                                           29
#define CLIQUER_ESCALIER                                        30
#define CLIQUER_COFFRE                                          31
#define DEPLACER_BLE                                            32
#define DESCENDRE_ESCALIER                                      33
#define QUITTER_MAISON                                          34

#define FERMER_FENETRE                          1100

#define IMAGE_JOUER                                 0
#define IMAGE_ERREUR_CONNEXION_MENU                 1
#define IMAGE_JOUER_CHARGEMENT                      2
#define IMAGE_JOUER_FILE_ATTENTE                    3
#define IMAGE_SERVEUR_INACCESSIBLE                  4
#define IMAGE_LISTE_SERVEURS                        5
#define IMAGE_SERVEUR_AGRIDE_ACCESSIBLE             6
#define IMAGE_SELECTIONNER_CHARGEMENT               7
#define IMAGE_SELECTONNER_FILE_ATTENTE              8
#define IMAGE_JOUER_SELECTON_PERSONNAGE             9
#define IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160        10
#define IMAGE_INFORMATIONS_CARTE                    11
#define IMAGE_DISPONIBILITE                         12
#define IMAGE_PRIVE                                 13
#define IMAGE_PRIVE2                                14
#define IMAGE_CROIX_COMBAT                          15
#define IMAGE_SERVEUR_AGRIDE_MAINTENANCE            16
#define IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT 17
#define IMAGE_CROIX_INVITATION                      18
#define IMAGE_IGNORER                               19
#define IMAGE_PETIT_IGNORE                          20
#define IMAGE_FLECHE_GAUCHE_ORANGE                  21
#define IMAGE_FLECHE_DROITE_ORANGE                  22
#define IMAGE_FLECHE_HAUT_ORANGE                    23
#define IMAGE_FLECHE_BAS_ORANGE                     24
#define IMAGE_FLECHE_GAUCHE_BLEU                    25
#define IMAGE_FLECHE_DROITE_BLEU                    26
#define IMAGE_FLECHE_HAUT_BLEU                      27
#define IMAGE_FLECHE_BAS_BLEU                       28
#define IMAGE_CONNEXION_SERVEUR_INTERROMPUE         29
#define IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND   30
#define IMAGE_CROIX_MESSAGE                         31
#define IMAGE_PAS_MAINTENANT_CADEAU                 32
#define IMAGE_DOFUS                                 33
#define IMAGE_EPI_BLE_1                             34
#define IMAGE_EPI_BLE_2                             35
#define IMAGE_EPI_BLE_3                             36
#define IMAGE_EPI_BLE_4                             37
#define IMAGE_EPI_BLE_5                             38
#define IMAGE_COMBAT_PRET                           39
#define IMAGE_FERME_RESUME_COMBAT                   40
#define IMAGE_SORT_RONCE_CIBLE                      41
#define IMAGE_SORT_RONCE                            42
#define IMAGE_COMBAT_MODE_TACTIQUE                  43
#define IMAGE_COMBAT_MODE_CREATURE                  44
#define IMAGE_FERMER_CHALLENGE                      45
#define IMAGE_FLECHE_TIMELINE                       46
#define IMAGE_AFFICHER_COORDONNEES                  47
#define IMAGE_CROIX_FENETRE_UP                      48
#define IMAGE_NO_UPDATER                            49
#define IMAGE_ICONE_INVENTAIRE                      50
#define IMAGE_ICONE_RESSOURCES                      51
#define IMAGE_BLE_INVENTAIRE                        52
#define IMAGE_TEXTE_DETRUIRE_INVENTAIRE             53
#define IMAGE_INVENTAIRE_EN_LETTRE                  54
#define IMAGE_BOUTON_OK_DELETE                      55
#define IMAGE_MAISON_PORTE                          56
#define IMAGE_MAISON_CODE                           57
#define IMAGE_BOUTON_OK                             58
#define IMAGE_MAISON_ESCALIER                       59
#define IMAGE_MAISON_COFFRE                         60
#define IMAGE_MAISON_ESCALIER_SORTIE                61
#define IMAGE_MAISON_SORTIE                         62
#define IMAGE_MAISON_BLE                            63
#define IMAGE_BOUTON_SUCCES                         64
#define IMAGE_BOUTON_ACCEPTER_SUCCES                65
#define IMAGE_OK_CONNEXION                          66

typedef struct
{
    unsigned int date;
    int idTache;
    int numFenetre;
}TACHE;

typedef struct
{
    char cheminNom[100];
    int id;
    RECT rect[100];
    int nbrMaxPts;
    int tolerance;
    int nbrTrouvees;
    int nbrPixelsFaux;
}IMAGE;

typedef struct
{
    int largeur, hauteur;
    COLORREF *imagePosition;
}IMAGECELLULE;

typedef struct
{
    char pseudo[100];
    char code[100];
    int direction;
    POINT coordonnees;
    IMAGECELLULE imageCellule;
    IMAGECELLULE imageCellule2;
    unsigned int heureConnexion, heureDeconnexion;
    int enCombat, connecte, ancienneTache;
}PERSONNAGE;

typedef struct
{
    int idFenetre;
    PERSONNAGE personnage;
}FENETRE;

typedef struct
{
    RECT rect;
    POINT point;
}POINTSRECOLTES;


typedef struct
{
    int tabClient[33 * 34][2];
    BYTE tabCellule[33 * 34];
}TABLEAUCARTECOMBAT;


extern TACHE taches[];
extern IMAGE images[];
extern PERSONNAGE personnages[];
extern FENETRE fenetres[];
extern POINTSRECOLTES pointsRecoltes[];
extern int nbrPointsRecoltes;
extern int LClient, HClient, lBordureHaut, lBordureBas, lBordureGauche, lBordureDroite;
extern int LFenetre, HFenetre;//va changer
extern int idFenetre[NBRFENETREAOUVRIR];
extern int nbrTachesPlanifiees;
extern int nbrPersonnages;
extern int directionFaucher[200][200];
extern int nbrIDLut;
extern unsigned int temps;

extern int err;
extern char msgErr[];
extern int nbrFenLargeur, nbrFenHauteur;
extern char cheminDofus[], cheminLauncher[];



int afficherPointsBle(void);

//combat.c
void combatJouer(int numFen);
int combatOuNon(int numFen);
void cartographierTerrain(int numFen, TABLEAUCARTECOMBAT *tableauxCarteCombat);
void checkList(numFen);
int lancerSortAttaque(int numFen, int idImage);
void lancerSortInvoquation(int numFen, int idImage);
void combat(int numFen);

//initialisation.c
void initialisation(void);
void initialisationTailleFenetre(void);
void initialiserImages(void);
int ouvrirDofusInitiliser(void);
void enleverFenetreNoUpdater(int numFen);
void initialiserFenetre(int numFen);
void changerPersonnageFenetre(int numFen);
void initialisationPersonnage(int numFen);

//fauche.c
void allerFaucher(int numFen);
void rechercheBle(int numFen, IMAGE image);
void clicSurBle(int numFen);
BOOL verificationPointsRecolte(RECT rect);
int ouAllerPourFaucher(int *pos);
void lireDirectionFaucher(void);
void checkPods(int numFen);

//maison.c
void allerMaison(int numFen);
void entrerMaison(int numFen);
void cliquerPorte(int numFen);
void clicEscalier(int numFen);
void cliquerCoffre(int numFen);
void deplacerBle(int numFen);
void quitterMaison(int numFen);
void descendreEscalier(int numFen);

//connexion.c
void connexion(int numFen);
void attenteConnexionPersonnage(int numFen);
void verificationEtatApresFileAttenteServeur(int numFen);
int ouvrirDofus(void);
void lireIdentifiants(void);
void verficationFileAttenteServeur(int numFen);
void testPossibiliteConnexionMenu(int numFen);
void connexionServeur(int numFen);
void ouvrirLaucnher(void);
void verificationFileAttente(int numFen);
void verificationEtatApresFileAttente(int numFen);
void reouvrirFenetre(int numFen);

//deplacements.c
BYTE deplacementsPossibles(int numFen);
void seDeplacer(int numFen, POINT arrivee, int rentrerMaison);
void deplacement(int numFen, int direction, int majuscule);
void verificationChangementCarte(int numFen);
int testPods(int numFen);


//fonctionDeBaseFenetre.c
void jarterEvenementFenetre(int numFen, int enleverDeconnexion, int enleverCheckList);
void rangerFenetre(int numFen);
void fermerFenetre(int numFen);
void appellerFonction(void);
int compare(const void *elem1, const void *elem2);
long int aleatoire(long int MINI, long int MAXI);
void afficherErreur(void);
void ajouterTache(unsigned int date, int idTache, int numFenetre);
void enumererTaches(void);
void testCasNonGeresMaisMaintenantOui(int numFen);
void trouverTailleFenetreclient(int numFen, int LClient_, int HClient_, int *LFenetre_, int *HFenetre_);

//interactionInventaire
void enleverPodsEtape1(int numFen);
void enleverPodsEtape2(int numFen);
void enleverPodsEtape3(int numFen);
void enleverPodsEtape4(int numFen);
void enleverPodsEtape5(int numFen);

//logging
void logInfo( const char* texte, ... );
void logDebug( const char* texte, ... );
void logWarning( const char* texte, ... );
void logError( const char* texte, ... );

#endif // BOT_H_INCLUDED

