#include "bot.h"


void connexion(int numFen)
{
    Sleep(100);
    scrSourisDeplace(fenetres[numFen].idFenetre,FALSE, 130, 73);
    Sleep(100);
    scrSourisClique(1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique(1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(20);
    scrSourisClique(1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique(1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(20);
    scrSourisClique(1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique(1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(20);

    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, personnages[numFen].pseudo);
    Sleep(50);
    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\t");
    Sleep(500);

    scrSourisDeplace(fenetres[numFen].idFenetre,FALSE,130, 83);
    Sleep(100);
    scrSourisClique(1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    scrSourisClique(1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
    Sleep(50);

    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, personnages[numFen].code);
    Sleep(50);
    scrClavierEnvoiCaracteres(fenetres[numFen].idFenetre, "\r");

   // ajouterTache(7200000, DECONNEXION, numFen);
    ajouterTache(1000, VERIFICATION_FILE_ATTENTE, numFen);

    scrTempsMs(&temps);
    fenetres[numFen].personnage.heureConnexion = temps;
}

void attenteConnexionPersonnage(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,221,176, images[IMAGE_PETIT_IGNORE].id  , images[IMAGE_PETIT_IGNORE].rect  , images[IMAGE_PETIT_IGNORE].nbrMaxPts  , &images[IMAGE_PETIT_IGNORE].nbrTrouvees, images[IMAGE_PETIT_IGNORE].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_PETIT_IGNORE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_PETIT_IGNORE].rect[0].left,images[IMAGE_PETIT_IGNORE].rect[0].right), aleatoire(images[IMAGE_PETIT_IGNORE].rect[0].top,images[IMAGE_PETIT_IGNORE].rect[0].bottom));
            Sleep(20);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(20);
        }
    }
    else
        afficherErreur();

    Sleep(200);

    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,221,176, images[IMAGE_OK_CONNEXION].id  , images[IMAGE_OK_CONNEXION].rect  , images[IMAGE_OK_CONNEXION].nbrMaxPts  , &images[IMAGE_OK_CONNEXION].nbrTrouvees, images[IMAGE_OK_CONNEXION].nbrPixelsFaux  )) == scrOK)
    {
        if(images[IMAGE_OK_CONNEXION].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_OK_CONNEXION].rect[0].left,images[IMAGE_OK_CONNEXION].rect[0].right), aleatoire(images[IMAGE_OK_CONNEXION].rect[0].top,images[IMAGE_OK_CONNEXION].rect[0].bottom));
            Sleep(20);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(20);
        }
    }
    else
        afficherErreur();

    Sleep(200);


    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,172,5,4, images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].id  , images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].rect  , images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrMaxPts  , &images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrTrouvees, images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_ETOILE_CHAT_X_MAX_10_Y_MIN_160].nbrTrouvees > 0)
            ajouterTache(1000, INITIALISATION_PERSONNAGE, numFen);
        else
            ajouterTache(1000, ATTENTE_PERSONNAGE_CONNECTE, numFen);
    }
    else
        afficherErreur();
}

