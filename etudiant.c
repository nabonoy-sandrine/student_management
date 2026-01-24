// implémente les fonctions permettant d’ajouter, afficher, rechercher, modifier et supprimer des étudiants.

#include "etudiant.h"
#include <string.h>
#include <time.h>

/* ========= MENU ========= */

void menu()
{
    printf("\n");
    printf("╔════════════════════════════════════════════════════╗\n");
    printf("║                                                    ║\n");
    printf("║            SYSTEME DE GESTION DES ETUDIANTS        ║\n");
    printf("║                                                    ║\n");
    printf("╠════════════════════════════════════════════════════╣\n");
    printf("║  1 - Enregistrer un etudiant                       ║\n");
    printf("║  2 - Modifier un etudiant                          ║\n");
    printf("║  3 - Rechercher un etudiant (dichotomie)           ║\n");
    printf("║  4 - Supprimer un etudiant                         ║\n");
    printf("║  5 - Trier par ordre alphabetique (Nom)            ║\n");
    printf("║  6 - Calculer l'age d'un etudiant                  ║\n");
    printf("║  7 - Trier par filiere                             ║\n");
    printf("║  8 - Afficher la liste des etudiants               ║\n");
    printf("║                                                    ║\n");
    printf("║  0 - Quitter                                       ║\n");
    printf("╚════════════════════════════════════════════════════╝\n");
    printf("Votre choix : ");
}


/* ===== ENREGISTRER PLUSIEURS ETUDIANTS ===== */

void ajouter_etudiant(Gestion_des_Etudians tab[], int *n)
{
    int nb, i, j;
    int existe;

    printf("Combien d'etudiants voulez-vous enregistrer ? ");
    scanf("%d", &nb);

    if (*n + nb > MAX)
    {
        printf("Erreur : nombre maximum d'etudiants depasse.\n");
        return;
    }

    for (i = 0; i < nb; i++)
    {
        printf("\n--- Etudiant %d ---\n", i + 1);

        /* ===== Matricule (UNIQUE) ===== */
        do
        {
            existe = 0;

            printf("Matricule : ");
            scanf("%s", tab[*n].matricule);

            for (j = 0; j < *n; j++)
            {
                if (strcmp(tab[j].matricule, tab[*n].matricule) == 0)
                {
                    existe = 1;
                    printf("Erreur : ce matricule existe deja. Entrez un autre.\n");
                    break;
                }
            }

        } while (existe);
        printf("Nom : ");
        scanf("%s", tab[*n].nom);

        printf("Prenom : ");
        scanf("%s", tab[*n].prenom);

        printf("Date de naissance (JJ MM AAAA) : ");
        scanf("%d %d %d",
              &tab[*n].date_naissance.jour,
              &tab[*n].date_naissance.mois,
              &tab[*n].date_naissance.annee);

        do
        {
            printf("Sexe (M/F) : ");
            scanf(" %c", &tab[*n].sexe);

            if (tab[*n].sexe != 'M' && tab[*n].sexe != 'm' &&
                tab[*n].sexe != 'F' && tab[*n].sexe != 'f')
            {
                printf("Erreur : vous devez entrer M ou F uniquement.\n");
            }

        } while (tab[*n].sexe != 'M' && tab[*n].sexe != 'm' &&
                 tab[*n].sexe != 'F' && tab[*n].sexe != 'f');

        printf("Departement : ");
        scanf("%s", tab[*n].departement);

        printf("Filiere : ");
        scanf("%s", tab[*n].filiere);

        printf("Region d'origine : ");
        scanf("%s", tab[*n].region_origine);

        (*n)++;
    }

    printf("\n Enregistrement termine avec succes !\n");
}

