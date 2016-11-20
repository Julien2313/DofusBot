#include "bot.h"


void allerFaucher(int numFen)
{
    POINT arrivee;
    arrivee.x = -28;
    arrivee.y = -41;

	fenetres[numFen].personnage.ancienneTache = ALLEZFAUCHER;

	if ((fenetres[numFen].personnage.coordonnees.x != arrivee.x || fenetres[numFen].personnage.coordonnees.y != arrivee.y))
    {
		seDeplacer(numFen, arrivee, FALSE);
    }
    else
    {
        logInfo("Vous êtes arrivés à destination\n");
		ajouterTache(1000, CLIC_BLE, numFen);
    }

}

void rechercheBle(int numFen, IMAGE image)
{
    int cpt = 0;

    if((err = scrTrouveImageTolerance(fenetres[numFen].idFenetre,0,0,1279,1047, image.id  , image.rect, image.nbrMaxPts  , &image.nbrTrouvees, image.nbrPixelsFaux, 20)) == scrOK)
    {
        printf("nombre d'epis trouves : %d\n", image.nbrTrouvees);
        while(image.nbrTrouvees > cpt)
        {
            if(verificationPointsRecolte(image.rect[cpt]) == TRUE)
            {
                pointsRecoltes[nbrPointsRecoltes].rect.left   = image.rect[cpt].left;
                pointsRecoltes[nbrPointsRecoltes].rect.top    = image.rect[cpt].top;
                pointsRecoltes[nbrPointsRecoltes].rect.bottom = image.rect[cpt].bottom;
                pointsRecoltes[nbrPointsRecoltes].rect.right  = image.rect[cpt].right;

                pointsRecoltes[nbrPointsRecoltes].point.x     = image.rect[cpt].left - image.rect[cpt].top * 2;
                pointsRecoltes[nbrPointsRecoltes].point.y     = image.rect[cpt].left + image.rect[cpt].top * 2;
                printf("nouvelle base : (x,y):(%ld,%ld), ancienne (x,y):(%ld,%ld)\n",pointsRecoltes[nbrPointsRecoltes].point.x, pointsRecoltes[nbrPointsRecoltes].point.y, image.rect[cpt].left, image.rect[cpt].top);
                nbrPointsRecoltes++;
            }
            cpt++;
        }
    }
    else
        afficherErreur();
}

void clicSurBle(int numFen)
{
    int cpt;
    BOOL majuscule;
    int tailleFenX, tailleFenY;

	fenetres[numFen].personnage.ancienneTache = CLIC_BLE;

    trouverTailleFenetreclient(numFen, 1263,1009, &tailleFenX, &tailleFenY);
    scrDeplaceFenetre(fenetres[numFen].idFenetre,0,0,tailleFenX,tailleFenY);

    cpt = 0;
    nbrPointsRecoltes = 0;

    rechercheBle(numFen, images[IMAGE_EPI_BLE_1]);
    rechercheBle(numFen, images[IMAGE_EPI_BLE_2]);
    rechercheBle(numFen, images[IMAGE_EPI_BLE_3]);

    qsort(&pointsRecoltes[0],nbrPointsRecoltes,sizeof(POINTSRECOLTES), compare);
    cpt = nbrPointsRecoltes;
    majuscule = FALSE;
    if(cpt > 40)
        cpt = 40;
    //x > 54
    //x < 1209
    //y < 844
    //y > 23
    while(cpt > 0)
    {
        cpt--;
        if(pointsRecoltes[cpt].rect.left > 54 && pointsRecoltes[cpt].rect.left,pointsRecoltes[cpt].rect.right < 1209 && pointsRecoltes[cpt].rect.top > 23 && pointsRecoltes[cpt].rect.bottom < 844)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(pointsRecoltes[cpt].rect.left,pointsRecoltes[cpt].rect.right), aleatoire(pointsRecoltes[cpt].rect.top,pointsRecoltes[cpt].rect.bottom));
            Sleep(20);
            scrSourisClique (1, TRUE, majuscule, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, majuscule, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(100);
            majuscule = TRUE;
        }

    }

	rangerFenetre(numFen);
    deplacement(numFen, directionFaucher[fenetres[numFen].personnage.coordonnees.x+94][fenetres[numFen].personnage.coordonnees.y+99] ,TRUE);

	fenetres[numFen].personnage.imageCellule.largeur = 7;
	fenetres[numFen].personnage.imageCellule.hauteur = 5;
	scrHardCopy(fenetres[numFen].idFenetre, 107, 160, &fenetres[numFen].personnage.imageCellule.largeur, &fenetres[numFen].personnage.imageCellule.hauteur, &fenetres[numFen].personnage.imageCellule.imagePosition);
	ajouterTache(6000, VERIFICATION_CHANGEMENT_CARTE, numFen);
}

BOOL verificationPointsRecolte(RECT rect)
{
    int i;

    for(i = 0; i < nbrPointsRecoltes; i++)
    {
        if((pointsRecoltes[i].rect.left - rect.left) * (pointsRecoltes[i].rect.left - rect.left) + (pointsRecoltes[i].rect.top - rect.top) * (pointsRecoltes[i].rect.top - rect.top) < 100)
            return FALSE;
    }
    return TRUE;
}

int ouAllerPourFaucher(int *pos)
{
    return (directionFaucher[pos[0]][pos[1]]);
}

void lireDirectionFaucher(void)
{// xxx yyy ex : -25 4; 4 -7;...
    FILE *fichier;
    char ligne[200], *p;
    int posx, posy, cptx, cpty;

    fichier = fopen("directionsFaucher.txt","rb");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier directionsFaucher.txt\n");
        exit(1);
    }
    fgets(ligne,200,fichier);
    while(ligne[strlen(ligne)-1] == 10 || ligne[strlen(ligne)-1] == 13)
        ligne[strlen(ligne)-1] = '\0';

    p = ligne;
    while(*p != ' ')
        p++;
    *p = '\0';

    posx = atoi(ligne);
    posy = atoi(p+1);

    logDebug("x : %d, y : %d", posx, posy);


    cpty = 0;
    while(TRUE)
    {
        fgets(ligne,200,fichier);
        p = ligne;

        if(*p == '@')
            break;

        while(p[strlen(p)-1] == 10 || p[strlen(p)-1] == 13)
            p[strlen(p)-1] = '\0';
        cptx = 0;
        while(*p != '\0')
        {
            switch(*p)
            {
                case 'r': directionFaucher[posx + 94 + cptx][posy + 99 + cpty] = 0; break;
                case 'd': directionFaucher[posx + 94 + cptx][posy + 99 + cpty] = 1; break;
                case 'h': directionFaucher[posx + 94 + cptx][posy + 99 + cpty] = 2; break;
                case 'g': directionFaucher[posx + 94 + cptx][posy + 99 + cpty] = 4; break;
                case 'b': directionFaucher[posx + 94 + cptx][posy + 99 + cpty] = 8; break;

                default:
                    printf("Caractere non reconnu dans le fichier directionsFaucher.txt.\n");
                    exit(1);
            }

            p += 2;
            cptx++;
        }
        cpty++;
    }

    /* Log inutile pour le bon fonctionnement du programme */

    /* printf("\n");

    for(cpty = 0; cpty < 10; cpty++)
    {
        for(cptx = 0; cptx < 10; cptx++)
        {
            printf("%d ", directionFaucher[posx + 93 + cptx][posy + 99 + cpty]);
        }
        printf("\n");
    } */

    fclose(fichier);
}
