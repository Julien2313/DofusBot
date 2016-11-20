#include "bot.h"

void initialisation(void)
{
    //scrDebug(1);
    int i, hautEcran, largeurEcran;
    TACHE t;
    RECT monde;

    logInfo("Starting DofusBot v0.1 made by the A-team");
    logInfo("\n\n         _         _");
    logInfo("  /_\\       | |_ ___  __ _ _ __ ___");
    logInfo(" //_\\\\ _____| __/ _ \\/ _` | '_ ` _ \\");
    logInfo("/  _  \\_____| ||  __/ (_| | | | | | |");
    logInfo("\\_/ \\_/      \\__\\___|\\__,_|_| |_| |_| ");

    srand(time(NULL));
    lireCheminDAcces();
    lireDirectionFaucher();

    monde.left = -93;monde.top = -99;monde.right = 49;monde.bottom = 60;
    scrInitialisation(10000, "carteDofus.bin",&monde);


    scrHauteurEcran(&hautEcran);
    scrLargeurEcran(&largeurEcran);
    nbrFenHauteur = hautEcran/HFenetre;
    nbrFenLargeur = largeurEcran/LFenetre;

    logDebug("LARGEUR : %d, HAUTEUR : %d, scrHauteurEcran : %d, scrLargeurEcran : %d\n",nbrFenLargeur, nbrFenHauteur,hautEcran,largeurEcran);
    initialisationTailleFenetre();
    initialiserImages();
    lireIdentifiants();
    for(i = 0; i < NBRFENETREAOUVRIR; i++)
    {
        t.date = 0;//ça va être initialisé dans le ajoutertache !
        t.idTache = INITIALISER_FENETRE;
        t.numFenetre = i;

        ajouterTache(t.date, t.idTache, t.numFenetre);
    }
    //scrAfficheCarte();
}

void initialisationTailleFenetre(void)
{
    int numFen;
    RECT dimensionsClient, dimensionsFenetre;

    numFen = ouvrirDofusInitiliser();
    rangerFenetre(numFen);


    scrRecupDimensionsFenetre(fenetres[numFen].idFenetre, &dimensionsFenetre, &dimensionsClient);
    /*
    printf("(%ld,%ld)->(%ld,%ld); (%ld,%ld)->(%ld,%ld)\n",dimensionsFenetre.left, dimensionsFenetre.top, dimensionsFenetre.right, dimensionsFenetre.bottom,dimensionsClient.left, dimensionsClient.top, dimensionsClient.right, dimensionsClient.bottom);
    printf("Largeur totale de la fenetre : %ld\n", dimensionsFenetre.right-dimensionsFenetre.left);
    printf("Hauteur totale de la fenetre : %ld\n", dimensionsFenetre.bottom-dimensionsFenetre.top);

    printf("Largeur client : %ld\n", dimensionsClient.right-dimensionsClient.left);
    printf("Hauteur client : %ld\n", dimensionsClient.bottom-dimensionsClient.top);

    printf("Bordure gauche : %ld\n", dimensionsClient.left-dimensionsFenetre.left);
    printf("Bordure droite : %ld\n", dimensionsFenetre.right-dimensionsClient.right);

    printf("Bordure haut : %ld\n", dimensionsClient.top-dimensionsFenetre.top);
    printf("Bordure bas : %ld\n\n\n\n", dimensionsFenetre.bottom-dimensionsClient.bottom);
*/
    lBordureHaut = dimensionsClient.top - dimensionsFenetre.top;
    lBordureBas = dimensionsFenetre.bottom - dimensionsClient.bottom;
    lBordureGauche = dimensionsClient.left - dimensionsFenetre.left;
    lBordureDroite = dimensionsFenetre.right - dimensionsClient.right;

    LFenetre = LClient + lBordureGauche + lBordureDroite;
    HFenetre = HClient + lBordureHaut   + lBordureBas;

    rangerFenetre(numFen);


    scrRecupDimensionsFenetre(fenetres[numFen].idFenetre, &dimensionsFenetre, &dimensionsClient);
    /*
    printf("(%ld,%ld)->(%ld,%ld); (%ld,%ld)->(%ld,%ld)\n",dimensionsFenetre.left, dimensionsFenetre.top, dimensionsFenetre.right, dimensionsFenetre.bottom,dimensionsClient.left, dimensionsClient.top, dimensionsClient.right, dimensionsClient.bottom);
    printf("Largeur totale de la fenetre : %ld\n", dimensionsFenetre.right-dimensionsFenetre.left);
    printf("Hauteur totale de la fenetre : %ld\n", dimensionsFenetre.bottom-dimensionsFenetre.top);

    printf("Largeur client : %ld\n", dimensionsClient.right-dimensionsClient.left);
    printf("Hauteur client : %ld\n", dimensionsClient.bottom-dimensionsClient.top);

    printf("Bordure gauche : %ld\n", dimensionsClient.left-dimensionsFenetre.left);
    printf("Bordure droite : %ld\n", dimensionsFenetre.right-dimensionsClient.right);

    printf("Bordure haut : %ld\n", dimensionsClient.top-dimensionsFenetre.top);
    printf("Bordure bas : %ld\n\n\n\n", dimensionsFenetre.bottom-dimensionsClient.bottom);
    */
    rangerFenetre(numFen);
    scrRecupDimensionsFenetre(fenetres[numFen].idFenetre, &dimensionsFenetre, &dimensionsClient);
    /*
    printf("(%ld,%ld)->(%ld,%ld); (%ld,%ld)->(%ld,%ld)\n",dimensionsFenetre.left, dimensionsFenetre.top, dimensionsFenetre.right, dimensionsFenetre.bottom,dimensionsClient.left, dimensionsClient.top, dimensionsClient.right, dimensionsClient.bottom);
    printf("Largeur totale de la fenetre : %ld\n", dimensionsFenetre.right-dimensionsFenetre.left);
    printf("Hauteur totale de la fenetre : %ld\n", dimensionsFenetre.bottom-dimensionsFenetre.top);

    printf("Largeur client : %ld\n", dimensionsClient.right-dimensionsClient.left);
    printf("Hauteur client : %ld\n", dimensionsClient.bottom-dimensionsClient.top);

    printf("Bordure gauche : %ld\n", dimensionsClient.left-dimensionsFenetre.left);
    printf("Bordure droite : %ld\n", dimensionsFenetre.right-dimensionsClient.right);

    printf("Bordure haut : %ld\n", dimensionsClient.top-dimensionsFenetre.top);
    printf("Bordure bas : %ld\n", dimensionsFenetre.bottom-dimensionsClient.bottom);
*/
    fermerFenetre(numFen);
}


