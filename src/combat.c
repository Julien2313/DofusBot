#include "bot.h"

int lancerSortAttaque(int numFen, int idImage)
{
    TABLEAUCARTECOMBAT tableauxCarteCombat;
    int i,j;

    cartographierTerrain(numFen, &tableauxCarteCombat);

    //on test le sort sur tous les ennemis
    for(j = 0; j < 33;j++)
        for(i = 0; i < 34;i++)
            if(tableauxCarteCombat.tabCellule[i + 34 * j] == 3)
            {
                logInfo("On a trouvé un ennemis !\n");
                //on deplace la souri

                Sleep(100);
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, tableauxCarteCombat.tabClient[i + 34 * j][0], tableauxCarteCombat.tabClient[i + 34 * j][1]);
                Sleep(100);
                //on regards si on peut lancer le sort
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[idImage].id  , images[idImage].rect, images[idImage].nbrMaxPts  , &images[idImage].nbrTrouvees, images[idImage].nbrPixelsFaux)) == scrOK)
                {
                    if(images[idImage].nbrTrouvees > 0)
                    {
                        Sleep(100);
                        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        Sleep(100);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
                        Sleep(100);
                        return 1;
                    }
                }
                else
                    afficherErreur();
            }
    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
    Sleep(100);
    return 0;
}

void lancerSortInvoquation(int numFen, int idImage)
{
/*
image à gérer :
sort_ronce_cible
croixupnoterposition
upstatsnoterposition
sortroncenoterposition
liste_sorts
AMODIFIER_uplvl5
AMODIFIER_uplvl2a4

*/
}


