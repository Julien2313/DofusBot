#include "bot.h"


void jarterEvenementFenetre(int numFen, int enleverDeconnexion, int enleverCheckList)
{
    int i, first;
    TACHE *p;
    first = TRUE;
    for(p = taches,i = 0; i < nbrTachesPlanifiees; p++,i++)
    {
        if(p->numFenetre == numFen)   // (a && b == c || b != c)
        {
            if(first == FALSE)
            if((enleverDeconnexion == TRUE && p->idTache == DECONNEXION) || p->idTache != DECONNEXION) //On enlève la taches si c'est une déconnexion et qu'on veut les enlever, ou alors si c'est pas une déconnexion
            if((enleverCheckList == TRUE && p->idTache == CHECK_LIST) || p->idTache != CHECK_LIST)
            {
                memcpy(p,p+1,sizeof(TACHE)*(nbrTachesPlanifiees-i-1));
                nbrTachesPlanifiees--; i--;
            }
            if(first == TRUE)
                first = FALSE;
        }
    }
}

void rangerFenetre(int numFen)
{
    scrDeplaceFenetre(fenetres[numFen].idFenetre,numFen * 230, 0, LFenetre, HFenetre);
}

void deconnexion(int numFen)
{
    if(fenetres[numFen].personnage.enCombat == TRUE)
    {
        ajouterTache(7200000, DECONNEXION, numFen);
    }
    else
    {
        fenetres[numFen].personnage.connecte = FALSE;
        scrTempsMs(&temps);
        fenetres[numFen].personnage.heureDeconnexion = temps;
        fermerFenetre(numFen);
        ajouterTache(5000, INITIALISER_FENETRE, numFen);

    }
}

void fermerFenetre(int numFen)
{
    printf("id fenetre : %d, numFen : %d\n",fenetres[numFen].idFenetre, numFen);
    scrClavierEnvoiFonction(fenetres[numFen].idFenetre,4, FALSE, FALSE, TRUE);
}

void appellerFonction(void)
{
    if(nbrTachesPlanifiees != 0)
    {
        switch(taches[0].idTache)
        {
            case INITIALISER_FENETRE:                               initialiserFenetre(taches[0].numFenetre);                           break;
            case TEST_CONNEXION_MENU:                               testPossibiliteConnexionMenu(taches[0].numFenetre);                 break;
            case CONNEXION:                                         connexion(taches[0].numFenetre);                                    break;
            case VERIFICATION_FILE_ATTENTE:                         verificationFileAttente(taches[0].numFenetre);                      break;
            case VERIFICATION_ETAT_APRES_FILE_ATTENTE:              verificationEtatApresFileAttente(taches[0].numFenetre);             break;
            case CONNEXION_SERVEUR:                                 connexionServeur(taches[0].numFenetre);                             break;
            case VERIFICATION_FILE_ATTENTE_SERVEUR:                 verficationFileAttenteServeur(taches[0].numFenetre);                break;
            case VERIFICATION_ETAT_APRES_FILE_ATTENTE_SERVEUR:      verificationEtatApresFileAttenteServeur(taches[0].numFenetre);      break;
            case ATTENTE_PERSONNAGE_CONNECTE:                       attenteConnexionPersonnage(taches[0].numFenetre);                   break;
            case INITIALISATION_PERSONNAGE:                         initialisationPersonnage(taches[0].numFenetre);                     break;
            case ALLEZFAUCHER:                                      allerFaucher(taches[0].numFenetre);                                 break;
            case VERIFICATION_CHANGEMENT_CARTE:                     verificationChangementCarte(taches[0].numFenetre);                  break;
            case COMBAT:                                            combat(taches[0].numFenetre);                                       break;
            case DECONNEXION:                                       deconnexion(taches[0].numFenetre);                                  break;
            case CHECK_LIST:                                        checkList(taches[0].numFenetre);                                    break;
            case VIDER_COFFRE:                                      viderCoffre(taches[0].numFenetre);                                  break;
            case ENLEVER_NO_UPDATER:                                enleverFenetreNoUpdater(taches[0].numFenetre);                      break;
			case CLIC_BLE:									        clicSurBle(taches[0].numFenetre);								    break;
			case ENLEVER_PODS_ETAPE_1:						        enleverPodsEtape1(taches[0].numFenetre);						    break;
			case ENLEVER_PODS_ETAPE_2:								enleverPodsEtape2(taches[0].numFenetre);		    			    break;
			case ENLEVER_PODS_ETAPE_3:						        enleverPodsEtape3(taches[0].numFenetre);						    break;
			case ENLEVER_PODS_ETAPE_4:						        enleverPodsEtape4(taches[0].numFenetre);						    break;
			case ENLEVER_PODS_ETAPE_5:						        enleverPodsEtape5(taches[0].numFenetre);						    break;
            case ALLER_MAISON:                                      allerMaison(taches[0].numFenetre);                                  break;
            case ENTRER_MAISON:                                     entrerMaison(taches[0].numFenetre);                                 break;
            case CLIQUER_ESCALIER:                                  clicEscalier(taches[0].numFenetre);                                 break;
            case CLIQUER_COFFRE:                                    cliquerCoffre(taches[0].numFenetre);                                break;
            case DEPLACER_BLE:                                      deplacerBle(taches[0].numFenetre);                                  break;
            case DESCENDRE_ESCALIER:                                descendreEscalier(taches[0].numFenetre);                            break;
            case QUITTER_MAISON:                                    quitterMaison(taches[0].numFenetre);                                break;
            case FERMER_FENETRE:                                    fermerFenetre(taches[0].numFenetre);                                break;



            default:
                printf("Aucune fonction n'a ete trouve pour la tache a planifier : %d.\n", taches[0].idTache);

                break;
        }

        nbrTachesPlanifiees--;
        memcpy(taches, taches+1, sizeof(TACHE) * nbrTachesPlanifiees);
    }
}