void verificationEtatApresFileAttenteServeur(int numFen)
{
    do{
        if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_PAS_MAINTENANT_CADEAU].id  , images[IMAGE_PAS_MAINTENANT_CADEAU].rect  , images[IMAGE_PAS_MAINTENANT_CADEAU].nbrMaxPts  , &images[IMAGE_PAS_MAINTENANT_CADEAU].nbrTrouvees, images[IMAGE_PAS_MAINTENANT_CADEAU].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_PAS_MAINTENANT_CADEAU].nbrTrouvees > 0)
            {
                scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_PAS_MAINTENANT_CADEAU].rect[0].left,images[IMAGE_PAS_MAINTENANT_CADEAU].rect[0].right), aleatoire(images[IMAGE_PAS_MAINTENANT_CADEAU].rect[0].top,images[IMAGE_PAS_MAINTENANT_CADEAU].rect[0].bottom));
                Sleep(20);
                scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
                Sleep(50);
            }
        }
        else
            afficherErreur();

    }while(images[IMAGE_PAS_MAINTENANT_CADEAU].nbrTrouvees > 0);

    if((err = scrTrouveImage(fenetres[numFen].idFenetre,92,149,30,6, images[IMAGE_JOUER_SELECTON_PERSONNAGE].id  , images[IMAGE_JOUER_SELECTON_PERSONNAGE].rect  , images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrMaxPts  , &images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrTrouvees, images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_JOUER_SELECTON_PERSONNAGE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_JOUER_SELECTON_PERSONNAGE].rect[0].left,images[IMAGE_JOUER_SELECTON_PERSONNAGE].rect[0].right), aleatoire(images[IMAGE_JOUER_SELECTON_PERSONNAGE].rect[0].top,images[IMAGE_JOUER_SELECTON_PERSONNAGE].rect[0].bottom));
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(20);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            ajouterTache(1000, ATTENTE_PERSONNAGE_CONNECTE, numFen);
            return;
        }
        else
        {
            if(combatOuNon(numFen) == TRUE)
            {
                combat(numFen);
            }
            else
            {
                if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_DOFUS].id  , images[IMAGE_DOFUS].rect  , images[IMAGE_DOFUS].nbrMaxPts  , &images[IMAGE_DOFUS].nbrTrouvees, images[IMAGE_DOFUS].nbrPixelsFaux )) == scrOK)
                {
                    if(images[IMAGE_DOFUS].nbrTrouvees > 0)
                        ajouterTache(1000, VERIFICATION_ETAT_APRES_FILE_ATTENTE_SERVEUR, numFen);
                    else
                    {
                        printf("Cas non gere, nous ne sommes pas a la selection du personnage.");
                        testCasNonGeresMaisMaintenantOui(numFen);
                    }
                }
                else
                    afficherErreur();
            }
        }
    }
}

void enleverFenetreNoUpdater(int numFen)
{
    scrTempsMs(&temps);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_NO_UPDATER].id, images[IMAGE_NO_UPDATER].rect, images[IMAGE_NO_UPDATER].nbrMaxPts, &images[IMAGE_NO_UPDATER].nbrTrouvees, images[IMAGE_JOUER].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_NO_UPDATER].nbrTrouvees > 0)
        {
           logInfo("Image de la fenetre no updater trouvee, x:%ld, y:%ld, temps : %u\n", images[IMAGE_NO_UPDATER].rect[0].left, images[IMAGE_NO_UPDATER].rect[0].top, temps);
           Sleep(100);
           scrSourisDeplace(fenetres[numFen].idFenetre,FALSE, 111, 99);
           Sleep(100);
           scrSourisClique(1, TRUE, FALSE, FALSE, FALSE);
           scrSourisClique(1, FALSE, FALSE, FALSE, FALSE);
           ajouterTache(1000, TEST_CONNEXION_MENU, numFen);

        }
        else
        {
            logWarning("Message de l'updater non trouve : %u\n", temps);
            ajouterTache(1000, ENLEVER_NO_UPDATER, numFen);
        }
    }
    else
        afficherErreur();
}

int ouvrirDofus(void)
{
    int res;

    if((err = scrLanceProgramme(cheminDofus, &res)) != scrOK)
        afficherErreur();

    idFenetre[taches[0].numFenetre] = res;

    ajouterTache(1000, ENLEVER_NO_UPDATER, taches[0].numFenetre);

    return res;

}

void lireIdentifiants(void)
{
    FILE *fichier;
    char ligne[200], *p;
    fichier = fopen("identifiants.txt","rb");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier identifiants.txt\n");
        exit(1);
    }
    nbrPersonnages = 0;
    do{
        fgets(ligne,200,fichier);
        while(ligne[strlen(ligne)-1] == 10 || ligne[strlen(ligne)-1] == 13)
            ligne[strlen(ligne)-1] = '\0';

        p = ligne;
        while(*p != ' ')
            p++;
        *p = '\0';

        strcpy(personnages[nbrPersonnages].pseudo, ligne);
        strcpy(personnages[nbrPersonnages].code, p+1);
        personnages[nbrPersonnages].imageCellule.imagePosition = NULL;
        personnages[nbrPersonnages].connecte = 0;
        personnages[nbrPersonnages].enCombat = 0;
        nbrPersonnages++;
    }while(strcmp(personnages[nbrPersonnages-1].pseudo,"CEST") != 0);
    nbrPersonnages--;
    fclose(fichier);
}

