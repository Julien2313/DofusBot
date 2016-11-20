#include "bot.h"

void enleverPodsEtape1(int numFen)//entrer dans l'inventaire
{
    jarterEvenementFenetre(numFen, FALSE, TRUE);

    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_ICONE_INVENTAIRE].id  , images[IMAGE_ICONE_INVENTAIRE].rect, images[IMAGE_ICONE_INVENTAIRE].nbrMaxPts  , &images[IMAGE_ICONE_INVENTAIRE].nbrTrouvees, images[IMAGE_ICONE_INVENTAIRE].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_ICONE_INVENTAIRE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].left,images[IMAGE_ICONE_INVENTAIRE].rect[0].right), aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].top,images[IMAGE_ICONE_INVENTAIRE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, ENLEVER_PODS_ETAPE_2, numFen);
        }
        else
        {
            logInfo("Problème, l'inventaire n'est pas visible. \n");
			ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
		}
    }
    else
        afficherErreur();
}

void enleverPodsEtape2(int numFen)//selectionner si besoin le menu ressources
{
    //on vérifie d'abord si tout c'est bien ouvert
	if ((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre, 0, 0, LClient, HClient, images[IMAGE_INVENTAIRE_EN_LETTRE].id, images[IMAGE_INVENTAIRE_EN_LETTRE].rect, images[IMAGE_INVENTAIRE_EN_LETTRE].nbrMaxPts, &images[IMAGE_INVENTAIRE_EN_LETTRE].nbrTrouvees, images[IMAGE_INVENTAIRE_EN_LETTRE].nbrPixelsFaux, 20)) == scrOK)
    {
        if(images[IMAGE_INVENTAIRE_EN_LETTRE].nbrTrouvees > 0)
        {
            //si l'inventaire est ouvert, on fait se qu'il faut !
            if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_ICONE_RESSOURCES].id  , images[IMAGE_ICONE_RESSOURCES].rect, images[IMAGE_ICONE_RESSOURCES].nbrMaxPts  , &images[IMAGE_ICONE_RESSOURCES].nbrTrouvees, images[IMAGE_ICONE_RESSOURCES].nbrPixelsFaux)) == scrOK)
            {
                if(images[IMAGE_ICONE_RESSOURCES].nbrTrouvees > 0)
                {
                    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_ICONE_RESSOURCES].rect[0].left,images[IMAGE_ICONE_RESSOURCES].rect[0].right), aleatoire(images[IMAGE_ICONE_RESSOURCES].rect[0].top,images[IMAGE_ICONE_RESSOURCES].rect[0].bottom));
                    Sleep(300);
                    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    Sleep(300);
                }
            }
            else
                afficherErreur();

            ajouterTache(1000, ENLEVER_PODS_ETAPE_3, numFen);
        }
        else
        {
            ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
        }
    }
    else
        afficherErreur();
}

void enleverPodsEtape3(int numFen)//clique droit sur le blé
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_BLE_INVENTAIRE].id  , images[IMAGE_BLE_INVENTAIRE].rect, images[IMAGE_BLE_INVENTAIRE].nbrMaxPts  , &images[IMAGE_BLE_INVENTAIRE].nbrTrouvees, images[IMAGE_BLE_INVENTAIRE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_BLE_INVENTAIRE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_BLE_INVENTAIRE].rect[0].left,images[IMAGE_BLE_INVENTAIRE].rect[0].right), aleatoire(images[IMAGE_BLE_INVENTAIRE].rect[0].top,images[IMAGE_BLE_INVENTAIRE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (3, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (3, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, ENLEVER_PODS_ETAPE_4, numFen);
        }
        else
        {
            logInfo("Il n'est pas visible !\n");
            //problème, le blé n'apparait pas
            ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
        }
    }
    else
        afficherErreur();
}

void enleverPodsEtape4(int numFen)//cliquer sur détruire
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].id  , images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].rect, images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrMaxPts  , &images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrTrouvees, images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrTrouvees > 0)
        {
            printf("visible\n");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].rect[0].left,images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].rect[0].right), aleatoire(images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].rect[0].top,images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            ajouterTache(1000, ENLEVER_PODS_ETAPE_5, numFen);
        }
        else
        {
            printf("pas visible\n");
            exit(1);
            //problème, le texte n'apparait pas
            ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
        }
    }
    else
        afficherErreur();
}

void enleverPodsEtape5(int numFen)//entrer une valeur
{
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_BOUTON_OK_DELETE].id  , images[IMAGE_BOUTON_OK_DELETE].rect, images[IMAGE_BOUTON_OK_DELETE].nbrMaxPts  , &images[IMAGE_BOUTON_OK_DELETE].nbrTrouvees, images[IMAGE_BOUTON_OK_DELETE].nbrPixelsFaux,20)) == scrOK)
    {
        if(images[IMAGE_BOUTON_OK_DELETE].nbrTrouvees > 0)
        {
            //on rentre la valeur à delete
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "10");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_BOUTON_OK_DELETE].rect[0].left,images[IMAGE_BOUTON_OK_DELETE].rect[0].right), aleatoire(images[IMAGE_BOUTON_OK_DELETE].rect[0].top,images[IMAGE_BOUTON_OK_DELETE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");
            Sleep(300);

            //on ferme la fenêtre
            if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_ICONE_INVENTAIRE].id  , images[IMAGE_ICONE_INVENTAIRE].rect, images[IMAGE_ICONE_INVENTAIRE].nbrMaxPts  , &images[IMAGE_ICONE_INVENTAIRE].nbrTrouvees, images[IMAGE_ICONE_INVENTAIRE].nbrPixelsFaux)) == scrOK)
            {
                if(images[IMAGE_ICONE_INVENTAIRE].nbrTrouvees > 0)
                {
                    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].left,images[IMAGE_ICONE_INVENTAIRE].rect[0].right), aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].top,images[IMAGE_ICONE_INVENTAIRE].rect[0].bottom));
                    Sleep(300);
                    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    Sleep(300);
                }
                else
                {
                    printf("Problème, l'inventaire n'est pas visible. \n");
                    exit(1);
                }
            }
            else
                afficherErreur();
            //on test si il est encore trop fat
            if(testPods(numFen) == 2)
                ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
			else
			{
			    ajouterTache(5000, CHECK_LIST, numFen);
				ajouterTache(1000, ALLER_MAISON, numFen);
			}
            //je fais exprès une faute de compile pour dire qu'il faut ajouter un évènement pour rentrer à la maison, biatch,
        }
        else
        {
            //problème, le bouton n'apparait pas
            ajouterTache(1000, ENLEVER_PODS_ETAPE_1, numFen);
        }
    }
    else
        afficherErreur();
}
