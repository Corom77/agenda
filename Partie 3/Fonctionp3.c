#include "Fonctionp3.h"

// Procédure d'importation des rendez-vous depuis un fichier externe
void ImporterAppointmentsDepuisFichier(MultiLevelNode* sommet, const char* fichierRDV) {
    FILE* fichierAppointments = fopen(fichierRDV, "r");
    if (!fichierAppointments) {
        fprintf(stderr, "Problème à l'ouverture de %s.\n", fichierRDV);
        return;
    }

    char nomFamille[100], prenomPersonne[100], sujet[100];
    int jourRdv, moisRdv, anneeRdv, heureRdv, minRdv, dureeRdv;
    while (fscanf(fichierAppointments, "%99s %99s %d-%d-%d %d:%d %d %[^\n]", nomFamille, prenomPersonne, &jourRdv, &moisRdv, &anneeRdv, &heureRdv, &minRdv, &dureeRdv, sujet) == 9) {
        char identiteComplete[200];
        sprintf(identiteComplete, "%s_%s", nomFamille, prenomPersonne);
        ConvertirEnMinuscule(identiteComplete);

        Interlocuteur* personne = RechercherInterlocuteur(sommet, nomFamille, prenomPersonne);
        if (!personne) {
            personne = CreerInterlocuteur(nomFamille, prenomPersonne);
            InsererInterlocuteur(sommet, personne);
        }

        Moment dateRdv = {jourRdv, moisRdv, anneeRdv, heureRdv, minRdv};
        AjouterAppointment(personne, dateRdv, dureeRdv, sujet);
    }

    fclose(fichierAppointments);
}




// Chargement des données des interlocuteurs depuis des fichiers spécifiés
void ImporterDonneesInterlocuteurs(MultiLevelNode* racine, const char* pathNoms, const char* pathPrenoms) {
    FILE *fichierN = fopen(pathNoms, "r");
    if (!fichierN) {
        fprintf(stderr, "Echec lors de l'ouverture du fichier des noms.\n");
        return;
    }

    FILE *fichierP = fopen(pathPrenoms, "r");
    if (!fichierP) {
        fprintf(stderr, "Echec lors de l'ouverture du fichier des prénoms.\n");
        fclose(fichierN);
        return;
    }

    char nomIndividu[100];
    char prenomIndividu[100];
    while (fscanf(fichierN, "%99s", nomIndividu) != EOF && fscanf(fichierP, "%99s", prenomIndividu) != EOF) {
        Interlocuteur* nouveauInterlocuteur = CreerInterlocuteur(nomIndividu, prenomIndividu);
        InsererInterlocuteur(racine, nouveauInterlocuteur);
    }

    fclose(fichierN);
    fclose(fichierP);
}






// Enregistrement des rendez-vous dans un fichier de sortie
void EnregistrerAppointmentsDansFichier(const char* nomFichierSortie, MultiLevelNode* pointDepart) {
    FILE *fichierSortie = fopen(nomFichierSortie, "w");
    if (!fichierSortie) {
        fprintf(stderr, "Erreur lors de l'ouverture de %s pour l'enregistrement.\n", nomFichierSortie);
        return;
    }

    MultiLevelNode* noeudActuel = pointDepart->level[0];
    while (noeudActuel) {
        Interlocuteur *individu = noeudActuel->interlocuteur;
        Appointment *rdvActuel = individu->appointmentsList;
        while (rdvActuel) {
            fprintf(fichierSortie, "%s %s %02d-%02d-%04d %02d:%02d %d %s\n", individu->surname, individu->firstname, rdvActuel->moment.day, rdvActuel->moment.month, rdvActuel->moment.year, rdvActuel->moment.hours, rdvActuel->moment.minutes, rdvActuel->duration, rdvActuel->description);
            rdvActuel = rdvActuel->next;
        }
        noeudActuel = noeudActuel->level[0];
    }

    fclose(fichierSortie);
}



Interlocuteur *CreerInterlocuteur(const char *nomFamille, const char *prenom) {
    Interlocuteur *interlocuteur = malloc(sizeof(Interlocuteur));
    if (!interlocuteur) return NULL;

    interlocuteur->surname = strdup(nomFamille);
    interlocuteur->firstname = strdup(prenom);

    // Assemblage et normalisation du nom complet
    char nomComplet[200];
    sprintf(nomComplet, "%s_%s", nomFamille, prenom);
    ConvertirEnMinuscule(nomComplet);
    interlocuteur->full_name = strdup(nomComplet);

    if (!interlocuteur->surname || !interlocuteur->firstname || !interlocuteur->full_name) {
        free(interlocuteur->surname); free(interlocuteur->firstname); free(interlocuteur->full_name); free(interlocuteur);
        return NULL;
    }

    return interlocuteur;
}


