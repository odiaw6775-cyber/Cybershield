#include <stdio.h>
#include <stdlib.h>
#include "incident.h"

int main(void) {
    Incident tableauIncidents[MAX_INCIDENTS];
    int nbIncidents = 0;
    int choix;
    char saisie[10];

    nbIncidents = chargerIncidents(tableauIncidents, FILENAME);

    do {
        afficherMenu();
        printf("Votre choix : ");

        if (fgets(saisie, sizeof(saisie), stdin) != NULL) {
            if (sscanf(saisie, "%d", &choix) != 1) {
                choix = 0;
            }
        }

        switch (choix) {
            case 1:
                nbIncidents = ajouterIncident(tableauIncidents, nbIncidents);
                sauvegarderIncidents(tableauIncidents, nbIncidents, FILENAME);
                break;
            case 2:
                afficherTousIncidents(tableauIncidents, nbIncidents);
                break;
            case 3:
                rechercherIncident(tableauIncidents, nbIncidents);
                break;
            case 4:
                modifierIncident(tableauIncidents, nbIncidents);
                sauvegarderIncidents(tableauIncidents, nbIncidents, FILENAME);
                break;
            case 5:
                nbIncidents = supprimerIncident(tableauIncidents, nbIncidents);
                sauvegarderIncidents(tableauIncidents, nbIncidents, FILENAME);
                break;
            case 6:
                trierIncidents(tableauIncidents, nbIncidents);
                break;
            case 7:
                afficherStatistiques(tableauIncidents, nbIncidents);
                break;
            case 8:
                printf("\nArrêt du programme et sauvegarde des données.\n");
                break;
            default:
                printf("\nOption invalide.\n");
        }
        if (choix != 8) {
            printf("\nAppuyez sur Entrée pour continuer...");
            getchar();
        }
    } while (choix != 8);

    return 0;
}