int ouvrirDofusInitiliser(void)
{
    int res;
    if((err = scrLanceProgramme(cheminDofus, &res)) != scrOK)
    {
        printf("Impossible d'ouvrir le jeu \n\n");
        afficherErreur();
    }
    return res;
}

void initialiserFenetre(int numFen)
{
    int erreur;
    erreur = slectionnerPersonnageDisponible(numFen, &fenetres[numFen].personnage.pseudo,personnages[nbrIDLut]);
    if(erreur == -1)
    {
        printf("Plus de compte disponibles !");
        return;
    }
    fenetres[numFen].idFenetre = ouvrirDofus();

    rangerFenetre(numFen);

}

int slectionnerPersonnageDisponible(int numFen)
{
    int i;
    scrTempsMs(&temps);
    for(i = 0; i < nbrPersonnages; i++)
    {
        if(personnages[i].connecte == 0 && (personnages[i].heureDeconnexion < temps + 1800000))
        {
            strcpy(fenetres[numFen].personnage.pseudo,personnages[i].pseudo);
            strcpy(fenetres[numFen].personnage.code,personnages[i].code);
            return 1;
        }

    }

    return -1;
}

void changerPersonnageFenetre(int numFen)
{
    int erreur;
    erreur = slectionnerPersonnageDisponible(numFen);
    if(erreur == -1)
    {
        printf("Plus de compte disponibles !");
        return;
    }
}

