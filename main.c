// contient la fonction principale et gère le menu ainsi que les appels aux fonctions de gestion des étudiants.

#include "etudiant.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main()
{
    Gestion_des_Etudians etudiants[MAX];
    int n = 0;
    int choix;
    char mat[20];
    int pos;


    do
    {
        menu();
        scanf("%d", &choix);

        switch (choix)
        {
            case 1:
                ajouter_etudiant(etudiants, &n);
                break;

            case 2:
               if (n == 0)
               {
                 printf("Aucun etudiant enregistre.\n");
               }
               else
              {
                modifier_etudiant(etudiants, n);
              }
              break;


            case 3:
                if (n == 0)
                {
                   printf("Aucun etudiant enregistre.\n");
                       break;
                }

              printf("Entrer le matricule a rechercher : ");
              scanf("%s", mat);

              pos = rechercher_etudiant(etudiants, n, mat);

              if (pos == -1)
              {
                printf(" Etudiant non trouve.\n");
              }
              else
             {
                printf("Etudiant trouve :\n");
                printf("\nEtudiant %d\n", pos + 1);
                printf("Matricule        : %s\n", etudiants[pos].matricule);
                printf("Nom              : %s\n", etudiants[pos].nom);
                printf("Prenom           : %s\n", etudiants[pos].prenom);
                printf("Date de naissance: %02d/%02d/%04d\n",
                  etudiants[pos].date_naissance.jour,
                  etudiants[pos].date_naissance.mois,
                  etudiants[pos].date_naissance.annee);
                printf("Sexe             : %c\n", etudiants[pos].sexe);
                printf("Departement      : %s\n", etudiants[pos].departement);
                printf("Filiere          : %s\n", etudiants[pos].filiere);
                printf("Region d'origine : %s\n", etudiants[pos].region_origine);
             }
             break;

            case 4:
              if (n == 0)
              {
                printf("Aucun etudiant enregistre.\n");
              }
              else
              {
                supprimer_etudiant(etudiants, &n);
              }
              break;


            case 5:
                if (n < 2){
                  printf("Impossible de trier : moins de 2 etudiants.\n");
                }
                else{
                  trier_par_nom(etudiants, n);
                  printf("Tri par nom effectue.\n");
                  afficher_etudiants(etudiants, n);
              }
            break;
            case 6:
                printf("Entrer le matricule : ");
                scanf("%s", mat);

                pos = rechercher_etudiant(etudiants, n, mat);

                if (pos == -1)
                  printf("Etudiant non trouve.\n");
               else
                  printf("Age : %d ans\n", calculer_age(etudiants[pos]));

               break;
            case 7:
               trier_par_filiere(etudiants, n);
               printf("Tri par filiere effectue.\n");
               break;

            case 8:
                 afficher_etudiants(etudiants, n);
                 break;

            case 0:
                printf("Fin du programme.\n");
                break;

            default:
                printf("Choix invalide !\n");
        }

    } while (choix != 0);

    return 0;
}