void trier_par_nom(Gestion_des_Etudians tab[], int n)
{
    int i,j;
    Gestion_des_Etudians temp;
    for ( i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if(strcmp(tab[i].nom, tab[j].nom) > 0){
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
        
    }
    
}

void trier_par_filiere(Gestion_des_Etudians tab[], int n)
{
    int i,j;
    Gestion_des_Etudians temp;
    for ( i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if(strcmp(tab[i].filiere, tab[j].filiere) > 0){
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
        
    }
}

//trier_par_nom(etudiants, n); ou trier_par_filiere(etudiants, n);

/* ========= RECHERCHE PAR DICHOTOMIE ========= */

int rechercher_etudiant(Gestion_des_Etudians tab[], int n, char matricule[])
{
    int i, j;
    Gestion_des_Etudians temp;

    /* TRI PAR MATRICULE (obligatoire pour la dichotomie) */
    for (i = 0; i < n - 1; i++)
    {
        for (j = i + 1; j < n; j++)
        {
            if (strcmp(tab[i].matricule, tab[j].matricule) > 0)
            {
                temp = tab[i];
                tab[i] = tab[j];
                tab[j] = temp;
            }
        }
    }

    /* RECHERCHE DICHOTOMIQUE */
    int debut = 0, fin = n - 1, milieu;
    int cmp;

    while (debut <= fin)
    {
        milieu = (debut + fin) / 2;
        cmp = strcmp(tab[milieu].matricule, matricule);

        if (cmp == 0)
            return milieu;
        else if (cmp < 0)
            debut = milieu + 1;
        else
            fin = milieu - 1;
    }

    return -1;
}

/* ========= MODIFIER ========= */

void modifier_etudiant(Gestion_des_Etudians tab[], int n)
{
char matricule[10];
    int i;
    int trouve = 0;

    printf("Entrez le matricule de l'etudiant a modifier : ");
    scanf("%s", matricule);

    for (i = 0; i < n; i++)
    {
        if (strcmp(tab[i].matricule, matricule) == 0)
        {
            printf("\n--- Modification de l'etudiant ---\n");

            printf("Nom : ");
            scanf("%s", tab[i].nom);

            printf("Prenom : ");
            scanf("%s", tab[i].prenom);

            printf("Date de naissance (JJ MM AAAA) : ");
            scanf("%d %d %d",
                  &tab[i].date_naissance.jour,
                  &tab[i].date_naissance.mois,
                  &tab[i].date_naissance.annee);

            do{
              printf("Sexe (M/F) : ");
              scanf(" %c", &tab[i].sexe);

              if (tab[i].sexe != 'M' && tab[i].sexe != 'm' && tab[i].sexe != 'F' && tab[i].sexe != 'f'){
                 printf("Erreur : vous devez entrer M ou F uniquement.\n");
              }
            } while (tab[i].sexe != 'M' && tab[i].sexe != 'm' && tab[i].sexe != 'F' && tab[i].sexe != 'f');

            printf("Departement : ");
            scanf("%s", tab[i].departement);

            printf("Filiere : ");
            scanf("%s", tab[i].filiere);

            printf("Region d'origine : ");
            scanf("%s", tab[i].region_origine);

            trouve = 1;
        }
    }

    if (!trouve)
    {
        printf("\nEtudiant non trouve.\n");
    }
}

/* ========= SUPPRESSION ========= */

void supprimer_etudiant(Gestion_des_Etudians tab[], int *n)
{
    char matricule[10];
    int i, j;
    int trouve = 0;

    printf("Entrez le matricule de l'etudiant a supprimer : ");
    scanf("%s", matricule);

    for (i = 0; i < *n; i++)
    {
        if (strcmp(tab[i].matricule, matricule) == 0)
        {
            for (j = i; j < *n - 1; j++)
            {
                tab[j] = tab[j + 1];
            }
            (*n)--;
            trouve = 1;
            printf("\nEtudiant supprime avec succes.\n");
            break;
        }
    }

    if (!trouve)
    {
        printf("\nEtudiant non trouve.\n");
    }
    

}

void afficher_etudiants(Gestion_des_Etudians tab[], int n)
{
    int i;

    if (n == 0)
    {
        printf("\nAucun etudiant enregistre.\n");
        return;
    }

    printf("\n=====================================================================================================\n");
    printf(" %-3s | %-10s | %-12s | %-12s | %-10s | %-4s | %-12s | %-12s | %-15s\n",
           "N°", "MATRICULE", "NOM", "PRENOM", "NAISSANCE", "SEXE",
           "DEPARTEMENT", "FILIERE", "REGION");
    printf("=======================================================================================================\n");

    for (i = 0; i < n; i++)
    {
        printf(" %-3d | %-10s | %-12s | %-12s | %02d/%02d/%04d | %-4c | %-12s | %-12s | %-15s\n",
               i + 1,
               tab[i].matricule,
               tab[i].nom,
               tab[i].prenom,
               tab[i].date_naissance.jour,
               tab[i].date_naissance.mois,
               tab[i].date_naissance.annee,
               tab[i].sexe,
               tab[i].departement,
               tab[i].filiere,
               tab[i].region_origine);
    }

    printf("========================================================================================================\n");
}



/* ========= AGE ========= */

int calculer_age(Gestion_des_Etudians e)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int age = (tm.tm_year + 1900) - e.date_naissance.annee;
   return age;
}