void AfficherTousInterlocuteurs(MultiLevelNode* racine) {
    MultiLevelNode* actuel = racine->level[0];
    while (actuel) {
        MontrerInterlocuteur(actuel->interlocuteur);
        actuel = actuel->level[0];
    }
}


void ProcedureAjoutInterlocuteur(MultiLevelNode* sommet) {
    printf("Entrez le nom de l'interlocuteur: ");
    char* nom = LireChaine();
    printf("Entrez le prénom de l'interlocuteur: ");
    char* prenom = LireChaine();
    Interlocuteur* interlocuteur = CreerInterlocuteur(nom, prenom);
    InsererInterlocuteur(sommet, interlocuteur);
}


void MontrerInterlocuteur(const Interlocuteur* interlocuteur) {
    if (!interlocuteur) {
        printf("Aucun interlocuteur trouvé.\n");
        return;
    }
    printf("Interlocuteur : %s %s\n", interlocuteur->surname, interlocuteur->firstname);
}

MultiLevelNode* InitialiserListe() {
    MultiLevelNode* racine = malloc(sizeof(MultiLevelNode));
    racine->interlocuteur = NULL;
    for (int i = 0; i < 4; ++i) {
        racine->level[i] = NULL;
    }
    return racine;
}


void InsererInterlocuteur(MultiLevelNode *racine, Interlocuteur *interlocuteur) {
    int niveau = NiveauInsertion(interlocuteur->full_name);
    MultiLevelNode *miseAJour[4] = {NULL};

    MultiLevelNode *actuel = racine;
    for (int i = 3; i >= 0; --i) {
        while (actuel->level[i] != NULL && strcmp(interlocuteur->full_name, actuel->level[i]->interlocuteur->full_name) > 0) {
            actuel = actuel->level[i];
        }
        if (i <= niveau) miseAJour[i] = actuel;
    }

    MultiLevelNode *nouveauNoeud = malloc(sizeof(MultiLevelNode));
    nouveauNoeud->interlocuteur = interlocuteur;
    for (int i = 0; i <= niveau; ++i) {
        nouveauNoeud->level[i] = miseAJour[i]->level[i];
        miseAJour[i]->level[i] = nouveauNoeud;
    }
}




void ConvertirEnMinuscule(char* chaine) {
    for (int i = 0; chaine[i]; i++) {
        chaine[i] = tolower(chaine[i]);
    }
}



int NiveauInsertion(const char* identite) {
    int longueur = strlen(identite);
    if (longueur < 3) return 0;

    if (identite[0] != identite[1]) return 3;
    else if (identite[1] != identite[2]) return 2;
    else if (longueur >= 3 && identite[2] != identite[3]) return 1;
    else return 0;
}




// Comparer deux moments
int ComparerMoments(const Moment *a, const Moment *b) {
    if (a->year != b->year) return a->year - b->year;
    if (a->month != b->month) return a->month - b->month;
    if (a->day != b->day) return a->day - b->day;
    if (a->hours != b->hours) return a->hours - b->hours;
    return a->minutes - b->minutes;
}




// Procédure pour planifier un nouveau rendez-vous
void ProcedurePlanificationAppointment(MultiLevelNode* sommet) {
    char nom[100], prenom[100];
    printf("Nom de l'interlocuteur : ");
    scanf("%99s", nom);
    printf("Prénom de l'interlocuteur : ");
    scanf("%99s", prenom);

    char identiteComplete[200];
    sprintf(identiteComplete, "%s_%s", nom, prenom);
    ConvertirEnMinuscule(identiteComplete);

    Interlocuteur* interlocuteur = RechercherInterlocuteur(sommet, nom, prenom);
    if (!interlocuteur) {
        printf("Interlocuteur non trouvé.\n");
        return;
    }

    printf("Date et heure du rendez-vous (AAAA-MM-JJ HH:MM) : ");
    char momentStr[20];
    scanf(" %19[^\n]", momentStr);
    Moment moment = ConvertirMoment(momentStr);

    printf("Durée du rendez-vous (minutes) : ");
    int duree;
    scanf("%d", &duree);

    printf("Sujet du rendez-vous : ");
    char sujet[100];
    scanf(" %99[^\n]", sujet);

    AjouterAppointment(interlocuteur, moment, duree, sujet);
}





