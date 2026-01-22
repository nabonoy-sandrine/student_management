// définit la structure Etudiant et déclare les fonctions de gestion des étudiants.

#ifndef ETUDIANT_H
#define ETUDIANT_H

#include <stdio.h>

#define MAX 100

/* STRUCTURES  */

typedef struct
{
    int jour;
    int mois;
    int annee;
} Date;

typedef struct
{
    char matricule[15];
    char nom[30];
    char prenom[30];
    Date date_naissance;
    char sexe;
    char departement[30];
    char filiere[30];
    char region_origine[30];
} Gestion_des_Etudians;

/* ========= PROTOTYPES ========= */

void menu();

void ajouter_etudiant(Gestion_des_Etudians tab[], int *n);
void modifier_etudiant(Gestion_des_Etudians tab[], int n);
void supprimer_etudiant(Gestion_des_Etudians tab[], int *n);
void afficher_etudiants(Gestion_des_Etudians tab[], int n);
void trier_par_nom(Gestion_des_Etudians tab[], int n);
void trier_par_filiere(Gestion_des_Etudians tab[], int n);
void pause_console();
int rechercher_etudiant(Gestion_des_Etudians tab[], int n, char mat[]);
int calculer_age(Gestion_des_Etudians e);
void menu_modification();
int date_valide(int jour, int mois, int annee);


#endif
