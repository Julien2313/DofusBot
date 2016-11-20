#include "bot.h"

void allerMaison(int numFen)
{
    POINT arrivee;
    arrivee.x = -29;
    arrivee.y = -49;

    jarterEvenementFenetre(numFen, FALSE, FALSE);
	fenetres[numFen].personnage.ancienneTache = ALLER_MAISON;

	if ((fenetres[numFen].personnage.coordonnees.x != arrivee.x || fenetres[numFen].personnage.coordonnees.y != arrivee.y))
    {
		seDeplacer(numFen, arrivee, TRUE);
    }
    else
    {
        logInfo("Vous êtes arrivés à la maison\n");
        cliquerPorte(numFen);
		//ajouterTache(1000, CLIC_BLE, numFen);
    }

}

void cliquerPorte(int numFen){
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_PORTE].id  , images[IMAGE_MAISON_PORTE].rect, images[IMAGE_MAISON_PORTE].nbrMaxPts  , &images[IMAGE_MAISON_PORTE].nbrTrouvees, images[IMAGE_MAISON_PORTE].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_MAISON_PORTE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_PORTE].rect[0].left,images[IMAGE_MAISON_PORTE].rect[0].right), aleatoire(images[IMAGE_MAISON_PORTE].rect[0].top,images[IMAGE_MAISON_PORTE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, ENTRER_MAISON, numFen);
        }
        else
        {
            logError("Problème, impossible de trouver la porte de la maison. \n");
			ajouterTache(1000, ALLER_MAISON, numFen);
		}
    }
    else
        afficherErreur();
}


void entrerMaison(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_CODE].id  , images[IMAGE_MAISON_CODE].rect, images[IMAGE_MAISON_CODE].nbrMaxPts  , &images[IMAGE_MAISON_CODE].nbrTrouvees, images[IMAGE_MAISON_CODE].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_MAISON_CODE].nbrTrouvees > 0)
        {
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "26061995");
            Sleep(200);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");
            ajouterTache(1000, CLIQUER_ESCALIER, numFen);
        }
        else
        {
            logError("Problème, impossible de détecter le code de la maison. \n");
			ajouterTache(1000, ENTRER_MAISON, numFen);
		}
    }
    else
        afficherErreur();
}

void clicEscalier(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_ESCALIER].id  , images[IMAGE_MAISON_ESCALIER].rect, images[IMAGE_MAISON_ESCALIER].nbrMaxPts  , &images[IMAGE_MAISON_ESCALIER].nbrTrouvees, images[IMAGE_MAISON_ESCALIER].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_MAISON_ESCALIER].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_ESCALIER].rect[0].left,images[IMAGE_MAISON_ESCALIER].rect[0].right), aleatoire(images[IMAGE_MAISON_ESCALIER].rect[0].top,images[IMAGE_MAISON_ESCALIER].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, CLIQUER_COFFRE, numFen);
        }
        else
        {
            logError("Problème, impossible de trouver l'escalier de la maison. \n");
			ajouterTache(1000, ENTRER_MAISON, numFen);
		}
    }
    else
        afficherErreur();
}

void cliquerCoffre(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_COFFRE].id  , images[IMAGE_MAISON_COFFRE].rect, images[IMAGE_MAISON_COFFRE].nbrMaxPts  , &images[IMAGE_MAISON_COFFRE].nbrTrouvees, images[IMAGE_MAISON_COFFRE].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_MAISON_COFFRE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_COFFRE].rect[0].left,images[IMAGE_MAISON_COFFRE].rect[0].right), aleatoire(images[IMAGE_MAISON_COFFRE].rect[0].top,images[IMAGE_MAISON_COFFRE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(2000);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "26061995");
            Sleep(200);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");
            ajouterTache(1000, DEPLACER_BLE, numFen);
        }
        else
        {
            logError("Problème, impossible de trouver le coffre de la maison. \n");
			ajouterTache(1000, CLIQUER_COFFRE, numFen);
		}
    }
}

void deplacerBle(int numFen)
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,100,0,LClient,HClient, images[IMAGE_MAISON_BLE].id  , images[IMAGE_MAISON_BLE].rect, images[IMAGE_MAISON_BLE].nbrMaxPts  , &images[IMAGE_MAISON_BLE].nbrTrouvees, images[IMAGE_MAISON_BLE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_MAISON_BLE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_BLE].rect[0].left,images[IMAGE_MAISON_BLE].rect[0].right), aleatoire(images[IMAGE_MAISON_BLE].rect[0].top,images[IMAGE_MAISON_BLE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 38, 70);
            Sleep(300);
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");
            Sleep(300);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\e");
            ajouterTache(1000, DESCENDRE_ESCALIER, numFen);
        }
        else
        {
            logError("Je ne détecte aucun blé dans l'inventaire !\n");
            ajouterTache(1000, DEPLACER_BLE, numFen);
        }
    }
    else
        afficherErreur();
}

void descendreEscalier(int numFen)
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_ESCALIER_SORTIE].id  , images[IMAGE_MAISON_ESCALIER_SORTIE].rect, images[IMAGE_MAISON_ESCALIER_SORTIE].nbrMaxPts  , &images[IMAGE_MAISON_ESCALIER_SORTIE].nbrTrouvees, images[IMAGE_MAISON_ESCALIER_SORTIE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_MAISON_ESCALIER_SORTIE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_ESCALIER_SORTIE].rect[0].left,images[IMAGE_MAISON_ESCALIER_SORTIE].rect[0].right), aleatoire(images[IMAGE_MAISON_ESCALIER_SORTIE].rect[0].top,images[IMAGE_MAISON_ESCALIER_SORTIE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, QUITTER_MAISON, numFen);
        }
        else
        {
            logError("Je ne détecte aucun escalier dans la maison :( !\n");
            ajouterTache(1000, DESCENDRE_ESCALIER, numFen);
        }
    }
    else
        afficherErreur();
}

void quitterMaison(int numFen)
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_MAISON_SORTIE].id  , images[IMAGE_MAISON_SORTIE].rect, images[IMAGE_MAISON_SORTIE].nbrMaxPts  , &images[IMAGE_MAISON_SORTIE].nbrTrouvees, images[IMAGE_MAISON_SORTIE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_MAISON_SORTIE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_MAISON_SORTIE].rect[0].left,images[IMAGE_MAISON_SORTIE].rect[0].right), aleatoire(images[IMAGE_MAISON_SORTIE].rect[0].top,images[IMAGE_MAISON_SORTIE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, ALLEZFAUCHER, numFen);
        }
        else
        {
            logError("Je ne détecte escalier dans la maison :( !\n");
            ajouterTache(1000, DESCENDRE_ESCALIER, numFen);
        }
    }
    else
        afficherErreur();
}