// 1 étage = 2 lignes
void cartographierTerrain(int numFen, TABLEAUCARTECOMBAT *tableauxCarteCombat)
{
    int y, x, i, j;
    int ecartY = -1;
    int hauteurEtage1 = 8;//la distance en pixel entre chaque "étage"
    int hauteurEtage2 = 7;//la distance en pixel entre chaque "étage"
    int largeurX = 15;
    int departPremiereLigneY = 2, departDeuxiemeLigneY = 6, departPremiereLigneX = 8 ,departDeuxiemeLigneX = 16;
    int posXTab, posYTab;

    COLORREF couleur, couleurMur, couleurSol, couleurVide;
    COLORREF couleurMonstre1, couleurMonstre2, couleurMonstre3, couleurMonstre4,couleurMonstre5,couleurMonstre6, couleurSortBleu, couleurSortBleuClair;
    couleurMonstre1 = RGB(46,54,61);
    couleurMonstre2 = RGB(0x41,0x44,0x40);
    couleurMonstre3 = RGB(0x6c,0x6e,0x77);
    couleurMonstre4 = RGB(0x4a,0x4c,0x45);
    couleurMonstre5 = RGB(0x4b,0x4e,0x47);

    couleurMonstre6 = RGB(0x2E,0x36,0x3D);
    couleurSortBleu = RGB(0x22,0x33,0x99);
    couleurSortBleuClair = RGB(0x54,0x6d,0xa5);
    couleurMur = RGB(61,58,40);
    couleurSol = RGB(142,134,94);
    couleurVide = RGB(0,0,0);

    posYTab = 14;

    for(i = 0; i < 34;i++)
        for(j = 0; j < 33;j++)
            tableauxCarteCombat->tabCellule[i + 34 * j] = 0;

    for(y = 0; y < 20; y++)//le 20 est le nombre de ligne/2
    {
        posYTab = 13 + y;
        for(x = 0, posXTab = y; x < 14; x++)
        {

            if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, departPremiereLigneX + largeurX * x, departPremiereLigneY, &couleur)) == scrOK)
            {
                if(couleur == couleurMonstre1 || couleur == couleurMonstre2 || couleur == couleurMonstre3 || couleur == couleurMonstre4 || couleur == couleurMonstre5 || couleur == couleurMonstre6)
                {
                    tableauxCarteCombat->tabCellule[posXTab + 34 * posYTab] = 3;
                }
                else if(couleur == couleurMur || couleur == couleurVide)
                {
                    tableauxCarteCombat->tabCellule[posXTab + 34 * posYTab] = 0;
                }
                else if(couleur == couleurSol)
                {
                    tableauxCarteCombat->tabCellule[posXTab + 34 * posYTab] = 1;
                }
                else
                {
                    tableauxCarteCombat->tabCellule[posXTab + 34 * posYTab] = 2;
                }
                tableauxCarteCombat->tabClient[posXTab + 34 * posYTab][0] = departPremiereLigneX + largeurX * x;
                tableauxCarteCombat->tabClient[posXTab + 34 * posYTab][1] = departPremiereLigneY;

                //scrChangeCouleurPixel(fenetres[numFen].idFenetre, departPremiereLigneX + largeurX * x, departPremiereLigneY, RGB(255,0,0),&couleur);
            }
            else
                afficherErreur();

            if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, departDeuxiemeLigneX + largeurX * x, departDeuxiemeLigneY, &couleur)) == scrOK)
            {
                if(couleur == couleurMonstre1 || couleur == couleurMonstre2 || couleur == couleurMonstre3 || couleur == couleurMonstre4 || couleur == couleurMonstre5 || couleur == couleurMonstre6)
                {
                    tableauxCarteCombat->tabCellule[posXTab+1 + 34 * posYTab] = 3;
                }
                else if(couleur == couleurMur || couleur == couleurVide)
                {
                    tableauxCarteCombat->tabCellule[posXTab+1 + 34 * posYTab] = 0;
                }
                else if(couleur == couleurSol)
                {
                    tableauxCarteCombat->tabCellule[posXTab+1 + 34 * posYTab] = 1;
                }
                else
                {
                    tableauxCarteCombat->tabCellule[posXTab+1 + 34 * posYTab] = 2;
                }
                tableauxCarteCombat->tabClient[posXTab+1 + 34 * posYTab][0] = departDeuxiemeLigneX + largeurX * x;
                tableauxCarteCombat->tabClient[posXTab+1 + 34 * posYTab][1] = departDeuxiemeLigneY;

                //scrChangeCouleurPixel(fenetres[numFen].idFenetre, departDeuxiemeLigneX + largeurX * x, departDeuxiemeLigneY, RGB(0,255,0),&couleur);
            }
            else
                afficherErreur();

            posXTab += 1;
            posYTab -= 1;
        }

        departPremiereLigneY += hauteurEtage1;
        departDeuxiemeLigneY += hauteurEtage2;
        hauteurEtage1 += ecartY;
        hauteurEtage2 -= ecartY;
        ecartY = -ecartY;
        //printf("hateureEtage : %d, ecartY %d \n", hateureEtage, ecartY);
    }

    tableauxCarteCombat->tabCellule[13 + 34 * 0] = 0;
    tableauxCarteCombat->tabCellule[20 + 34 * 32] = 0;
    scrSauveImage(fenetres[numFen].idFenetre,0,0,221,176,"test.bmp");

    printf("\n");
    for(j = 0; j < 33;j++)
    {
        for(i = 0; i < 34;i++)
        {
            if(tableauxCarteCombat->tabCellule[i + 34 * j] != 0)
                printf("%d ",tableauxCarteCombat->tabCellule[i + 34 * j]);
            else
                printf("  ");
        }
        printf("\n");
    }
}

void combatJouer(int numFen)
{
    //on regards si le sort est disponible(la sacrifie)
    /*
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_CROIX_MESSAGE].id  , images[IMAGE_CROIX_MESSAGE].rect, images[IMAGE_CROIX_MESSAGE].nbrMaxPts  , &images[IMAGE_CROIX_MESSAGE].nbrTrouvees, images[IMAGE_CROIX_MESSAGE].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_CROIX_MESSAGE].nbrTrouvees > 10)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_CROIX_MESSAGE].rect[0].left,images[IMAGE_CROIX_MESSAGE].rect[0].right), aleatoire(images[IMAGE_CROIX_MESSAGE].rect[0].top,images[IMAGE_CROIX_MESSAGE].rect[0].bottom));
            Sleep(20);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(100);
            lancerSortInvoquation(numFen, IMAGE_SORT_RONCE_CIBLE);
            combatJouer(numFen);
            return;
        }
    }
    else
        afficherErreur();*/

    //on regards si le sort est disponible(ronce)
    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_SORT_RONCE].id  , images[IMAGE_SORT_RONCE].rect, images[IMAGE_SORT_RONCE].nbrMaxPts  , &images[IMAGE_SORT_RONCE].nbrTrouvees, images[IMAGE_SORT_RONCE].nbrPixelsFaux, 25)) == scrOK)
    {
        if(images[IMAGE_SORT_RONCE].nbrTrouvees > 0)
        {
            logDebug("Ronce est dispo !\n");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_SORT_RONCE].rect[0].left,images[IMAGE_SORT_RONCE].rect[0].right), aleatoire(images[IMAGE_SORT_RONCE].rect[0].top,images[IMAGE_SORT_RONCE].rect[0].bottom));
            Sleep(20);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(100);
            if(lancerSortAttaque(numFen, IMAGE_SORT_RONCE_CIBLE) != 0)
                combatJouer(numFen);
        }
        else
        {
            logDebug("Ronce n'est pas disponible !\n");
        }
    }
    else
        afficherErreur();

}

