#include "bot.h"

int testPods(int numFen)//0 il peut faucher 1 il doit rentrer 2 il doit se vider
{
    COLORREF couleur;
    if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, 108, 151, &couleur)) == scrOK)
    {
        if(couleur == RGB(0xFD, 0x36, 0x36))
        {
            if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, 98, 158, &couleur)) == scrOK)
            {
                if(couleur == RGB(0x9E, 0x9C, 0x9A))
                    return 2;
                else
                    return 1;
            }
            else
                afficherErreur();
        }
        else
            return 0;
    }
    else
        afficherErreur();
    return 0;//ne devrait jamais y aller, mais c'pour éviter une warning
}

int combatOuNon(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_CROIX_COMBAT].id  , images[IMAGE_CROIX_COMBAT].rect  , images[IMAGE_CROIX_COMBAT].nbrMaxPts  , &images[IMAGE_CROIX_COMBAT].nbrTrouvees, images[IMAGE_CROIX_COMBAT].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_CROIX_COMBAT].nbrTrouvees > 0)
            return 1;
    }
    else
        afficherErreur();
    return 0;
}

void upPaysant(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_BOUTON_OK].id, images[IMAGE_BOUTON_OK].rect, images[IMAGE_BOUTON_OK].nbrMaxPts, &images[IMAGE_BOUTON_OK].nbrTrouvees, images[IMAGE_BOUTON_OK].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_BOUTON_OK].nbrTrouvees > 0 )
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].left,images[IMAGE_ICONE_INVENTAIRE].rect[0].right), aleatoire(images[IMAGE_ICONE_INVENTAIRE].rect[0].top,images[IMAGE_ICONE_INVENTAIRE].rect[0].bottom));
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
        }
    }
    else
        afficherErreur();
}

void checkPods(int numFen)
{
    int pods = testPods(numFen);
    if (pods == 2)
    {
        logWarning("Le perso est pleing, faut qu'il décuve.");
        fenetres[numFen].personnage.ancienneTache = ENLEVER_PODS_ETAPE_1;
    }
    else if(pods == 1 && fenetres[numFen].personnage.ancienneTache != ALLER_MAISON)
    {
        logInfo("Le perso a assez travaillé pour le moment, retour au bercail");
        fenetres[numFen].personnage.ancienneTache = ALLER_MAISON;
    }
}

void checkSucces(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_BOUTON_SUCCES].id, images[IMAGE_BOUTON_SUCCES].rect, images[IMAGE_BOUTON_SUCCES].nbrMaxPts, &images[IMAGE_BOUTON_SUCCES].nbrTrouvees, images[IMAGE_BOUTON_SUCCES].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_BOUTON_SUCCES].nbrTrouvees > 0 )
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_BOUTON_SUCCES].rect[0].left,images[IMAGE_BOUTON_SUCCES].rect[0].right), aleatoire(images[IMAGE_BOUTON_SUCCES].rect[0].top,images[IMAGE_BOUTON_SUCCES].rect[0].bottom));
            Sleep(100);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(100);
            if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_BOUTON_ACCEPTER_SUCCES].id, images[IMAGE_BOUTON_ACCEPTER_SUCCES].rect, images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrMaxPts, &images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrTrouvees, images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrPixelsFaux )) == scrOK)
            {
                if(images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrTrouvees > 0 )
                {
                    scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_BOUTON_ACCEPTER_SUCCES].rect[0].left,images[IMAGE_BOUTON_ACCEPTER_SUCCES].rect[0].right), aleatoire(images[IMAGE_BOUTON_ACCEPTER_SUCCES].rect[0].top,images[IMAGE_BOUTON_ACCEPTER_SUCCES].rect[0].bottom));
                    Sleep(100);
                    scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                    Sleep(100);
                }
            }
        else
            afficherErreur();
        }
    }
    else
        afficherErreur();
}
