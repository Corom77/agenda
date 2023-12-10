#ifndef _Fonctionp3_H_
#define _Fonctionp3_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <stdbool.h>


#include "timer.h" 
typedef struct {
    int day;
    int month;
    int year;
    int hours;
    int minutes;
} Moment;





typedef struct Appointment {
    Moment moment;
    int duration;
    char *description;
    struct Appointment* next;   
} Appointment;




typedef struct Interlocuteur {
    char *surname;
    char *firstname;
    char *full_name;
    Appointment *appointmentsList; 
} Interlocuteur;






typedef struct MultiLevelNode {
    Interlocuteur* interlocuteur; 
    struct MultiLevelNode* level[4]; 
} MultiLevelNode;






Interlocuteur* CreerInterlocuteur(const char* nomFamille, const char* prenom);
void ProcedureAjoutInterlocuteur(MultiLevelNode* sommet);
void MontrerInterlocuteur(const Interlocuteur* interlocuteur);
MultiLevelNode* InitialiserListe();
void InsererInterlocuteur(MultiLevelNode* sommet, Interlocuteur* interlocuteur);
void AfficherTousInterlocuteurs(MultiLevelNode* sommet);
void AjouterAppointment(Interlocuteur* interlocuteur, Moment moment, int duree, const char* sujet);
void MontrerAppointment(const Appointment* rdv);
void AfficherTousAppointments(MultiLevelNode* sommet);
void AfficherAppointmentsInterlocuteur(MultiLevelNode* sommet);
int SupprimerAppointment(Appointment **listeAppointments, Moment moment);
void ProcedurePlanificationAppointment(MultiLevelNode* sommet);
void ImporterAppointmentsDepuisFichier(MultiLevelNode* sommet, const char* fichierRDV);
void ImporterDonneesInterlocuteurs(MultiLevelNode* racine, const char* pathNoms, const char* pathPrenoms);
void EnregistrerAppointmentsDansFichier(const char* nomFichierSortie, MultiLevelNode* pointDepart);
void ConvertirEnMinuscule(char* chaine);
int NiveauInsertion(const char* identite);
Moment ConvertirMoment(const char* str);
int ValiderMoment(const char *momentStr);
char* LireChaine();
int ComparerMoments(const Moment *a, const Moment *b);
void LibererListe(MultiLevelNode* sommet);
void ProcedureRechercheInterlocuteur(MultiLevelNode* sommet);
Interlocuteur* RechercherInterlocuteur(MultiLevelNode* sommet, const char* nomFamille, const char* prenom);
Interlocuteur* TrouverInterlocuteur(MultiLevelNode* racine, const char* nomFamille, const char* prenom);
void ProcedureEffacementAppointment(MultiLevelNode* sommet);
void ProcedureChargementAppointments(MultiLevelNode* sommet);



#endif // _Fonctionp3_H_