void initialisationPersonnage(int numFen)
{
    int tailleFenX, tailleFenY;
    trouverTailleFenetreclient(numFen, 1263,1009, &tailleFenX, &tailleFenY);
    scrDeplaceFenetre(fenetres[numFen].idFenetre,0,0,tailleFenX,tailleFenY);
    COLORREF couleurFond = RGB(255,255,255);
    COLORREF couleurGeneral = RGB(224,238,255);
    int positionX, positionGeneralY, positionPriveY, positionInfoY, positionGuildeY, positionAllianceY, positionCommerceY, positionRecrutementY, positionAnkamaY;
    COLORREF couleur;
    positionX = 509;
    positionGeneralY         = 881;
    positionPriveY           = 895;
    positionInfoY            = 909;
    positionGuildeY          = 922;
    positionAllianceY        = 936;
    positionCommerceY        = 950;
    positionRecrutementY     = 964;
    positionAnkamaY          = 978;

    //Évitez les défis/échanges
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,730,520,150,60, images[IMAGE_IGNORER].id  , images[IMAGE_IGNORER].rect, images[IMAGE_IGNORER].nbrMaxPts  , &images[IMAGE_IGNORER].nbrTrouvees, images[IMAGE_IGNORER].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_IGNORER].nbrTrouvees > 0)
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\033");
    }
    else
        afficherErreur();

    Sleep(300);
    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, " ");

    //Évitez les défis/échanges
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,730,520,150,60, images[IMAGE_IGNORER].id  , images[IMAGE_IGNORER].rect, images[IMAGE_IGNORER].nbrMaxPts  , &images[IMAGE_IGNORER].nbrTrouvees, images[IMAGE_IGNORER].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_IGNORER].nbrTrouvees > 0)
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\033");
    }
    else
        afficherErreur();

    Sleep(300);
    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "/privé");

    //Évitez les défis/échanges
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,730,520,150,60, images[IMAGE_IGNORER].id  , images[IMAGE_IGNORER].rect, images[IMAGE_IGNORER].nbrMaxPts  , &images[IMAGE_IGNORER].nbrTrouvees, images[IMAGE_IGNORER].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_IGNORER].nbrTrouvees > 0)
            scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\033");
    }
    else
        afficherErreur();
    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");

    //on coupe les canaux
    if((err = scrRecupCouleurPixel(fenetres[numFen].idFenetre, 508, 876, &couleur)) == scrOK)
    {
        if(couleur != couleurGeneral)
        {
            printf("Vous êtes dans le chat avance !\n");
            exit(1);
        }

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionGeneralY, &couleur)) == scrOK)
        {
            if(couleur != couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionGeneralY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("General !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionPriveY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionPriveY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Prive !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionInfoY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionInfoY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Informations !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionGuildeY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionGuildeY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Guilde !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionAllianceY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionAllianceY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Alliance !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionCommerceY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionCommerceY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Commerce !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionRecrutementY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionRecrutementY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Recrutement !\n");
            }
        }
        else
            afficherErreur();

        if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionAnkamaY, &couleur)) == scrOK)
        {
            if(couleur == couleurFond)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionAnkamaY);
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
                printf("Ankama !\n");
            }
        }
        else
            afficherErreur();
    }
    else
        afficherErreur();


    //On enlève les coordonnées
    do
    {
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,9999,9999, images[IMAGE_AFFICHER_COORDONNEES].id  , images[IMAGE_AFFICHER_COORDONNEES].rect, images[IMAGE_AFFICHER_COORDONNEES].nbrMaxPts  , &images[IMAGE_AFFICHER_COORDONNEES].nbrTrouvees, images[IMAGE_AFFICHER_COORDONNEES].nbrPixelsFaux  )) == scrOK)
        {
            if(images[IMAGE_AFFICHER_COORDONNEES].nbrTrouvees > 0)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_AFFICHER_COORDONNEES].rect[0].left,images[IMAGE_AFFICHER_COORDONNEES].rect[0].right), aleatoire(images[IMAGE_AFFICHER_COORDONNEES].rect[0].top,images[IMAGE_AFFICHER_COORDONNEES].rect[0].bottom));
                Sleep(400);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(400);
            }
        }
        else
            afficherErreur();
    }
    while(images[IMAGE_AFFICHER_COORDONNEES].nbrTrouvees > 0);

    /*//OCR

    //on test si les coordonnées sont bien affichées
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,519,939,33,31, images[IMAGE_INFORMATIONS_CARTE].id  , images[IMAGE_INFORMATIONS_CARTE].rect, images[IMAGE_INFORMATIONS_CARTE].nbrMaxPts  , &images[IMAGE_INFORMATIONS_CARTE].nbrTrouvees, images[IMAGE_INFORMATIONS_CARTE].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_INFORMATIONS_CARTE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_INFORMATIONS_CARTE].rect[0].left,images[IMAGE_INFORMATIONS_CARTE].rect[0].right), aleatoire(images[IMAGE_INFORMATIONS_CARTE].rect[0].top,images[IMAGE_INFORMATIONS_CARTE].rect[0].bottom));
            Sleep(400);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(400);
        }
    }
    else
        afficheErreur();
    scrOcrCoordonneesDofus(fenetres[numFen].idFenetre, 14, 47, 100, 17, &coordonnees);
    */

    //Évitez les invitations de groupe
    do
    {
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,9999,9999, images[IMAGE_CROIX_INVITATION].id  , images[IMAGE_CROIX_INVITATION].rect, images[IMAGE_CROIX_INVITATION].nbrMaxPts  , &images[IMAGE_CROIX_INVITATION].nbrTrouvees, images[IMAGE_CROIX_INVITATION].nbrPixelsFaux  )) == scrOK)
        {
            if(images[IMAGE_CROIX_INVITATION].nbrTrouvees > 0)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_CROIX_INVITATION].rect[0].left,images[IMAGE_CROIX_INVITATION].rect[0].right), aleatoire(images[IMAGE_CROIX_INVITATION].rect[0].top,images[IMAGE_CROIX_INVITATION].rect[0].bottom));
                Sleep(400);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(400);
            }
        }
        else
            afficherErreur();
    }
    while(images[IMAGE_CROIX_INVITATION].nbrTrouvees > 0);

    //scrSauveImage(fenetres[numFen].idFenetre,0,0,1000,1000,"test.bmp");
    do{

        EmptyClipboard();
        scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, " ");
        Sleep(200);
        scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "%pos%");
        Sleep(200);
        scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");
        Sleep(200);

        scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(30,455), aleatoire(970,978));
        Sleep(300);
        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        Sleep(100);
        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        Sleep(100);
        scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
        Sleep(100);

        scrClavierEnvoiControle(fenetres[numFen].idFenetre,'C');
        Sleep(100);
        err = scrRecupCoordonneesCellule(&fenetres[numFen].personnage.coordonnees);
        //Sleep(4000);

    }while(err == scrPAS_DE_TEXTE || err == scrPAS_DE_COORDS_DS_PP);
    if(err != scrOK)
        afficherErreur();

    if((err = scrRecupCouleurPixel   (fenetres[numFen].idFenetre, positionX, positionGeneralY, &couleur)) == scrOK)
    {
        if(couleur == couleurFond)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, positionX,  positionGeneralY);
            Sleep(300);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(300);
            printf("General !\n");
        }
    }
    else
        afficherErreur();

    rangerFenetre(numFen);

    //Enlever les informations à gauche
    do{
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_CROIX_MESSAGE].id  , images[IMAGE_CROIX_MESSAGE].rect, images[IMAGE_CROIX_MESSAGE].nbrMaxPts  , &images[IMAGE_CROIX_MESSAGE].nbrTrouvees, images[IMAGE_CROIX_MESSAGE].nbrPixelsFaux  )) == scrOK)
        {
            if(images[IMAGE_CROIX_MESSAGE].nbrTrouvees > 0)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_CROIX_MESSAGE].rect[0].left,images[IMAGE_CROIX_MESSAGE].rect[0].right), aleatoire(images[IMAGE_CROIX_MESSAGE].rect[0].top,images[IMAGE_CROIX_MESSAGE].rect[0].bottom));
                Sleep(300);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(300);
            }
        }
        else
            afficherErreur();

    }while(images[IMAGE_CROIX_MESSAGE].nbrTrouvees > 0);

    printf("[%ld,%ld] %s\n",fenetres[numFen].personnage.coordonnees.x, fenetres[numFen].personnage.coordonnees.y, fenetres[numFen].personnage.pseudo);
    //il faudra encore afficher les pods


    //ajouterTache(1000, COMBAT_TEST, numFen);
    ajouterTache(20000, CHECK_LIST, numFen);
    ajouterTache(1000, ALLEZFAUCHER, numFen);
}