void lireCheminDAcces(void)
{
    FILE *fichier;
    char *p;
    fichier = fopen("cheminsdacces.txt","rb");
    if(fichier == NULL)
    {
        printf("Impossible d'ouvrir le fichier cheminsdacces.txt\n");
        exit(1);
    }
    fgets(cheminDofus,199,fichier);
    fgets(cheminLauncher,199,fichier);

    p = cheminDofus;
    while(*p != '\r')
        p++;
    *p = '\0';

    p = cheminLauncher;
    while(*p != '\r')
        p++;
    *p = '\0';

    printf("Chemin de dofus : <%s>\n", cheminDofus);
    printf("Chemin du launcher : <%s>\n", cheminLauncher);

    fclose(fichier);
}

void verficationFileAttenteServeur(int numFen)
{
    int trouvee;

    trouvee = FALSE;
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,91,126,40,10, images[IMAGE_SELECTONNER_FILE_ATTENTE].id  , images[IMAGE_SELECTONNER_FILE_ATTENTE].rect  , images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrMaxPts  , &images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrTrouvees, images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_SELECTONNER_FILE_ATTENTE].nbrTrouvees > 0)
            trouvee = TRUE;

        if((err = scrTrouveImage(fenetres[numFen].idFenetre,91,126,40,10, images[IMAGE_SELECTIONNER_CHARGEMENT].id, images[IMAGE_SELECTIONNER_CHARGEMENT].rect, images[IMAGE_SELECTIONNER_CHARGEMENT].nbrMaxPts, &images[IMAGE_SELECTIONNER_CHARGEMENT].nbrTrouvees, images[IMAGE_SELECTIONNER_CHARGEMENT].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_SELECTIONNER_CHARGEMENT].nbrTrouvees > 0)
                trouvee = TRUE;
        }
        else
            afficherErreur();
    }
    else
        afficherErreur();


    if(trouvee)
        ajouterTache(1000, VERIFICATION_FILE_ATTENTE_SERVEUR, numFen);
    else
        ajouterTache(1000, VERIFICATION_ETAT_APRES_FILE_ATTENTE_SERVEUR, numFen);

}

void testPossibiliteConnexionMenu(int numFen)
{
    scrTempsMs(&temps);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_JOUER].id, images[IMAGE_JOUER].rect, images[IMAGE_JOUER].nbrMaxPts, &images[IMAGE_JOUER].nbrTrouvees, images[IMAGE_JOUER].nbrPixelsFaux)) == scrOK)
    {
        if(images[IMAGE_JOUER].nbrTrouvees > 0)
           {
            logInfo("Menu de connection trouvé, x:%ld, y:%ld, temps : %u", images[IMAGE_JOUER].rect[0].left, images[IMAGE_JOUER].rect[0].top, temps);
            ajouterTache(1000, CONNEXION, numFen);
           }
        else
        {
            logWarning("%u, pas trouvee\n", temps);
            ajouterTache(1000, TEST_CONNEXION_MENU, numFen);
        }
    }
    else
        afficherErreur();
}

void connexionServeur(int numFen)
{
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,24,88,7,30, images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].id, images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].rect, images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrMaxPts, &images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrTrouvees, images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].rect[0].left,images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].rect[0].right), aleatoire(images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].rect[0].top,images[IMAGE_SERVEUR_AGRIDE_ACCESSIBLE].rect[0].bottom));

            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit

            ajouterTache(1000, VERIFICATION_FILE_ATTENTE_SERVEUR, numFen);
            return;
        }
    }
    else
        afficherErreur();
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,24,88,7,30, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].id, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].rect, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrMaxPts, &images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrTrouvees, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].rect[0].left,images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].rect[0].right), aleatoire(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].rect[0].top,images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE].rect[0].bottom));
            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            ajouterTache(60000, CONNEXION_SERVEUR, numFen);
            return;
        }
    }
    else
        afficherErreur();
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,24,88,7,30, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].id, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].rect, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrMaxPts, &images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrTrouvees, images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].nbrTrouvees > 0)
        {
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].rect[0].left,images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].rect[0].right), aleatoire(images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].rect[0].top,images[IMAGE_SERVEUR_AGRIDE_MAINTENANCE_CHARGEMENT].rect[0].bottom));
            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            Sleep(40);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            ajouterTache(60000, CONNEXION_SERVEUR, numFen);
            return;
        }
    }
    else
        afficherErreur();

    testCasNonGeresMaisMaintenantOui(numFen);
}

void ouvrirLaucnher(void)
{
    int res;
    if((err = scrLanceProgramme(cheminLauncher, &res)) != scrOK)
    {
        fprintf(stderr,"Impossible d'ouvrir le Launcher \n\n");
        exit(1);
    }
}

