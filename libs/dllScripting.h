#ifndef DLLSCRIPTING_H_INCLUDED
#define DLLSCRIPTING_H_INCLUDED

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define DllExport __declspec(dllexport)

#define VERSION "Version du 24/08/2014 à 09:58"

typedef struct
 {
  HANDLE  hProcess;  /**< Le handle du processus */
  HWND    hwnd;      /**< Le handle de la fenêtre */
  DWORD   processID; /**< L'ID du processus */
  HDC     hDC;       /**< Le device context */
  HANDLE  hThread;   /**< Le handle du thread */
 } scrDonneesFenetre;

typedef struct
 {
  LONG     larg;        /**< Largeur en pixel de l'image */
  LONG     haut;        /**< Hauteur en pixel de l'image */
  COLORREF transparent; /**< Couleur représentant le transparent dans l'image */
  COLORREF *pImage;     /**< Les pixels de l'image */
  COLORREF *pImageMin;  /**< Les pixels dont chaque composante est diminuée de "tolérance" */
  COLORREF *pImageMax;  /**< Les pixels dont chaque composante est augmentée de "tolérance" */
 } scrDonneesImage;

typedef BYTE scrCelluleDuMonde;

#define scrDROITE        1u
#define scrHAUT          2u
#define scrGAUCHE        4u
#define scrBAS           8u
#define scrDEJAEXPLOREE 16u
#define scrPROTEGEE     32u

#define scrOK                       10000
#define scrCARTE_NON_CHARGEE        10001
#define scrCARTE_NON_ENREGISTREE    10002
#define scrDIMENSION_NEGATIVE       10003
#define scrALLOCATION_MEM_MONDE     10004
#define scrFICHIER_NON_CREE         10005
#define scrCODE_DIRECTIONS          10006
#define scrPAS_UNE_CARTE_DOFUS      10007
#define scrPAS_DE_TAS               10008
#define scrMAUVAISES_COORDS         10009
#define scrPAS_DE_CHEMIN            10010
#define scrPAS_DE_TEXTE             10011
#define scrOUVERTURE_PP             10012
#define scrRECUP_DONNEES_PP         10013
#define scrSCAN_TOUCHE              10014
#define scrMAUVAIS_NUM_FENETRE      10015
#define scrMAUVAIS_NUM_IMAGE        10016
#define scrCHAINE_TROP_COURTE       10017
#define scrCLIENT_RECT              10018
#define scrWINDOW_RECT              10019
#define scrDIMENSIONS_COPIE         10020
#define scrHORS_IMAGE               10021
#define scrZONE_RECH_TROP_GRANDE    10022
#define scrALLOCATION_MEM_BUFFER    10023
#define scrCREATION_CDC             10024
#define scrCREATION_CBM             10025
#define scrSELECT_OBJ               10026
#define scrBITBLT                   10027
#define scrGET_OBJ                  10028
#define scrGET_DIBITS               10029
#define scrALLOCATION_MEM_BMBITS    10030
#define scrSUSPEND_THREAD           10031
#define scrRESUME_THREAD            10032
#define scrTAILLE_INT               10033
#define scrALLOCATION_MEM_LISTESI   10034
#define scrALLOCATION_MEM_LISTEPI   10035
#define scrCREATE_PROCESS           10036
#define scrALLOCATION_MEM_LISTEDF   10037
#define scrTIMEOUT_LANCE_PGM        10038
#define scrOPEN_PROCESS             10039
#define scrLOAD_IMAGE               10040
#define scrALLOCATION_MEM_LISTEDI   10041
#define scrALLOCATION_MEM_PIMAGE    10042
#define scrALLOCATION_MEM_PIMAGEMAX 10043
#define scrALLOCATION_MEM_PIMAGEMIN 10044
#define scrAIGUILLE_RECHERCHE       10045
#define scrMOVE_WINDOW              10046
#define scrWINDOW_HUNG              10047
#define scrTIMEOUT_ACTIVATE         10048
#define scrTIMEOUT_WAIT_IDLE        10049
#define scrCURSOR_POS               10050
#define scrCLIENT_TO_SCREEN         10051
#define scrPAS_DE_COORDS_DS_PP      10052
#define scrFICHIER_MURS             10053
#define scrDONNEES_MURS             10054
#define scrPAS_DE_FENETRE           10055
#define scrPAS_DE_DC                10056
#define scrPAS_DE_PROCESSID         10057
#define scrOPEN_THREAD              10058
#define scrTROUVE_PAS_MOI           10059
#define scrTROUVE_PAS_ENNEMI        10060
#define scrMAUVAIS_NBR_PAS          10061
#define scrCOORDS_SOURIS            10062