void initialiserImages(void)
{
    int idImage;
    strcpy(images[IMAGE_JOUER].cheminNom, "images\\jouer.bmp");
    if(scrChargeImage(images[IMAGE_JOUER].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_JOUER].id = idImage;
    images[IMAGE_JOUER].nbrMaxPts = 1;
    images[IMAGE_JOUER].tolerance = 0;
    images[IMAGE_JOUER].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_ERREUR_CONNEXION_MENU].cheminNom, "images\\erreur_connexion_menu.bmp");
    if(scrChargeImage(images[IMAGE_ERREUR_CONNEXION_MENU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_ERREUR_CONNEXION_MENU].id = idImage;
    images[IMAGE_ERREUR_CONNEXION_MENU].nbrMaxPts = 1;
    images[IMAGE_ERREUR_CONNEXION_MENU].tolerance = 0;
    images[IMAGE_ERREUR_CONNEXION_MENU].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_JOUER_CHARGEMENT].cheminNom, "images\\jouer_chargement.bmp");
    if(scrChargeImage(images[IMAGE_JOUER_CHARGEMENT].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_JOUER_CHARGEMENT].id = idImage;
    images[IMAGE_JOUER_CHARGEMENT].nbrMaxPts = 1;
    images[IMAGE_JOUER_CHARGEMENT].tolerance = 0;
    images[IMAGE_JOUER_CHARGEMENT].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_JOUER_FILE_ATTENTE].cheminNom, "images\\jouer_file_attente.bmp");
    if(scrChargeImage(images[IMAGE_JOUER_FILE_ATTENTE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_JOUER_FILE_ATTENTE].id = idImage;
    images[IMAGE_JOUER_FILE_ATTENTE].nbrMaxPts = 1;
    images[IMAGE_JOUER_FILE_ATTENTE].tolerance = 0;
    images[IMAGE_JOUER_FILE_ATTENTE].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_SERVEUR_INACCESSIBLE].cheminNom, "images\\serveur_inaccessible.bmp");
    if(scrChargeImage(images[IMAGE_SERVEUR_INACCESSIBLE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SERVEUR_INACCESSIBLE].id = idImage;
    images[IMAGE_SERVEUR_INACCESSIBLE].nbrMaxPts = 1;
    images[IMAGE_SERVEUR_INACCESSIBLE].tolerance = 0;
    images[IMAGE_SERVEUR_INACCESSIBLE].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_LISTE_SERVEURS].cheminNom, "images\\liste_serveurs.bmp");
    if(scrChargeImage(images[IMAGE_LISTE_SERVEURS].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_LISTE_SERVEURS].id = idImage;
    images[IMAGE_LISTE_SERVEURS].nbrMaxPts = 1;
    images[IMAGE_LISTE_SERVEURS].tolerance = 0;
    images[IMAGE_LISTE_SERVEURS].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].cheminNom, "images\\serveur_agride_accessible.bmp");
    if(scrChargeImage(images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].id = idImage;
    images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrMaxPts = 1;
    images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].tolerance = 0;
    images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_SELECTIONNER_CHARGEMENT].cheminNom, "images\\selectionner_chargement.bmp");
    if(scrChargeImage(images[IMAGE_SELECTIONNER_CHARGEMENT].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SELECTIONNER_CHARGEMENT].id = idImage;
    images[IMAGE_SELECTIONNER_CHARGEMENT].nbrMaxPts = 1;
    images[IMAGE_SELECTIONNER_CHARGEMENT].tolerance = 0;
    images[IMAGE_SELECTIONNER_CHARGEMENT].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_SELECTONNER_FILE_ATTENTE].cheminNom, "images\\selectionner_file_attente.bmp");
    if(scrChargeImage(images[IMAGE_SELECTONNER_FILE_ATTENTE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SELECTONNER_FILE_ATTENTE].id = idImage;
    images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrMaxPts = 1;
    images[IMAGE_SELECTONNER_FILE_ATTENTE].tolerance = 0;
    images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_JOUER_SELECTON_PERSONNAGE].cheminNom, "images\\jouer_selection_personnage.bmp");
    if(scrChargeImage(images[IMAGE_JOUER_SELECTON_PERSONNAGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_JOUER_SELECTON_PERSONNAGE].id = idImage;
    images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrMaxPts = 1;
    images[IMAGE_JOUER_SELECTON_PERSONNAGE].tolerance = 0;
    images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrPixelsFaux = 0;

////////////////////////////////////////////////////////////////////////////////

    strcpy(images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].cheminNom, "images\\etoile_chat_x_max_10_et_y_min_160.bmp");
    if(scrChargeImage(images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].id = idImage;
    images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrMaxPts = 1;
    images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].tolerance = 0;
    images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_INFORMATIONS_CARTE].cheminNom, "images\\informations_carte.bmp");
    if(scrChargeImage(images[IMAGE_INFORMATIONS_CARTE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_INFORMATIONS_CARTE].id = idImage;
    images[IMAGE_INFORMATIONS_CARTE].nbrMaxPts = 1;
    images[IMAGE_INFORMATIONS_CARTE].tolerance = 0;
    images[IMAGE_INFORMATIONS_CARTE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_DISPONIBILITE].cheminNom, "images\\disponibilite.bmp");
    if(scrChargeImage(images[IMAGE_DISPONIBILITE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_DISPONIBILITE].id = idImage;
    images[IMAGE_DISPONIBILITE].nbrMaxPts = 1;
    images[IMAGE_DISPONIBILITE].tolerance = 0;
    images[IMAGE_DISPONIBILITE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_PRIVE].cheminNom, "images\\prive.bmp");
    if(scrChargeImage(images[IMAGE_PRIVE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_PRIVE].id = idImage;
    images[IMAGE_PRIVE].nbrMaxPts = 1;
    images[IMAGE_PRIVE].tolerance = 0;
    images[IMAGE_PRIVE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_PRIVE2].cheminNom, "images\\prive2.bmp");
    if(scrChargeImage(images[IMAGE_PRIVE2].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_PRIVE2].id = idImage;
    images[IMAGE_PRIVE2].nbrMaxPts = 1;
    images[IMAGE_PRIVE2].tolerance = 0;
    images[IMAGE_PRIVE2].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CROIX_COMBAT].cheminNom, "images\\croix_combat.bmp");
    if(scrChargeImage(images[IMAGE_CROIX_COMBAT].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CROIX_COMBAT].id = idImage;
    images[IMAGE_CROIX_COMBAT].nbrMaxPts = 1;
    images[IMAGE_CROIX_COMBAT].tolerance = 0;
    images[IMAGE_CROIX_COMBAT].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].cheminNom, "images\\serveur_agride_maintenance.bmp");
    if(scrChargeImage(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].id = idImage;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrMaxPts = 1;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].tolerance = 0;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].cheminNom, "images\\serveur_agride_maintenance_chargement.bmp");
    if(scrChargeImage(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].id = idImage;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrMaxPts = 1;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].tolerance = 0;
    images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CROIX_INVITATION].cheminNom, "images\\croix_invitation.bmp");
    if(scrChargeImage(images[IMAGE_CROIX_INVITATION].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CROIX_INVITATION].id = idImage;
    images[IMAGE_CROIX_INVITATION].nbrMaxPts = 1;
    images[IMAGE_CROIX_INVITATION].tolerance = 0;
    images[IMAGE_CROIX_INVITATION].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_IGNORER].cheminNom, "images\\ignorer.bmp");
    if(scrChargeImage(images[IMAGE_IGNORER].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_IGNORER].id = idImage;
    images[IMAGE_IGNORER].nbrMaxPts = 1;
    images[IMAGE_IGNORER].tolerance = 0;
    images[IMAGE_IGNORER].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_PETIT_IGNORE].cheminNom, "images\\petit_ignore.bmp");
    if(scrChargeImage(images[IMAGE_PETIT_IGNORE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_PETIT_IGNORE].id = idImage;
    images[IMAGE_PETIT_IGNORE].nbrMaxPts = 1;
    images[IMAGE_PETIT_IGNORE].tolerance = 0;
    images[IMAGE_PETIT_IGNORE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_GAUCHE_ORANGE].cheminNom, "images\\fleche_gauche_orange.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_GAUCHE_ORANGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_GAUCHE_ORANGE].id = idImage;
    images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrMaxPts = 1;
    images[IMAGE_FLECHE_GAUCHE_ORANGE].tolerance = 0;
    images[IMAGE_FLECHE_GAUCHE_ORANGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_DROITE_ORANGE].cheminNom, "images\\fleche_droite_orange.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_DROITE_ORANGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_DROITE_ORANGE].id = idImage;
    images[IMAGE_FLECHE_DROITE_ORANGE].nbrMaxPts = 1;
    images[IMAGE_FLECHE_DROITE_ORANGE].tolerance = 0;
    images[IMAGE_FLECHE_DROITE_ORANGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_HAUT_ORANGE].cheminNom, "images\\fleche_haut_orange.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_HAUT_ORANGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_HAUT_ORANGE].id = idImage;
    images[IMAGE_FLECHE_HAUT_ORANGE].nbrMaxPts = 1;
    images[IMAGE_FLECHE_HAUT_ORANGE].tolerance = 0;
    images[IMAGE_FLECHE_HAUT_ORANGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_BAS_ORANGE].cheminNom, "images\\fleche_bas_orange.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_BAS_ORANGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_BAS_ORANGE].id = idImage;
    images[IMAGE_FLECHE_BAS_ORANGE].nbrMaxPts = 1;
    images[IMAGE_FLECHE_BAS_ORANGE].tolerance = 0;
    images[IMAGE_FLECHE_BAS_ORANGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_GAUCHE_BLEU].cheminNom, "images\\fleche_gauche_bleu.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_GAUCHE_BLEU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_GAUCHE_BLEU].id = idImage;
    images[IMAGE_FLECHE_GAUCHE_BLEU].nbrMaxPts = 1;
    images[IMAGE_FLECHE_GAUCHE_BLEU].tolerance = 0;
    images[IMAGE_FLECHE_GAUCHE_BLEU].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_DROITE_BLEU].cheminNom, "images\\fleche_droite_bleu.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_DROITE_BLEU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_DROITE_BLEU].id = idImage;
    images[IMAGE_FLECHE_DROITE_BLEU].nbrMaxPts = 1;
    images[IMAGE_FLECHE_DROITE_BLEU].tolerance = 0;
    images[IMAGE_FLECHE_DROITE_BLEU].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_HAUT_BLEU].cheminNom, "images\\fleche_haut_bleu.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_HAUT_BLEU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_HAUT_BLEU].id = idImage;
    images[IMAGE_FLECHE_HAUT_BLEU].nbrMaxPts = 1;
    images[IMAGE_FLECHE_HAUT_BLEU].tolerance = 0;
    images[IMAGE_FLECHE_HAUT_BLEU].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_BAS_BLEU].cheminNom, "images\\fleche_bas_bleu.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_BAS_BLEU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_BAS_BLEU].id = idImage;
    images[IMAGE_FLECHE_BAS_BLEU].nbrMaxPts = 1;
    images[IMAGE_FLECHE_BAS_BLEU].tolerance = 0;
    images[IMAGE_FLECHE_BAS_BLEU].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].cheminNom, "images\\connexion_serveur_interrompue.bmp");
    if(scrChargeImage(images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].id = idImage;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrMaxPts = 1;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].tolerance = 0;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].cheminNom, "images\\connexion_serveur_interrompue_grand.bmp");
    if(scrChargeImage(images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].id = idImage;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].nbrMaxPts = 1;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].tolerance = 0;
    images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE_GRAND].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CROIX_MESSAGE].cheminNom, "images\\croix_message.bmp");
    if(scrChargeImage(images[IMAGE_CROIX_MESSAGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CROIX_MESSAGE].id = idImage;
    images[IMAGE_CROIX_MESSAGE].nbrMaxPts = 1;
    images[IMAGE_CROIX_MESSAGE].tolerance = 0;
    images[IMAGE_CROIX_MESSAGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_PAS_MAINTENANT_CADEAU].cheminNom, "images\\pas_maintenant_cadeau.bmp");
    if(scrChargeImage(images[IMAGE_PAS_MAINTENANT_CADEAU].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_PAS_MAINTENANT_CADEAU].id = idImage;
    images[IMAGE_PAS_MAINTENANT_CADEAU].nbrMaxPts = 1;
    images[IMAGE_PAS_MAINTENANT_CADEAU].tolerance = 0;
    images[IMAGE_PAS_MAINTENANT_CADEAU].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_DOFUS].cheminNom, "images\\dofus.bmp");
    if(scrChargeImage(images[IMAGE_DOFUS].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_DOFUS].id = idImage;
    images[IMAGE_DOFUS].nbrMaxPts = 1;
    images[IMAGE_DOFUS].tolerance = 0;
    images[IMAGE_DOFUS].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_EPI_BLE_1].cheminNom, "images\\epi_ble_1.bmp");
    if(scrChargeImage(images[IMAGE_EPI_BLE_1].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_EPI_BLE_1].id = idImage;
    images[IMAGE_EPI_BLE_1].nbrMaxPts = 100;
    images[IMAGE_EPI_BLE_1].tolerance = 0;
    images[IMAGE_EPI_BLE_1].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_EPI_BLE_2].cheminNom, "images\\epi_ble_2.bmp");
    if(scrChargeImage(images[IMAGE_EPI_BLE_2].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_EPI_BLE_2].id = idImage;
    images[IMAGE_EPI_BLE_2].nbrMaxPts = 100;
    images[IMAGE_EPI_BLE_2].tolerance = 0;
    images[IMAGE_EPI_BLE_2].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_EPI_BLE_3].cheminNom, "images\\epi_ble_3.bmp");
    if(scrChargeImage(images[IMAGE_EPI_BLE_3].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_EPI_BLE_3].id = idImage;
    images[IMAGE_EPI_BLE_3].nbrMaxPts = 100;
    images[IMAGE_EPI_BLE_3].tolerance = 0;
    images[IMAGE_EPI_BLE_3].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_EPI_BLE_4].cheminNom, "images\\epi_ble_4.bmp");
    if(scrChargeImage(images[IMAGE_EPI_BLE_4].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_EPI_BLE_4].id = idImage;
    images[IMAGE_EPI_BLE_4].nbrMaxPts = 100;
    images[IMAGE_EPI_BLE_4].tolerance = 0;
    images[IMAGE_EPI_BLE_4].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_EPI_BLE_5].cheminNom, "images\\epi_ble_5.bmp");
    if(scrChargeImage(images[IMAGE_EPI_BLE_5].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_EPI_BLE_5].id = idImage;
    images[IMAGE_EPI_BLE_5].nbrMaxPts = 100;
    images[IMAGE_EPI_BLE_5].tolerance = 0;
    images[IMAGE_EPI_BLE_5].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_COMBAT_PRET].cheminNom, "images\\combat_pret.bmp");
    if(scrChargeImage(images[IMAGE_COMBAT_PRET].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_COMBAT_PRET].id = idImage;
    images[IMAGE_COMBAT_PRET].nbrMaxPts = 100;
    images[IMAGE_COMBAT_PRET].tolerance = 0;
    images[IMAGE_COMBAT_PRET].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FERME_RESUME_COMBAT].cheminNom, "images\\ferme_resume_combat.bmp");
    if(scrChargeImage(images[IMAGE_FERME_RESUME_COMBAT].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FERME_RESUME_COMBAT].id = idImage;
    images[IMAGE_FERME_RESUME_COMBAT].nbrMaxPts = 100;
    images[IMAGE_FERME_RESUME_COMBAT].tolerance = 0;
    images[IMAGE_FERME_RESUME_COMBAT].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_SORT_RONCE_CIBLE].cheminNom, "images\\sort_ronce_cible.bmp");
    if(scrChargeImage(images[IMAGE_SORT_RONCE_CIBLE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SORT_RONCE_CIBLE].id = idImage;
    images[IMAGE_SORT_RONCE_CIBLE].nbrMaxPts = 100;
    images[IMAGE_SORT_RONCE_CIBLE].tolerance = 0;
    images[IMAGE_SORT_RONCE_CIBLE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_SORT_RONCE].cheminNom, "images\\sort_ronce.bmp");
    if(scrChargeImage(images[IMAGE_SORT_RONCE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_SORT_RONCE].id = idImage;
    images[IMAGE_SORT_RONCE].nbrMaxPts = 100;
    images[IMAGE_SORT_RONCE].tolerance = 0;
    images[IMAGE_SORT_RONCE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_COMBAT_MODE_TACTIQUE].cheminNom, "images\\combat_mode_tactic.bmp");
    if(scrChargeImage(images[IMAGE_COMBAT_MODE_TACTIQUE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_COMBAT_MODE_TACTIQUE].id = idImage;
    images[IMAGE_COMBAT_MODE_TACTIQUE].nbrMaxPts = 100;
    images[IMAGE_COMBAT_MODE_TACTIQUE].tolerance = 0;
    images[IMAGE_COMBAT_MODE_TACTIQUE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_COMBAT_MODE_CREATURE].cheminNom, "images\\combat_mode_creature.bmp");
    if(scrChargeImage(images[IMAGE_COMBAT_MODE_CREATURE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_COMBAT_MODE_CREATURE].id = idImage;
    images[IMAGE_COMBAT_MODE_CREATURE].nbrMaxPts = 100;
    images[IMAGE_COMBAT_MODE_CREATURE].tolerance = 0;
    images[IMAGE_COMBAT_MODE_CREATURE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FERMER_CHALLENGE].cheminNom, "images\\fermer_challenge.bmp");
    if(scrChargeImage(images[IMAGE_FERMER_CHALLENGE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FERMER_CHALLENGE].id = idImage;
    images[IMAGE_FERMER_CHALLENGE].nbrMaxPts = 100;
    images[IMAGE_FERMER_CHALLENGE].tolerance = 0;
    images[IMAGE_FERMER_CHALLENGE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_FLECHE_TIMELINE].cheminNom, "images\\fleche_timeline.bmp");
    if(scrChargeImage(images[IMAGE_FLECHE_TIMELINE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_FLECHE_TIMELINE].id = idImage;
    images[IMAGE_FLECHE_TIMELINE].nbrMaxPts = 100;
    images[IMAGE_FLECHE_TIMELINE].tolerance = 0;
    images[IMAGE_FLECHE_TIMELINE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_AFFICHER_COORDONNEES].cheminNom, "images\\afficher_coordonnees.bmp");
    if(scrChargeImage(images[IMAGE_AFFICHER_COORDONNEES].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_AFFICHER_COORDONNEES].id = idImage;
    images[IMAGE_AFFICHER_COORDONNEES].nbrMaxPts = 100;
    images[IMAGE_AFFICHER_COORDONNEES].tolerance = 0;
    images[IMAGE_AFFICHER_COORDONNEES].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_CROIX_FENETRE_UP].cheminNom, "images\\croix_fenetre_up.bmp");
    if(scrChargeImage(images[IMAGE_CROIX_FENETRE_UP].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_CROIX_FENETRE_UP].id = idImage;
    images[IMAGE_CROIX_FENETRE_UP].nbrMaxPts = 100;
    images[IMAGE_CROIX_FENETRE_UP].tolerance = 0;
    images[IMAGE_CROIX_FENETRE_UP].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_NO_UPDATER].cheminNom, "images\\no_updater.bmp");
    if(scrChargeImage(images[IMAGE_NO_UPDATER].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_NO_UPDATER].id = idImage;
    images[IMAGE_NO_UPDATER].nbrMaxPts = 100;
    images[IMAGE_NO_UPDATER].tolerance = 0;
    images[IMAGE_NO_UPDATER].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_ICONE_INVENTAIRE].cheminNom, "images\\icone_inventaire.bmp");
    if(scrChargeImage(images[IMAGE_ICONE_INVENTAIRE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_ICONE_INVENTAIRE].id = idImage;
    images[IMAGE_ICONE_INVENTAIRE].nbrMaxPts = 100;
    images[IMAGE_ICONE_INVENTAIRE].tolerance = 0;
    images[IMAGE_ICONE_INVENTAIRE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_ICONE_RESSOURCES].cheminNom, "images\\icone_ressources.bmp");
    if(scrChargeImage(images[IMAGE_ICONE_RESSOURCES].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_ICONE_RESSOURCES].id = idImage;
    images[IMAGE_ICONE_RESSOURCES].nbrMaxPts = 100;
    images[IMAGE_ICONE_RESSOURCES].tolerance = 0;
    images[IMAGE_ICONE_RESSOURCES].nbrPixelsFaux = 0;


//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_BLE_INVENTAIRE].cheminNom, "images\\ble_inventaire.bmp");
    if(scrChargeImage(images[IMAGE_BLE_INVENTAIRE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_BLE_INVENTAIRE].id = idImage;
    images[IMAGE_BLE_INVENTAIRE].nbrMaxPts = 100;
    images[IMAGE_BLE_INVENTAIRE].tolerance = 0;
    images[IMAGE_BLE_INVENTAIRE].nbrPixelsFaux = 0;


//-------------------------------------------------------------------------------------------------------------

    strcpy(images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].cheminNom, "images\\texte_detruire_inventaire.bmp");
    if(scrChargeImage(images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].id = idImage;
    images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrMaxPts = 100;
    images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].tolerance = 0;
    images[IMAGE_TEXTE_DETRUIRE_INVENTAIRE].nbrPixelsFaux = 0;


//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_INVENTAIRE_EN_LETTRE].cheminNom, "images\\inventaire_en_lettre.bmp");
    if(scrChargeImage(images[IMAGE_INVENTAIRE_EN_LETTRE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_INVENTAIRE_EN_LETTRE].id = idImage;
    images[IMAGE_INVENTAIRE_EN_LETTRE].nbrMaxPts = 100;
    images[IMAGE_INVENTAIRE_EN_LETTRE].tolerance = 0;
    images[IMAGE_INVENTAIRE_EN_LETTRE].nbrPixelsFaux = 0;


//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_BOUTON_OK_DELETE].cheminNom, "images\\bouton_ok_delete.bmp");
    if(scrChargeImage(images[IMAGE_BOUTON_OK_DELETE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_BOUTON_OK_DELETE].id = idImage;
    images[IMAGE_BOUTON_OK_DELETE].nbrMaxPts = 100;
    images[IMAGE_BOUTON_OK_DELETE].tolerance = 0;
    images[IMAGE_BOUTON_OK_DELETE].nbrPixelsFaux = 0;



//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_PORTE].cheminNom, "images\\maison_porte.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_PORTE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_PORTE].id = idImage;
    images[IMAGE_MAISON_PORTE].nbrMaxPts = 100;
    images[IMAGE_MAISON_PORTE].tolerance = 0;
    images[IMAGE_MAISON_PORTE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_CODE].cheminNom, "images\\maison_code.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_CODE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_CODE].id = idImage;
    images[IMAGE_MAISON_CODE].nbrMaxPts = 100;
    images[IMAGE_MAISON_CODE].tolerance = 0;
    images[IMAGE_MAISON_CODE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_BOUTON_OK].cheminNom, "images\\bouton_ok.bmp");
    if(scrChargeImage(images[IMAGE_BOUTON_OK].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_BOUTON_OK].id = idImage;
    images[IMAGE_BOUTON_OK].nbrMaxPts = 100;
    images[IMAGE_BOUTON_OK].tolerance = 0;
    images[IMAGE_BOUTON_OK].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_ESCALIER].cheminNom, "images\\maison_escalier.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_ESCALIER].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_ESCALIER].id = idImage;
    images[IMAGE_MAISON_ESCALIER].nbrMaxPts = 100;
    images[IMAGE_MAISON_ESCALIER].tolerance = 0;
    images[IMAGE_MAISON_ESCALIER].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_COFFRE].cheminNom, "images\\maison_coffre.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_COFFRE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_COFFRE].id = idImage;
    images[IMAGE_MAISON_COFFRE].nbrMaxPts = 100;
    images[IMAGE_MAISON_COFFRE].tolerance = 0;
    images[IMAGE_MAISON_COFFRE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_ESCALIER_SORTIE].cheminNom, "images\\maison_escalier_sortie.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_ESCALIER_SORTIE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_ESCALIER_SORTIE].id = idImage;
    images[IMAGE_MAISON_ESCALIER_SORTIE].nbrMaxPts = 100;
    images[IMAGE_MAISON_ESCALIER_SORTIE].tolerance = 0;
    images[IMAGE_MAISON_ESCALIER_SORTIE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_SORTIE].cheminNom, "images\\maison_sortie.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_SORTIE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_SORTIE].id = idImage;
    images[IMAGE_MAISON_SORTIE].nbrMaxPts = 100;
    images[IMAGE_MAISON_SORTIE].tolerance = 0;
    images[IMAGE_MAISON_SORTIE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_MAISON_BLE].cheminNom, "images\\maison_ble.bmp");
    if(scrChargeImage(images[IMAGE_MAISON_BLE].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_MAISON_BLE].id = idImage;
    images[IMAGE_MAISON_BLE].nbrMaxPts = 100;
    images[IMAGE_MAISON_BLE].tolerance = 0;
    images[IMAGE_MAISON_BLE].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_BOUTON_SUCCES].cheminNom, "images\\bouton_succes.bmp");
    if(scrChargeImage(images[IMAGE_BOUTON_SUCCES].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_BOUTON_SUCCES].id = idImage;
    images[IMAGE_BOUTON_SUCCES].nbrMaxPts = 100;
    images[IMAGE_BOUTON_SUCCES].tolerance = 0;
    images[IMAGE_BOUTON_SUCCES].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_BOUTON_ACCEPTER_SUCCES].cheminNom, "images\\bouton_accepter_succes.bmp");
    if(scrChargeImage(images[IMAGE_BOUTON_ACCEPTER_SUCCES].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_BOUTON_ACCEPTER_SUCCES].id = idImage;
    images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrMaxPts = 100;
    images[IMAGE_BOUTON_ACCEPTER_SUCCES].tolerance = 0;
    images[IMAGE_BOUTON_ACCEPTER_SUCCES].nbrPixelsFaux = 0;

//-------------------------------------------------------------------------------------------------------------


    strcpy(images[IMAGE_OK_CONNEXION].cheminNom, "images\\ok_connexion.bmp");
    if(scrChargeImage(images[IMAGE_OK_CONNEXION].cheminNom, &idImage) != scrOK)
        afficherErreur();

    images[IMAGE_OK_CONNEXION].id = idImage;
    images[IMAGE_OK_CONNEXION].nbrMaxPts = 100;
    images[IMAGE_OK_CONNEXION].tolerance = 0;
    images[IMAGE_OK_CONNEXION].nbrPixelsFaux = 0;

}
