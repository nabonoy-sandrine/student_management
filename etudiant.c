// implémente les fonctions permettant d’ajouter, afficher, rechercher, modifier et supprimer des étudiants.

#include "etudiant.h"
#include <string.h>
#include <time.h>

/* ========= MENU ========= */

    void menu()
{
    printf("\n");
    printf("╔==***=======================***=========================***===╗\n");
    printf("*                                                              *\n");
    printf("*     BIENVENUE DANS LE SYSTEME DE GESTION DES ETUDIANTS       *\n");
    printf("*                                                              *\n");
    printf("╠==***=======================***=========================***===╣\n");
    printf("*  1 - Enregistrer un etudiant                                 *\n");
    printf("*  2 - Modifier un etudiant                                    *\n");
    printf("║  3 - Rechercher un etudiant (recherche dichotomique)         ║\n");
    printf("║  4 - Supprimer un etudiant                                   ║\n");
    printf("*  5 - Trier par ordre alphabetique (Nom)                      *\n");
    printf("║  6 - Calculer l'age d'un etudiant                            ║\n");
    printf("║  7 - Trier par filiere                                       ║\n");
    printf("║  8 - Afficher la liste des etudiants                         ║\n");
    printf("*                                                              *\n");
    printf("*  0 - Quitter                                                 *\n");
    printf("╚==============================================================╝\n");
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
        printf(" Erreur : nombre maximum d'etudiants dépassé.\n");
        pause_console();
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
                    printf(" Erreur : ce matricule existe déjà. Entrez un autre.\n");
                    break;
                }
            }
        } while (existe);

        /* ===== Nom et Prénom ===== */
        printf("Nom : ");
        scanf("%s", tab[*n].nom);

        printf("Prenom : ");
        scanf("%s", tab[*n].prenom);

        /* ===== Date de naissance (avec validation) ===== */
        do
        {
            printf("Date de naissance (JJ MM AAAA) : ");
            scanf("%d %d %d",
                  &tab[*n].date_naissance.jour,
                  &tab[*n].date_naissance.mois,
                  &tab[*n].date_naissance.annee);

            if (!date_valide(tab[*n].date_naissance.jour,
                             tab[*n].date_naissance.mois,
                             tab[*n].date_naissance.annee))
            {
                printf(" Date invalide. Veuillez entrer à nouveau.\n");
            }
        } while (!date_valide(tab[*n].date_naissance.jour,
                              tab[*n].date_naissance.mois,
                              tab[*n].date_naissance.annee));

        /* ===== Sexe ===== */
        do
        {
            printf("Sexe (M/F) : ");
            scanf(" %c", &tab[*n].sexe);

            if (tab[*n].sexe != 'M' && tab[*n].sexe != 'm' &&
                tab[*n].sexe != 'F' && tab[*n].sexe != 'f')
            {
                printf(" Erreur : vous devez entrer M ou F uniquement.\n");
            }

        } while (tab[*n].sexe != 'M' && tab[*n].sexe != 'm' &&
                 tab[*n].sexe != 'F' && tab[*n].sexe != 'f');

        /* ===== Département, Filière, Région ===== */
        printf("Departement : ");
        scanf("%s", tab[*n].departement);

        printf("Filiere : ");
        scanf("%s", tab[*n].filiere);

        printf("Region d'origine : ");
        scanf("%s", tab[*n].region_origine);

        (*n)++;
    }

    printf("\n Enregistrement terminé avec succès !\n");
    pause_console();
}


void trier_par_nom(Gestion_des_Etudians tab[], int n)
{

}

void trier_par_filiere(Gestion_des_Etudians tab[], int n)
{

}

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
    pause_console();
}


/* ========= MODIFIER ========= */