// Vérifie la validité d'un moment
int ValiderMoment(const char *momentStr) {
    int jour, mois, annee, heure, minute;
    if (sscanf(momentStr, "%d-%d-%d %d:%d", &annee, &mois, &jour, &heure, &minute) != 5) {
        return 0;
    }
    if (jour < 1 || jour > 31 || mois < 1 || mois > 12 || annee < 0 || heure < 0 || heure > 23 || minute < 0 || minute > 59) {
        return 0;
    }
    return 1;
}



// Convertit une chaîne en Moment
Moment ConvertirMoment(const char* str) {
    Moment m;
    sscanf(str, "%d-%d-%d %d:%d", &m.year, &m.month, &m.day, &m.hours, &m.minutes);
    return m;
}



// Ajouter un nouveau rendez-vous
void AjouterAppointment(Interlocuteur *interlocuteur, Moment moment, int duree, const char* sujet) {
    if (!interlocuteur) {
        fprintf(stderr, "Interlocuteur non spécifié.\n");
        return;
    }

    Appointment *nouveauRdv = malloc(sizeof(Appointment));
    if (!nouveauRdv) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nouveau rendez-vous.\n");
        return;
    }

    nouveauRdv->moment = moment;
    nouveauRdv->duration = duree;
    nouveauRdv->description = strdup(sujet);
    nouveauRdv->next = NULL;

    if (!interlocuteur->appointmentsList || ComparerMoments(&moment, &interlocuteur->appointmentsList->moment) < 0) {
        nouveauRdv->next = interlocuteur->appointmentsList;
        interlocuteur->appointmentsList = nouveauRdv;
    } else {
        Appointment *actuel = interlocuteur->appointmentsList;
        while (actuel->next && ComparerMoments(&moment, &actuel->next->moment) > 0) {
            actuel = actuel->next;
        }
        nouveauRdv->next = actuel->next;
        actuel->next = nouveauRdv;
    }
}


// Montrer les détails d'un rendez-vous
void MontrerAppointment(const Appointment *rdv) {
    if (!rdv) {
        printf("Aucun rendez-vous à montrer.\n");
        return;
    }

    printf("Date : %02d-%02d-%04d\n", rdv->moment.day, rdv->moment.month, rdv->moment.year);
    printf("Heure : %02d:%02d\n", rdv->moment.hours, rdv->moment.minutes);
    printf("Durée : %d minutes\n", rdv->duration);
    printf("Sujet : %s\n\n", rdv->description);
}


// Afficher les rendez-vous d'un Interlocuteur
void AfficherAppointmentsInterlocuteur(MultiLevelNode* sommet) {
    char nomFamille[100], prenom[100];
    printf("Nom de l'interlocuteur : ");
    scanf("%99s", nomFamille);
    printf("Prénom de l'interlocuteur : ");
    scanf("%99s", prenom);

    char identiteComplete[200];
    sprintf(identiteComplete, "%s_%s", nomFamille, prenom);
    ConvertirEnMinuscule(identiteComplete);

    Interlocuteur* interlocuteur = RechercherInterlocuteur(sommet, nomFamille, prenom);
    if (interlocuteur) {
        printf("Rendez-vous de %s %s :\n", interlocuteur->surname, interlocuteur->firstname);
        Appointment* rdv = interlocuteur->appointmentsList;
        while (rdv) {
            MontrerAppointment(rdv);
            rdv = rdv->next;
        }
    } else {
        printf("Interlocuteur non trouvé.\n");
    }
}


// Afficher tous les rendez-vous
void AfficherTousAppointments(MultiLevelNode* racine) {
    MultiLevelNode* courant = racine->level[0];
    while (courant) {
        Interlocuteur* interlocuteur = courant->interlocuteur;
        printf("Rendez-vous de %s %s :\n", interlocuteur->surname, interlocuteur->firstname);
        Appointment* rdv = interlocuteur->appointmentsList;
        if (!rdv) {
            printf("  Aucun rendez-vous pour cet interlocuteur.\n");
        } else {
            while (rdv) {
                MontrerAppointment(rdv);
                rdv = rdv->next;
            }
        }
        courant = courant->level[0];
    }
}