int scrInitialisation               (int  msTimeout, const char *nomCarte, const RECT *monde); // monde ne sert que si c'est une nouvelle carte (c'est la cas si le fichier nomFichierCarte n'existe pas)
int scrInitialisationRoulette       (int  msTimeout);
int scrTimeout                      (int  msTimeout);
int scrDebug                        (int  niveau);
int scrQuitte                       (BOOL attendre);
int scrMessageErreur                (int codeErreur, char *messageErreur, int nbrCarMax);
int scrTempsMs                      (unsigned int *temps); // ms écoulées depuis démarrage du PC (49,7 jours)

int scrLanceProgramme               (      char *cmd,        int *numFenetre);
int scrTrouveFenetre                (const char *nomFenetre, int *numFenetre);
int scrDeplaceFenetre               (int  fenetre,  int x, int y, int larg, int  haut);
int scrActiveFenetre                (int  fenetre);

int scrClavierEnvoiCaracteres       (int fenetre, const char *txt);
int scrClavierEnvoiControle         (int fenetre, const char car);
int scrClavierEnvoiFonction         (int fenetre, int        fct,  BOOL shift, BOOL ctrl, BOOL alt);

int scrSourisDeplace                (int fenetre, BOOL coordEcran, int  x,     int  y); // fenetre ne sert pas si coordEcran est TRUE
int scrSourisClique                 (int bouton,  BOOL down,       BOOL shift, BOOL ctrl, BOOL alt); // bouton=1,2,3 gauche,centre,droit
int scrSourisCoordonnees            (POINT *coords);

int scrRecupCouleurPixel            (int fenetre, int x, int y, COLORREF *couleur);
int scrInverseCouleurPixel          (int fenetre, int x, int y, COLORREF *couleur);
int scrChangeCouleurPixel           (int fenetre, int x, int y, COLORREF couleur, COLORREF *ancCouleur);
int scrTrouvePixel                  (int fenetre, COLORREF couleurCherchee, POINT *pts, int nbrMaxPts, int *nbTrouves);
int scrTrouvePixelTolerance         (int fenetre, COLORREF couleurCherchee, POINT *pts, int nbrMaxPts, int *nbTrouves, int tolerance);

int scrChargeImage                  (const char *nomFichierImage, int *numImage);
int scrTrouveImage                  (int fenetre, int xZR,  int yZR,  int largZR,   int hautZR,  int image,                               RECT *rects, int nbrMaxRects, int *nbTrouves, int nbrPixelsFaux);
int scrTrouveImageTolerance         (int fenetre, int xZR,  int yZR,  int largZR,   int hautZR,  int image,                               RECT *rects, int nbrMaxRects, int *nbTrouves, int nbrPixelsFaux, int tolerance);
int scrTrouveImageImage             (int botte,   int xZR,  int yZR,  int largZR,   int hautZR,  int aiguille,                            RECT *rects, int nbrMaxRects, int *nbTrouves, int nbrPixelsFaux);
int scrTrouveImage2                 (int fenetre, int xZR,  int yZR,  int largZR,   int hautZR,  COLORREF *image, int largAI, int hautAI, RECT *rects, int nbrMaxRects, int *nbTrouves, int nbrPixelsFaux);
int scrSauveImage                   (int fenetre, int xSV,  int ySV,  int largSV,   int hautSV,  const char *nomFichierImage);
int scrHardCopy                     (int fenetre, int xCP,  int yCP,  int *largCP,  int *hautCP, COLORREF   **hardCopy);
int scrHardCopyLent                 (int fenetre, int xCP,  int yCP,  int *largCP,  int *hautCP, COLORREF   **hardCopy);