void verificationFileAttente(int numFen)
{
    int trouvee = FALSE;
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,89,100,40,20, images[IMAGE_JOUER_CHARGEMENT].id  , images[IMAGE_JOUER_CHARGEMENT].rect  , images[IMAGE_JOUER_CHARGEMENT].nbrMaxPts  , &images[IMAGE_JOUER_CHARGEMENT].nbrTrouvees, images[IMAGE_JOUER_CHARGEMENT].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_JOUER_CHARGEMENT].nbrTrouvees > 0)
            trouvee = TRUE;

        if((err = scrTrouveImage(fenetres[numFen].idFenetre,89,100,40,20, images[IMAGE_JOUER_FILE_ATTENTE].id, images[IMAGE_JOUER_FILE_ATTENTE].rect, images[IMAGE_JOUER_FILE_ATTENTE].nbrMaxPts, &images[IMAGE_JOUER_FILE_ATTENTE].nbrTrouvees, images[IMAGE_JOUER_FILE_ATTENTE].nbrPixelsFaux )) == scrOK)
        {
            if(images[IMAGE_JOUER_FILE_ATTENTE].nbrTrouvees > 0)
                trouvee = TRUE;

        }
        else
            afficherErreur();
    }
    else
        afficherErreur();


    if(trouvee)
        ajouterTache(1000, VERIFICATION_FILE_ATTENTE, numFen);
    else
        ajouterTache(1000, VERIFICATION_ETAT_APRES_FILE_ATTENTE, numFen);


}

void verificationEtatApresFileAttente(int numFen)
{

    if((err = scrTrouveImage(fenetres[numFen].idFenetre,91,126,40,10, images[IMAGE_LISTE_SERVEURS].id, images[IMAGE_LISTE_SERVEURS].rect, images[IMAGE_LISTE_SERVEURS].nbrMaxPts, &images[IMAGE_LISTE_SERVEURS].nbrTrouvees, images[IMAGE_LISTE_SERVEURS].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_LISTE_SERVEURS].nbrTrouvees > 0)
        {
            printf("Connexion serveur\n");
            ajouterTache(1000, CONNEXION_SERVEUR, numFen);
            return;
        }
    }
    else
        afficherErreur();
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,70,60,90,60, images[IMAGE_SERVEUR_INACCESSIBLE].id, images[IMAGE_SERVEUR_INACCESSIBLE].rect, images[IMAGE_SERVEUR_INACCESSIBLE].nbrMaxPts, &images[IMAGE_SERVEUR_INACCESSIBLE].nbrTrouvees, images[IMAGE_SERVEUR_INACCESSIBLE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_SERVEUR_INACCESSIBLE].nbrTrouvees > 0)
        {
            printf("Serveur inaccessible\n");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_SERVEUR_INACCESSIBLE].rect[0].left,images[IMAGE_SERVEUR_INACCESSIBLE].rect[0].right), aleatoire(images[IMAGE_SERVEUR_INACCESSIBLE].rect[0].top,images[IMAGE_SERVEUR_INACCESSIBLE].rect[0].bottom));
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit

            ajouterTache(1000, TEST_CONNEXION_MENU, numFen);
            return;
        }
    }
    else
        afficherErreur();
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,70,60,90,60, images[IMAGE_ERREUR_CONNEXION_MENU].id, images[IMAGE_ERREUR_CONNEXION_MENU].rect, images[IMAGE_ERREUR_CONNEXION_MENU].nbrMaxPts, &images[IMAGE_ERREUR_CONNEXION_MENU].nbrTrouvees, images[IMAGE_ERREUR_CONNEXION_MENU].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_ERREUR_CONNEXION_MENU].nbrTrouvees > 0)
        {
            printf("Erreur de connexion\n");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, aleatoire(images[IMAGE_ERREUR_CONNEXION_MENU].rect[0].left,images[IMAGE_ERREUR_CONNEXION_MENU].rect[0].right), aleatoire(images[IMAGE_ERREUR_CONNEXION_MENU].rect[0].top,images[IMAGE_ERREUR_CONNEXION_MENU].rect[0].bottom));
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit

            ajouterTache(1000, TEST_CONNEXION_MENU, numFen);
            return;
        }
    }
    else
        afficherErreur();

    testCasNonGeresMaisMaintenantOui(numFen);

}

void reouvrirFenetre(int numFen)
{
    fenetres[numFen].idFenetre = ouvrirDofus();
    rangerFenetre(numFen);
}

