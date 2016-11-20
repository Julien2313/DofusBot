#include "bot.h"

BYTE deplacementsPossibles(int numFen)
{
    BYTE valeurRetournee = 0;

    scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient/2, 1);
    Sleep(100);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,50, images[IMAGE_FLECHE_HAUT_ORANGE].id, images[IMAGE_FLECHE_HAUT_ORANGE].rect, images[IMAGE_FLECHE_HAUT_ORANGE].nbrMaxPts, &images[IMAGE_FLECHE_HAUT_ORANGE].nbrTrouvees, images[IMAGE_FLECHE_HAUT_ORANGE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_FLECHE_HAUT_ORANGE].nbrTrouvees > 0)
            valeurRetournee += scrHAUT;

        else
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,50, images[IMAGE_FLECHE_HAUT_BLEU].id, images[IMAGE_FLECHE_HAUT_BLEU].rect, images[IMAGE_FLECHE_HAUT_BLEU].nbrMaxPts, &images[IMAGE_FLECHE_HAUT_BLEU].nbrTrouvees, images[IMAGE_FLECHE_HAUT_BLEU].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_FLECHE_HAUT_BLEU].nbrTrouvees > 0)
                valeurRetournee += scrHAUT;

        }
        else
            afficherErreur();
    }
    else
        afficherErreur();

    scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, 1        , HClient/2);
    Sleep(100);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,50,HClient, images[IMAGE_FLECHE_GAUCHE_ORANGE].id, images[IMAGE_FLECHE_GAUCHE_ORANGE].rect, images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrMaxPts, &images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrTrouvees, images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrTrouvees > 0)
            valeurRetournee += scrGAUCHE;

        else
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,50,HClient, images[IMAGE_FLECHE_GAUCHE_BLEU].id,   images[IMAGE_FLECHE_GAUCHE_BLEU].rect,   images[IMAGE_FLECHE_GAUCHE_BLEU].nbrMaxPts, &images[IMAGE_FLECHE_GAUCHE_BLEU].nbrTrouvees,   images[IMAGE_FLECHE_GAUCHE_BLEU].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_FLECHE_GAUCHE_BLEU].nbrTrouvees > 0)
                valeurRetournee += scrGAUCHE;

        }
        else
            afficherErreur();
    }
    else
        afficherErreur();

    scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient/2, 149  );
    Sleep(100);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,HClient-50,LClient,50, images[IMAGE_FLECHE_BAS_ORANGE].id, images[IMAGE_FLECHE_BAS_ORANGE].rect, images[IMAGE_FLECHE_BAS_ORANGE].nbrMaxPts, &images[IMAGE_FLECHE_BAS_ORANGE].nbrTrouvees, images[IMAGE_FLECHE_BAS_ORANGE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_FLECHE_BAS_ORANGE].nbrTrouvees > 0)
            valeurRetournee += scrBAS;

        else
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,HClient-50,LClient,50, images[IMAGE_FLECHE_BAS_BLEU].id,   images[IMAGE_FLECHE_BAS_BLEU].rect,   images[IMAGE_FLECHE_BAS_BLEU].nbrMaxPts, &images[IMAGE_FLECHE_BAS_BLEU].nbrTrouvees,   images[IMAGE_FLECHE_BAS_BLEU].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_FLECHE_BAS_BLEU].nbrTrouvees > 0)
                valeurRetournee += scrBAS;

        }
        else
            afficherErreur();
    }
    else
        afficherErreur();

    scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient-1  , HClient/2);
    Sleep(100);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,LClient-50,0,48,HClient, images[IMAGE_FLECHE_DROITE_ORANGE].id, images[IMAGE_FLECHE_DROITE_ORANGE].rect, images[IMAGE_FLECHE_DROITE_ORANGE].nbrMaxPts, &images[IMAGE_FLECHE_DROITE_ORANGE].nbrTrouvees, images[IMAGE_FLECHE_DROITE_ORANGE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_FLECHE_DROITE_ORANGE].nbrTrouvees > 0)
            valeurRetournee += scrDROITE;

        else
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,LClient-50,0,48,HClient, images[IMAGE_FLECHE_DROITE_BLEU].id,   images[IMAGE_FLECHE_DROITE_BLEU].rect, images[IMAGE_FLECHE_DROITE_BLEU].nbrMaxPts, &images[IMAGE_FLECHE_DROITE_BLEU].nbrTrouvees,     images[IMAGE_FLECHE_DROITE_BLEU].nbrPixelsFaux)) == scrOK)
        {
            if(images[IMAGE_FLECHE_DROITE_BLEU].nbrTrouvees > 0)
                valeurRetournee += scrDROITE;

        }
        else
            afficherErreur();
    }
    else
        afficherErreur();

    return valeurRetournee;
}