void modifier_etudiant(Gestion_des_Etudians tab[], int n)
{
    char matricule[20];
    int pos, choix;

    if (n == 0)
    {
        printf("\n⚠ Aucun étudiant enregistré.\n");
        pause_console();
        return;
    }

    printf("Entrez le matricule de l'etudiant a modifier : ");
    scanf("%s", matricule);

    /* Le tableau doit être déjà trié par matricule */
    pos = rechercher_etudiant(tab, n, matricule);

    if (pos == -1)
    {
        printf("\n Etudiant non trouvé.\n");
        pause_console();
        return;
    }

    printf("\n Etudiant trouvé : %s %s\n",
           tab[pos].nom, tab[pos].prenom);

    do
    {
        menu_modification();
        scanf("%d", &choix);

        switch (choix)
        {
        case 1:
            printf("Nouveau nom : ");
            scanf("%s", tab[pos].nom);
            break;

        case 2:
            printf("Nouveau prenom : ");
            scanf("%s", tab[pos].prenom);
            break;

        case 3:
            printf("Nouvelle date (JJ MM AAAA) : ");
            scanf("%d %d %d",
                  &tab[pos].date_naissance.jour,
                  &tab[pos].date_naissance.mois,
                  &tab[pos].date_naissance.annee);
            break;

        case 4:
            do
            {
                printf("Sexe (M/F) : ");
                scanf(" %c", &tab[pos].sexe);
            } while (tab[pos].sexe != 'M' && tab[pos].sexe != 'm' &&
                     tab[pos].sexe != 'F' && tab[pos].sexe != 'f');
            break;

        case 5:
            printf("Nouveau departement : ");
            scanf("%s", tab[pos].departement);
            break;

        case 6:
            printf("Nouvelle filiere : ");
            scanf("%s", tab[pos].filiere);
            break;

        case 7:
            printf("Nouvelle region : ");
            scanf("%s", tab[pos].region_origine);
            break;

        case 0:
            printf("\n Modification terminée.\n");
            break;

        default:
            printf("⚠ Choix invalide.\n");
        }

    } while (choix != 0);

    pause_console();
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
    pause_console();
    

}

void afficher_etudiants(Gestion_des_Etudians tab[], int n)
{
    int i;

    if (n == 0)
    {
        printf("\n⚠ Aucun étudiant enregistré dans le système.\n");
        pause_console();
        return;
    }

    printf("\n══════════════════════════════════════════════════════════════════════════════════════════════════════\n");
    printf("                                LISTE DES ETUDIANTS ENREGISTRES\n");
    printf("══════════════════════════════════════════════════════════════════════════════════════════════════════\n");

    printf("╔════╦═══════════════╦════════════╦════════════╦════════════╦════╦════════════╦════════════╦════════════╗\n");
    printf("║ N° ║ MATRICULE     ║ NOM        ║ PRENOM     ║ NAISSANCE  ║ SX ║ DEPARTEMENT║ FILIERE    ║ REGION     ║\n");
    printf("╠════╬═══════════════╬════════════╬════════════╬════════════╬════╬════════════╬════════════╬════════════╣\n");

    for (i = 0; i < n; i++)
    {
        printf("║ %-2d ║ %-13s ║ %-10s ║ %-10s ║ %02d/%02d/%04d ║ %-2c ║ %-10s ║ %-10s ║ %-10s ║\n",
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

    printf("╚════╩═══════════════╩════════════╩════════════╩════════════╩════╩════════════╩════════════╩════════════╝\n");
    printf("Total : %d étudiant(s) enregistré(s).\n", n);

    pause_console();
}



/* ========= AGE ========= */

int calculer_age(Gestion_des_Etudians e)
{
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    int age = (tm.tm_year + 1900) - e.date_naissance.annee;
   return age;
   pause_console();
}


void pause_console()
{
    printf("\nAppuyez sur Entree pour continuer...");
    getchar();   // consomme le \n restant
    getchar();   // attend que l'utilisateur appuie sur Entree
}


void menu_modification()
{
    printf("\n----- CHOISIR LE CHAMPS QUE VOUS SOUHAITEZ MODIFIER -----\n");
    printf("1 - Nom\n");
    printf("2 - Prenom\n");
    printf("3 - Date de naissance\n");
    printf("4 - Sexe\n");
    printf("5 - Departement\n");
    printf("6 - Filiere\n");
    printf("7 - Region d'origine\n");
    printf("0 - Terminer la modification\n");
    printf("Votre choix : ");
}


int date_valide(int jour, int mois, int annee)
{
    if (annee < 1900 || annee > 2100)
        return 0; // année invalide
    if (mois < 1 || mois > 12)
        return 0; // mois invalide

    int jours_par_mois[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

    // année bissextile ?
    if ((annee % 4 == 0 && annee % 100 != 0) || (annee % 400 == 0))
        jours_par_mois[1] = 29;

    if (jour < 1 || jour > jours_par_mois[mois - 1])
        return 0; // jour invalide

    return 1; // date valide
}
