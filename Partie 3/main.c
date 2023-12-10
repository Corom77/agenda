#include "Fonctionp3.h"

int main() {
    // Message d'accueil de l'application
    printf("\n\nPARTIE 3\n\n");
    
    // Création de la liste principale pour l'agenda
    MultiLevelNode* agenda = InitialiserListe();

    // Chargement des données initiales
    ImporterDonneesInterlocuteurs(agenda, "liste_noms.txt", "liste_prenoms.txt");

    // Interface utilisateur principale
    int actif = 1;
    int selection;

    while (actif) {


        printf("1. Chercher un interlocuteur\n");
        printf("2. Voir les rendez-vous d'un interlocuteur\n");
        printf("3. Créer un nouvel interlocuteur\n");
        printf("4. Programmer un rendez-vous\n");
        printf("5. Annuler un rendez-vous\n");
        printf("6. Enregistrer les rendez-vous\n");
        printf("7. Importer des rendez-vous\n");
        printf("8. Fermer l'application\n");
        printf("Entrez votre choix : ");
        
        scanf("%d", &selection);

        switch (selection) {
            case 1:
                ProcedureRechercheInterlocuteur(agenda);
                break;
            case 2:
                AfficherAppointmentsInterlocuteur(agenda);
                break;
            case 3:
                ProcedureAjoutInterlocuteur(agenda);
                break;
            case 4:
                ProcedurePlanificationAppointment(agenda);
                break;
            case 5:
                ProcedureEffacementAppointment(agenda);
                break;
            case 6:
                EnregistrerAppointmentsDansFichier("agenda_enregistre.txt", agenda);
                break;
            case 7:
                ProcedureChargementAppointments(agenda);
                break;
            case 8:
                printf("Fermeture de l'application de gestion d'agenda.\n");
                actif = 0;
                break;
            default:
                printf("Option non reconnue, veuillez essayer à nouveau.\n");
                break;
        }
    }
    
    // Nettoyage et libération de la mémoire
    LibererListe(agenda);

    return 0;
}