void deplacementCombat(int numFen)
{
    TABLEAUCARTECOMBAT tableauxCarteCombat;
    int i, j;
    int monstreLePlusProche, distanceLaPlusPetite = 999999, positionPersonnageX, positionPersonnageY;
    POINT point;

    cartographierTerrain(numFen, &tableauxCarteCombat);


    positionPersonnageX = -1;
    positionPersonnageY = -1;
    monstreLePlusProche = -1;
    for(j = 0; j < 33;j++)
        for(i = 0; i < 34;i++)
        {
            if(tableauxCarteCombat.tabCellule[i + 34 * j] == 2)
            {
                positionPersonnageX = i;
                positionPersonnageY = j;
                logDebug("Je me suis trouvé ! \n");
            }
        }

    if(positionPersonnageX == -1 || positionPersonnageY == -1)
    {
        logError("On a pas trouvé le joueur ! \n");
        exit(1);
    }

    for(j = 0; j < 33;j++)
        for(i = 0; i < 34;i++)
        {
            if(tableauxCarteCombat.tabCellule[i + 34 * j] == 3)
            {
                if(distanceLaPlusPetite > (positionPersonnageX-i)*(positionPersonnageX-i) + (positionPersonnageY-j)*(positionPersonnageY-j))
                {
                    distanceLaPlusPetite = (positionPersonnageX-i)*(positionPersonnageX-i) + (positionPersonnageY-j)*(positionPersonnageY-j);
                    if(monstreLePlusProche != -1)
                        tableauxCarteCombat.tabCellule[monstreLePlusProche] = 0;
                    monstreLePlusProche = i + 34 * j;
                }
                else
                    tableauxCarteCombat.tabCellule[i + 34 * j] = 0;
            }
        }


    logDebug("Je suis là : x :%d, y :%d\n",positionPersonnageX, positionPersonnageY);

    scrTrouveCheminCombat(tableauxCarteCombat.tabCellule, 3, &point);

    logDebug("Je dois aller là : x :%ld, y :%ld\n",point.x, point.y);

    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, tableauxCarteCombat.tabClient[point.x + 34 * point.y][0], tableauxCarteCombat.tabClient[point.x + 34 * point.y][1]);
    Sleep(20);
    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(50);
    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
    Sleep(150);
}