int compare(const void *elem1, const void *elem2)
{
    if ( ((POINTSRECOLTES *)elem1) ->point.y - ((POINTSRECOLTES *)elem2) ->point.y > 10)
      return -1;

    else if( ((POINTSRECOLTES *)elem1) ->point.y - ((POINTSRECOLTES *)elem2) ->point.y < -10)
      return 1;
    else
    {
       if ( ((POINTSRECOLTES *)elem1) ->point.x < ((POINTSRECOLTES *)elem2) ->point.x)
          return -1;
       else
          return 1;
    }
}

long int aleatoire(long int MINI, long int MAXI)
{
    return ((rand() % (MAXI - MINI + 1)) + MINI);
}

void afficherErreur(void)
{
    scrMessageErreur(err, msgErr,LGMSGERR);
    printf("%s\n",msgErr);
    exit(1);
}

void ajouterTache(unsigned int date, int idTache, int numFenetre)
{
    TACHE *pTache;
    scrTempsMs(&temps);
    date = date + temps;
    for(pTache = taches;pTache < taches + nbrTachesPlanifiees; pTache++)
    {
        if(pTache->date > date)
            break;
    }
    memcpy(pTache+1, pTache, sizeof(TACHE)*(taches + nbrTachesPlanifiees - pTache));
    pTache->date = date;
    pTache->idTache = idTache;
    pTache->numFenetre = numFenetre;
    nbrTachesPlanifiees++;
}

void enumererTaches(void)
{
    int i;
    for(i = 0; i < nbrTachesPlanifiees; i++)
        logDebug("Date : %10d, tache a faire : %2d, numero de la fenetre : %2d",  (int)taches[i].date, taches[i].idTache, fenetres[taches[i].numFenetre].idFenetre);
    printf("\n");
}


void trouverTailleFenetreclient(int numFen, int LClient_, int HClient_, int *LFenetre_, int *HFenetre_)
{
    int lBordureHaut, lBordureBas, lBordureGauche, lBordureDroite;
    RECT dimensionsClient, dimensionsFenetre;


    scrRecupDimensionsFenetre(fenetres[numFen].idFenetre, &dimensionsFenetre, &dimensionsClient);

    lBordureHaut = dimensionsClient.top - dimensionsFenetre.top;
    lBordureBas = dimensionsFenetre.bottom - dimensionsClient.bottom;
    lBordureGauche = dimensionsClient.left - dimensionsFenetre.left;
    lBordureDroite = dimensionsFenetre.right - dimensionsClient.right;

    *LFenetre_ = LClient_ + lBordureGauche + lBordureDroite;
    *HFenetre_ = HClient_ + lBordureHaut   + lBordureBas;

}

void testCasNonGeresMaisMaintenantOui(int numFen)
{
    //tester si banni, et tous les autres cas où il faut redémarrer une fenêtre dofus

    jarterEvenementFenetre(numFen, TRUE, TRUE);
    if((err = scrTrouveImage(fenetres[numFen].idFenetre,0,0,LClient,HClient, images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].id, images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].rect, images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrMaxPts, &images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrTrouvees, images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrPixelsFaux )) == scrOK)
    {
        if(images[IMAGE_CONNEXION_SERVEUR_INTERROMPUE].nbrTrouvees > 0 )
        {
            printf("Le personnage a ete deconnecte\n");
            scrSourisDeplace(fenetres[numFen].idFenetre,    FALSE, 111, 99);
            scrSourisClique (1, TRUE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            scrSourisClique (1, FALSE, FALSE, FALSE, FALSE); // bouton=1,2,3 gauche,centre,droit
            return;
        }
    }
    else
        afficherErreur();

    //sinon, on referme la fenêtre et on la reouvre
    fermerFenetre(numFen);
    ajouterTache(1000, INITIALISER_FENETRE, numFen);
    return;
}



void checkList(int numFen)
{
    if(fenetres[numFen].personnage.enCombat == 0)
    {
        combat(numFen);
        checkPods(numFen);
        upPaysant(numFen);
        checkSucces(numFen);
    }
    logDebug("Check de l'êtat du personnage effectué!\n");
    ajouterTache(5000, CHECK_LIST, numFen);
}


