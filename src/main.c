/*
Pour que le programme marche, il faut :
-avoir le th�me 2.0 (noir)
-qualit� minimum
-personnages non transparants
-d�sactiver le zoom automatique en int�rieur (fonctionnalit�s->carte)
-raccourcis � voir
-connexion au menu des serveurs (et pas aux personnages ou directement connecter le personnage)
-pas de num�ro pour les joueurs pendant les combats
-d�sactiver invocations
*/


// il faut que je g�re les anciennes taches, allezfaucher, faucher, sevider
//bug si lorsque l'on se co, le perso est en combat, et qu'il le quitte tout de suite (il y a une boucle infini pour mettre en mode petit, etc etc etc)
#include "bot.h"

TACHE taches[NBRTACHES];
IMAGE images[NBRIMAGES];
PERSONNAGE personnages[100];
FENETRE fenetres[NBRFENETREAOUVRIR];
POINTSRECOLTES pointsRecoltes[200];
int nbrPointsRecoltes;
int LClient = 221, HClient = 176, lBordureHaut, lBordureBas, lBordureGauche, lBordureDroite;
int LFenetre = 500, HFenetre = 500;//va changer
int idFenetre[NBRFENETREAOUVRIR];
int nbrTachesPlanifiees = 0;
int nbrPersonnages;
int directionFaucher[200][200];
int nbrIDLut = 0;
char cheminDofus[200], cheminLauncher[200];
unsigned int temps;


int err;
char msgErr[LGMSGERR];

int nbrFenLargeur, nbrFenHauteur;

int main()
{
    initialisation();
    while(nbrTachesPlanifiees != 0)
    {
        scrTempsMs(&temps);
        if(taches[0].date <= temps)
        {
            enumererTaches();
            appellerFonction();
        }
       Sleep(50);
    }
    printf("A pu de taches !\n");

    return 0;
}