void combat(int numFen)
{
    COLORREF couleurTempsJouer = RGB(0xFD,0x6B,0x14), couleur;
    Sleep(1000);
    if(combatOuNon(numFen))
    {
        if(fenetres[numFen].personnage.enCombat == 0)
        {
            fenetres[numFen].personnage.enCombat = 1;
            jarterEvenementFenetre(numFen, FALSE, FALSE);
        }
        logWarning("On est en combat !\n");
        //on test si on trouve le bouton prêt, se qui veut dire que l'on est au début du combat
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_COMBAT_PRET].id  , images[IMAGE_COMBAT_PRET].rect, images[IMAGE_COMBAT_PRET].nbrMaxPts  , &images[IMAGE_COMBAT_PRET].nbrTrouvees, images[IMAGE_COMBAT_PRET].nbrPixelsFaux  )) == scrOK)
        {
            if(images[IMAGE_COMBAT_PRET].nbrTrouvees > 0)
            {
                //IL FAUT ENCORE TESTER S'IL N'Y A PAS UN CON QUI A REJOINT LE COMBAT, IL FAUT LE CICKER !!!!
                logDebug("prêt !\n");

                scrClavierEnvoiFonction(fenetres[numFen].idFenetre, 1,FALSE, FALSE, FALSE);
                ajouterTache(1000, COMBAT, numFen);
                return;
            }
        }
        else
            afficherErreur();

        //on regarde si on peut jouer
        if((err = scrRecupCouleurPixel(fenetres[numFen].idFenetre, 114, 152, &couleur)) == scrOK)
        {

            //on clique partout où il faut pour être en mode tactique et les mobs en petits !
            //mode tactique
            do
            {
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,94,151,5,5, images[IMAGE_COMBAT_MODE_TACTIQUE].id  , images[IMAGE_COMBAT_MODE_TACTIQUE].rect, images[IMAGE_COMBAT_MODE_TACTIQUE].nbrMaxPts  , &images[IMAGE_COMBAT_MODE_TACTIQUE].nbrTrouvees, images[IMAGE_COMBAT_MODE_TACTIQUE].nbrPixelsFaux  )) == scrOK)
                {
                    if(images[IMAGE_COMBAT_MODE_TACTIQUE].nbrTrouvees > 0)
                    {
                        logDebug("Mode combat !\n");
                        Sleep(100);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_COMBAT_MODE_TACTIQUE].rect[0].left,images[IMAGE_COMBAT_MODE_TACTIQUE].rect[0].right), aleatoire(images[IMAGE_COMBAT_MODE_TACTIQUE].rect[0].top,images[IMAGE_COMBAT_MODE_TACTIQUE].rect[0].bottom));
                        Sleep(100);
                        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        Sleep(100);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
                        Sleep(50);
                    }
                }
                else
                    afficherErreur();
            }
            while(images[IMAGE_COMBAT_MODE_TACTIQUE].nbrTrouvees > 0);

            //créature en petit
            do
            {
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,92,156,4,4, images[IMAGE_COMBAT_MODE_CREATURE].id  , images[IMAGE_COMBAT_MODE_CREATURE].rect, images[IMAGE_COMBAT_MODE_CREATURE].nbrMaxPts  , &images[IMAGE_COMBAT_MODE_CREATURE].nbrTrouvees, images[IMAGE_COMBAT_MODE_CREATURE].nbrPixelsFaux  )) == scrOK)
                {
                    if(images[IMAGE_COMBAT_MODE_CREATURE].nbrTrouvees > 0)
                    {
                        logDebug("Créatures en petit !\n");

                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_COMBAT_MODE_CREATURE].rect[0].left,images[IMAGE_COMBAT_MODE_CREATURE].rect[0].right), aleatoire(images[IMAGE_COMBAT_MODE_CREATURE].rect[0].top,images[IMAGE_COMBAT_MODE_CREATURE].rect[0].bottom));
                        Sleep(20);
                        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        Sleep(50);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
                        Sleep(50);
                        /*
                        Sleep(50);
                        scrClavierEnvoiFonction(fenetres[numFen].idFenetre, 1, FALSE, TRUE, FALSE);
                        Sleep(50);
                        */
                    }
                }
                else
                    afficherErreur();
            }
            while(images[IMAGE_COMBAT_MODE_CREATURE].nbrTrouvees > 0);

            //on enlève l'affichage du chall
            do
            {
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_FERMER_CHALLENGE].id  , images[IMAGE_FERMER_CHALLENGE].rect, images[IMAGE_FERMER_CHALLENGE].nbrMaxPts  , &images[IMAGE_FERMER_CHALLENGE].nbrTrouvees, images[IMAGE_FERMER_CHALLENGE].nbrPixelsFaux  )) == scrOK)
                {
                    if(images[IMAGE_FERMER_CHALLENGE].nbrTrouvees > 0)
                    {
                        logDebug("On enlève l'affichage du chall !\n");
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_FERMER_CHALLENGE].rect[0].left,images[IMAGE_FERMER_CHALLENGE].rect[0].right), aleatoire(images[IMAGE_FERMER_CHALLENGE].rect[0].top,images[IMAGE_FERMER_CHALLENGE].rect[0].bottom));
                        Sleep(20);
                        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        Sleep(50);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
                        Sleep(50);
                    }
                }
                else
                    afficherErreur();
            }
            while(images[IMAGE_FERMER_CHALLENGE].nbrTrouvees > 0);

            //on enlève l'affichage de la timeline
            do
            {
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_FLECHE_TIMELINE].id  , images[IMAGE_FLECHE_TIMELINE].rect, images[IMAGE_FLECHE_TIMELINE].nbrMaxPts  , &images[IMAGE_FLECHE_TIMELINE].nbrTrouvees, images[IMAGE_FLECHE_TIMELINE].nbrPixelsFaux  )) == scrOK)
                {
                    if(images[IMAGE_FLECHE_TIMELINE].nbrTrouvees > 0)
                    {
                        logDebug("On enlève l'affichage de la timeline !\n");
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_FLECHE_TIMELINE].rect[0].left+1,images[IMAGE_FLECHE_TIMELINE].rect[0].right), aleatoire(images[IMAGE_FLECHE_TIMELINE].rect[0].top,images[IMAGE_FLECHE_TIMELINE].rect[0].bottom-2));
                        Sleep(20);
                        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                        Sleep(50);
                        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 0, 0);
                        Sleep(50);
                    }
                }
                else
                    afficherErreur();
            }
            while(images[IMAGE_FLECHE_TIMELINE].nbrTrouvees > 0);


                if(couleur == couleurTempsJouer)
                {
                    logDebug("on peut jouer !\n");
                    deplacementCombat(numFen);
                    combatJouer(numFen);
                    scrClavierEnvoiFonction(fenetres[numFen].idFenetre, 1,FALSE, FALSE, FALSE);
                    ajouterTache(7000, COMBAT, numFen);
                    return;
                }
                else
                {
                    logDebug("Pas encore notre tour !\n");
                    ajouterTache(1000, COMBAT, numFen);
                }
        }
        else
            afficherErreur();
    }
    else
    {
        if(fenetres[numFen].personnage.enCombat == 1)
        {
            fenetres[numFen].personnage.enCombat = 0;
            logDebug("on est pas/plus en combat!\n");

            ajouterTache(5000, fenetres[numFen].personnage.ancienneTache, numFen);
            //on ferme la fenêtre de résumé du combat si on la trouve
            if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_FERME_RESUME_COMBAT].id  , images[IMAGE_FERME_RESUME_COMBAT].rect, images[IMAGE_FERME_RESUME_COMBAT].nbrMaxPts  , &images[IMAGE_FERME_RESUME_COMBAT].nbrTrouvees, images[IMAGE_FERME_RESUME_COMBAT].nbrPixelsFaux  )) == scrOK)
            {
                if(images[IMAGE_FERME_RESUME_COMBAT].nbrTrouvees > 0)
                {
                    logDebug("fermuture de la fenêtre résumé !\n");
                    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_FERME_RESUME_COMBAT].rect[0].left,images[IMAGE_FERME_RESUME_COMBAT].rect[0].right), aleatoire(images[IMAGE_FERME_RESUME_COMBAT].rect[0].top,images[IMAGE_FERME_RESUME_COMBAT].rect[0].bottom));
                    Sleep(20);
                    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    Sleep(20);
                }
            }
            else
                afficherErreur();

            //on regards si on a pas up
            if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_CROIX_FENETRE_UP].id  , images[IMAGE_CROIX_FENETRE_UP].rect, images[IMAGE_CROIX_FENETRE_UP].nbrMaxPts  , &images[IMAGE_CROIX_FENETRE_UP].nbrTrouvees, images[IMAGE_CROIX_FENETRE_UP].nbrPixelsFaux  )) == scrOK)
            {
                if(images[IMAGE_CROIX_FENETRE_UP].nbrTrouvees > 0)
                {
                    logDebug("fermuture de la fenêtre up !\n");
                    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_CROIX_FENETRE_UP].rect[0].left,images[IMAGE_CROIX_FENETRE_UP].rect[0].right), aleatoire(images[IMAGE_CROIX_FENETRE_UP].rect[0].top,images[IMAGE_CROIX_FENETRE_UP].rect[0].bottom));
                    Sleep(20);
                    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    Sleep(20);
                }
            }
            else
                afficherErreur();

            ajouterTache(1000,fenetres[numFen].personnage.ancienneTache, numFen);
        }
    }

}