// Supprimer un rendez-vous spécifique
int SupprimerAppointment(Appointment **listeAppointments, Moment moment) {
    Appointment *courant = *listeAppointments;
    Appointment *precedent = NULL;

    while (courant) {
        if (ComparerMoments(&courant->moment, &moment) == 0) {
            if (!precedent) {
                *listeAppointments = courant->next;
            } else {
                precedent->next = courant->next;
            }

            free(courant);
            return 1; // Suppression réussie
        }

        precedent = courant;
        courant = courant->next;
    }
    return 0; // Rendez-vous introuvable
}





Interlocuteur* RechercherInterlocuteur(MultiLevelNode* racine, const char* nomFamille, const char* prenom) {
    MultiLevelNode* actuel = racine->level[0];
    while (actuel) {
        if (strcmp(actuel->interlocuteur->surname, nomFamille) == 0 && strcmp(actuel->interlocuteur->firstname, prenom) == 0) {
            return actuel->interlocuteur;
        }
        actuel = actuel->level[0];
    }
    return NULL;
}




Interlocuteur* TrouverInterlocuteur(MultiLevelNode* racine, const char* nomFamille, const char* prenom) {
    MultiLevelNode* actuel = racine->level[0];
    while (actuel) {
        if (strcmp(actuel->interlocuteur->surname, nomFamille) == 0 && strcmp(actuel->interlocuteur->firstname, prenom) == 0) {
            return actuel->interlocuteur;
        }
        actuel = actuel->level[0];
    }
    return NULL;
}




void ProcedureRechercheInterlocuteur(MultiLevelNode* sommet) {
    printf("Nom de l'interlocuteur : ");
    char *nom = LireChaine();
    printf("Prénom de l'interlocuteur : ");
    char *prenom = LireChaine();

    Interlocuteur* interlocuteur = TrouverInterlocuteur(sommet, nom, prenom);

    if (interlocuteur) {
        MontrerInterlocuteur(interlocuteur);
    } else {
        printf("Interlocuteur non trouvé.\n");
    }

    free(nom);
    free(prenom);
}


void ProcedureChargementAppointments(MultiLevelNode* racine) {
    char fichierNom[100];
    printf("Nom du fichier à charger : ");
    scanf("%99s", fichierNom);
    ImporterAppointmentsDepuisFichier(racine, fichierNom);
}




char* LireChaine() {
    char* chaine = malloc(sizeof(char) * 100);
    scanf("%99s", chaine);
    return chaine;
}


void ProcedureEffacementAppointment(MultiLevelNode* sommet) {
    printf("Saisir le nom de l'interlocuteur : ");
    char nomFamille[100];
    scanf("%99s", nomFamille);
    printf("Saisir le prénom de l'interlocuteur : ");
    char prenom[100];
    scanf("%99s", prenom);

    char identiteComplete[200];
    sprintf(identiteComplete, "%s_%s", nomFamille, prenom);
    ConvertirEnMinuscule(identiteComplete);

    Interlocuteur* interlocuteur = RechercherInterlocuteur(sommet, nomFamille, prenom);
    if (!interlocuteur) {
        printf("Interlocuteur introuvable.\n");
    } else {
        printf("Date et heure du rendez-vous à supprimer (AAAA-MM-JJ HH:MM) : ");
        char momentStr[20];
        scanf(" %19[^\n]", momentStr);

        if (!ValiderMoment(momentStr)) {
            fprintf(stderr, "Format de moment invalide.\n");
        } else {
            Moment moment = ConvertirMoment(momentStr);
            if (SupprimerAppointment(&interlocuteur->appointmentsList, moment)) {
                printf("Rendez-vous effacé.\n");
            } else {
                printf("Rendez-vous non trouvé.\n");
            }
        }
    }
}








void LibererListe(MultiLevelNode* racine) {
    if (!racine) return;

    MultiLevelNode* courant = racine->level[0];
    while (courant) {
        MultiLevelNode* noeudTemp = courant;
        courant = courant->level[0];

        Appointment* rdv = noeudTemp->interlocuteur->appointmentsList;
        while (rdv) {
            Appointment* rdvTemp = rdv;
            rdv = rdv->next;
            free(rdvTemp->description);
            free(rdvTemp);
        }

        free(noeudTemp->interlocuteur->surname);
        free(noeudTemp->interlocuteur->firstname);
        free(noeudTemp->interlocuteur->full_name);
        free(noeudTemp->interlocuteur);
        free(noeudTemp);
    }

    free(racine);
}