void deplacement(int numFen, int direction, int majuscule)
{

    if(direction == scrHAUT)
        scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient/2, 1);
    if(direction == scrBAS)
        scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient/2, 149  );
    if(direction == scrGAUCHE)
        scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, 1        , HClient/2);
    if(direction == scrDROITE)
        scrSourisDeplace(fenetres[numFen].idFenetre, FALSE, LClient-1  , HClient/2);

	fenetres[numFen].personnage.direction = direction;
    Sleep(50);
    scrSourisClique(1, TRUE, majuscule, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique(1, FALSE, majuscule, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(20);
}

void seDeplacer(int numFen, POINT arrivee, int rentrerMaison)
{
	int direction;
	int directions;
	BYTE directionsPossible;
	BOOL AExplorer;

	scrCelluleDirections(&fenetres[numFen].personnage.coordonnees, &directions);
	printf("directions possibles : %d\n", directions);
	directionsPossible = deplacementsPossibles(numFen);
	if ((fenetres[numFen].personnage.coordonnees.x != arrivee.x || fenetres[numFen].personnage.coordonnees.y != arrivee.y))
	{
		if ((err = scrCelluleAExplorer(&fenetres[numFen].personnage.coordonnees, &AExplorer)) != scrOK)
			afficherErreur();

		if (AExplorer)
		if ((err = scrModificationCellule(&fenetres[numFen].personnage.coordonnees, directionsPossible)) != scrOK)
			afficherErreur();
		do{
			if ((err = scrTrouveChemin(&fenetres[numFen].personnage.coordonnees, &arrivee, &direction)) != scrOK)
				afficherErreur();
			printf("direction : %d\n", direction);
			scrCelluleDirections(&fenetres[numFen].personnage.coordonnees, &directions);
			printf("directions possibles : %d\n", directions);
			printf("[%ld;%ld]\n", fenetres[numFen].personnage.coordonnees.x, fenetres[numFen].personnage.coordonnees.y);
			if ((directionsPossible & direction) != 0)
			{
				fenetres[numFen].personnage.imageCellule.largeur = 7;
				fenetres[numFen].personnage.imageCellule.hauteur = 5;

				scrHardCopy(fenetres[numFen].idFenetre, 107, 160, &fenetres[numFen].personnage.imageCellule.largeur, &fenetres[numFen].personnage.imageCellule.hauteur, &fenetres[numFen].personnage.imageCellule.imagePosition);
				if(rentrerMaison == TRUE)
                {
                    Sleep(100);
                    deplacement(numFen, direction, FALSE);
                    Sleep(100);
                }
				deplacement(numFen, direction, TRUE);

				ajouterTache(6000, VERIFICATION_CHANGEMENT_CARTE, numFen);
				break;
			}
			else
			if ((err = scrModificationCellule(&fenetres[numFen].personnage.coordonnees, directionsPossible)) != scrOK)
				afficherErreur();
		} while (TRUE);
	}
	else
	{
		ajouterTache(1000, fenetres[numFen].personnage.ancienneTache, numFen);
	}
}

void verificationChangementCarte(int numFen)
{
    int nbrTrouves;
    RECT zone;
    fenetres[numFen].personnage.imageCellule2.largeur = 7;
    fenetres[numFen].personnage.imageCellule2.hauteur = 5;

    if(combatOuNon(numFen))
    {
        combat(numFen);
        return;
    }


    scrHardCopy(fenetres[numFen].idFenetre, 107,160, &fenetres[numFen].personnage.imageCellule2.largeur, &fenetres[numFen].personnage.imageCellule2.hauteur, &fenetres[numFen].personnage.imageCellule2.imagePosition);

    if(scrTrouveImage2(fenetres[numFen].idFenetre, 107,160, fenetres[numFen].personnage.imageCellule2.largeur, fenetres[numFen].personnage.imageCellule2.hauteur, fenetres[numFen].personnage.imageCellule.imagePosition, fenetres[numFen].personnage.imageCellule.largeur, fenetres[numFen].personnage.imageCellule.hauteur, &zone,1 , &nbrTrouves,0 ) == scrOK)
    {
        if(nbrTrouves == 0)
        {
            if(fenetres[numFen].personnage.direction == scrHAUT)
                fenetres[numFen].personnage.coordonnees.y--;

            if(fenetres[numFen].personnage.direction == scrBAS)
                fenetres[numFen].personnage.coordonnees.y++;

            if(fenetres[numFen].personnage.direction == scrGAUCHE)
                fenetres[numFen].personnage.coordonnees.x--;

            if(fenetres[numFen].personnage.direction == scrDROITE)
                fenetres[numFen].personnage.coordonnees.x++;

            //if(testPods(numFen) != 1 || testPods(numFen) != 2)
            ajouterTache(1000, fenetres[numFen].personnage.ancienneTache, numFen);

        }
        else
            ajouterTache(1000, VERIFICATION_CHANGEMENT_CARTE, numFen);
    }
    else
        afficherErreur();

}



void viderCoffre(int numFen)
{
    fenetres[numFen].personnage.ancienneTache = VIDER_COFFRE;
}