int scrLargeurEcran                 (int *largeur);
int scrHauteurEcran                 (int *hauteur);
int scrRecupDimensionsFenetre       (int fenetre, RECT *fen, RECT *clt);

int scrOcrImage                     (int image,   int xOcr, int yOcr, int largOcr, int hautOcr, char *txtOcr, int nbCarMax);
int scrOcrFenetre                   (int fenetre, int xOcr, int yOcr, int largOcr, int hautOcr, char *txtOcr, int nbCarMax);
int scrOcrCoordonneesDofus          (int fenetre, int xOcr, int yOcr, int largOcr, int hautOcr, POINT *pt);

int scrRecupDF                      (int fenetre, scrDonneesFenetre **df);
int scrRecupDI                      (int image,   scrDonneesImage   **di);

int scrChargeCarteDuMonde           (const char *nomFichierCarte, const RECT *monde);
int scrSauveCarteDuMonde            (void);
int scrCelluleAExplorer             (const POINT *cellule,  BOOL *AExplorer);
int scrModificationCellule          (const POINT *coords,   BYTE directions);
int scrTrouveChemin                 (const POINT *cellule1, const POINT *cellule2, int *direction);
int scrRecupCoordonneesCellule      (POINT *coordonneesPersonnage);
int scrCelluleDirections            (const POINT *cellule,  int *directions);
int scrAfficheCarte                 (void);

int scrTrouveCheminCombat           (BYTE *zoneCombat, int nbrPas, POINT *dest);
int scrRecupCoordonneesCelluleCombat(POINT *coordonneesPersonnage);
int scrAfficheZoneCombat            (const BYTE *zoneCombat);


#endif // DLLSCRIPTING_H_INCLUDED

/*****************************************************************************************************************************************************************************
 Liste des modifications :
 04/08/2014 : Ajout d'une fonction scrInitialisation qui initialise la DLL avec le temps de timeout
 04/08/2014 : Ajout de la gestion de la carte du monde
 06/08/2014 : Ajout de la recherche d'un chemin entre 2 cellules avec l'algo A*
 07/08/2014 : Ajout de la récupération des coordonnées du personnage depuis le presse-papiers
 07/08/2014 : Ajout des premiers commentaires pour Doxygen
 07/08/2014 : Mise en place de tous les codes d'erreur scrXXX et de la fonction permettant de les transformer en texte clair
 08/08/2014 : Revision complète de la façon dont sont gérées les erreurs
 08/08/2014 : Correction d'un bug dans le passage des paramètres, vers scrHardCopy
 08/08/2014 : Correction d'un bug dans scrMessageErreur pour le message système s'affiche : ajouté | FORMAT_MESSAGE_FROM_SYSTEM
 08/08/2014 : Récupération des coordonnées de la cellule à partir du presse-papiers
 09/08/2014 : Ajout de setlocale(LC_CTYPE, ".1252"); dans scrInitialisation pour afficher correctement les accents dans la console, SetConsoleOutputCP ne marche pas !
 09/08/2014 : Ajout de la notion de cellule non modifiable avec scrPROTEGEE et lecture de ces cellules depuis un fichier
 11/08/2014 : Libération de la mémoire allouée à buffer dans scrHardCopy et scrHardCopyLent
 11/08/2014 : Ajout de scrTrouveImage2 où l'image cherchée est un pointeur sur COLORREF
 12/08/2014 : Ajout d'une fonction de visualisation de la carte Dofus : scrAfficheCarte()
 14/08/2014 : Ajout d'une fonction scrInitialisationRoulette
 14/08/2014 : Ajout d'une fonction scrTrouveFenetre qui retrouve une fenêtre par son titre
 16/08/2014 : Impression de x et y à l'entrée de scrSourisDeplace
 23/08/2014 : Ajout de la recherche d'un chemin de combat entre 2 cellules avec l'algo A*
 24/08/2014 : Utilisation pour scrTrouveCheminCombat les mêmes fonctions que pour scrTrouveChemin
 24/08/2014 : Récupération des coordonnées de la souris avec scrSourisCoordonnees
 *****************************************************************************************************************************************************************************/
