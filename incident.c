#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "incident.h"

void afficherMenu(void) {
    printf("\n==================== MENU PRINCIPAL ====================\n");
    printf("1. Ajouter un ou plusieurs incidents\n");
    printf("2. Afficher tous les incidents\n");
    printf("3. Rechercher un incident\n");
    printf("4. Modifier un incident\n");
    printf("5. Supprimer un incident\n");
    printf("6. Trier les incidents\n");
    printf("7. Afficher les statistiques\n");
    printf("8. Quitter\n");
    printf("========================================================\n");
}

void lireChaine(char *chaine, int longueur) {
    if (chaine == NULL || longueur <= 0) return;

    int c;
    while ((c = getchar()) == '\n' || c == '\r' || c == ' ');

    int i = 0;
    if (c != EOF) {
        chaine[i++] = (char)c;
    }

    while (i < longueur - 1) {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        chaine[i++] = (char)c;
    }
    chaine[i] = '\0';
}

int chargerIncidents(Incident t[], const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) return 0;

    int n = 0;
    char gTemp[10], sTemp[10];

    while (n < MAX_INCIDENTS && !feof(f)) {
        if (!fgets(t[n].code, sizeof(t[n].code), f)) break;
        t[n].code[strcspn(t[n].code, "\n")] = '\0';

        if (!fgets(t[n].titre, sizeof(t[n].titre), f)) break;
        t[n].titre[strcspn(t[n].titre, "\n")] = '\0';

        if (!fgets(t[n].description, sizeof(t[n].description), f)) break;
        t[n].description[strcspn(t[n].description, "\n")] = '\0';

        if (!fgets(t[n].type, sizeof(t[n].type), f)) break;
        t[n].type[strcspn(t[n].type, "\n")] = '\0';

        if (!fgets(gTemp, sizeof(gTemp), f)) break;
        t[n].gravite = (Gravite)atoi(gTemp);

        if (!fgets(t[n].ip, sizeof(t[n].ip), f)) break;
        t[n].ip[strcspn(t[n].ip, "\n")] = '\0';

        if (!fgets(t[n].machine, sizeof(t[n].machine), f)) break;
        t[n].machine[strcspn(t[n].machine, "\n")] = '\0';

        if (!fgets(t[n].date, sizeof(t[n].date), f)) break;
        t[n].date[strcspn(t[n].date, "\n")] = '\0';

        if (!fgets(t[n].heure, sizeof(t[n].heure), f)) break;
        t[n].heure[strcspn(t[n].heure, "\n")] = '\0';

        if (!fgets(sTemp, sizeof(sTemp), f)) break;
        t[n].statut = (Statut)atoi(sTemp);

        if (!fgets(t[n].technicien, sizeof(t[n].technicien), f)) break;
        t[n].technicien[strcspn(t[n].technicien, "\n")] = '\0';

        if (strlen(t[n].code) > 0) {
            n++;
        }
    }
    fclose(f);
    return n;
}

void sauvegarderIncidents(const Incident t[], int n, const char *filename) {
    FILE *f = fopen(filename, "w");
    if (!f) {
        printf("Erreur d'écriture dans le fichier.\n");
        return;
    }
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s\n%s\n%s\n%s\n%d\n%s\n%s\n%s\n%s\n%d\n%s\n",
                t[i].code, t[i].titre, t[i].description, t[i].type,
                t[i].gravite, t[i].ip, t[i].machine, t[i].date,
                t[i].heure, t[i].statut, t[i].technicien);
    }
    fclose(f);
}

int ajouterIncident(Incident t[], int n) {
    char nbrSaisie[10];
    int nbAajouter = 0;

    printf("Combien d'incidents voulez-vous ajouter ? ");
    lireChaine(nbrSaisie, sizeof(nbrSaisie));
    nbAajouter = atoi(nbrSaisie);

    for (int i = 0; i < nbAajouter; i++) {
        if (n >= MAX_INCIDENTS) {
            printf("Capacité maximale atteinte.\n");
            break;
        }
        printf("\n--- Saisie de l'incident %d ---\n", i + 1);

        printf("Code : ");
        lireChaine(t[n].code, sizeof(t[n].code));

        printf("Titre : ");
        lireChaine(t[n].titre, sizeof(t[n].titre));

        printf("Description : ");
        lireChaine(t[n].description, sizeof(t[n].description));

        printf("Type d'incident : ");
        lireChaine(t[n].type, sizeof(t[n].type));

        char gSaisie[10];
        printf("Gravité (0:Faible, 1:Moyen, 2:Élevé, 3:Critique) : ");
        lireChaine(gSaisie, sizeof(gSaisie));
        int gTemp = atoi(gSaisie);
        t[n].gravite = (gTemp >= 0 && gTemp <= 3) ? (Gravite)gTemp : FAIBLE;

        printf("Adresse IP : ");
        lireChaine(t[n].ip, sizeof(t[n].ip));

        printf("Nom de la machine : ");
        lireChaine(t[n].machine, sizeof(t[n].machine));

        printf("Date (JJ/MM/AAAA) : ");
        lireChaine(t[n].date, sizeof(t[n].date));

        printf("Heure (HH:MM) : ");
        lireChaine(t[n].heure, sizeof(t[n].heure));

        char sSaisie[10];
        printf("Statut (0:Ouvert, 1:En cours, 2:Résolu) : ");
        lireChaine(sSaisie, sizeof(sSaisie));
        int sTemp = atoi(sSaisie);
        t[n].statut = (sTemp >= 0 && sTemp <= 2) ? (Statut)sTemp : OUVERT;

        printf("Technicien responsable : ");
        lireChaine(t[n].technicien, sizeof(t[n].technicien));

        n++;
    }
    return n;
}

void afficherTousIncidents(const Incident t[], int n) {
    if (n == 0) {
        printf("\nAucun incident à afficher.\n");
        return;
    }
    printf("\n%-10s | %-15s | %-10s | %-10s | %-15s | %-15s\n", "CODE", "TITRE", "GRAVITE", "STATUT", "IP", "TECHNICIEN");
    printf("-----------------------------------------------------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("%-10s | %-15.15s | %-10s | %-10s | %-15s | %-15s\n",
               t[i].code, t[i].titre, graviteVersChaine(t[i].gravite),
               statutVersChaine(t[i].statut), t[i].ip, t[i].technicien);
    }
}

void rechercherIncident(const Incident t[], int n) {
    if (n == 0) {
        printf("\nAucun incident enregistré.\n");
        return;
    }
    char critereSaisie[10];
    printf("\nRecherche par :\n1. Code\n2. Adresse IP\n3. Nom du technicien\n4. Niveau de gravité\nChoix : ");
    lireChaine(critereSaisie, sizeof(critereSaisie));
    int critere = atoi(critereSaisie);

    char cle[MAX_STR];
    int graviteCle = -1;
    if (critere >= 1 && critere <= 3) {
        printf("Entrez la valeur recherchée : ");
        lireChaine(cle, sizeof(cle));
    } else if (critere == 4) {
        char gSaisie[10];
        printf("Entrez le niveau de gravité (0:Faible, 1:Moyen, 2:Élevé, 3:Critique) : ");
        lireChaine(gSaisie, sizeof(gSaisie));
        graviteCle = atoi(gSaisie);
    } else {
        printf("Critère invalide.\n");
        return;
    }

    int trouve = 0;
    for (int i = 0; i < n; i++) {
        int match = 0;
        if (critere == 1 && strcmp(t[i].code, cle) == 0) match = 1;
        else if (critere == 2 && strcmp(t[i].ip, cle) == 0) match = 1;
        else if (critere == 3 && strcmp(t[i].technicien, cle) == 0) match = 1;
        else if (critere == 4 && (int)t[i].gravite == graviteCle) match = 1;

        if (match) {
            if (!trouve) {
                printf("\n%-10s | %-15s | %-10s | %-10s\n", "CODE", "TITRE", "GRAVITE", "STATUT");
                printf("---------------------------------------------------\n");
            }
            printf("%-10s | %-15.15s | %-10s | %-10s\n", t[i].code, t[i].titre, graviteVersChaine(t[i].gravite), statutVersChaine(t[i].statut));
            trouve = 1;
        }
    }
    if (!trouve) printf("Aucun incident trouvé correspondant à ce critère.\n");
}

void modifierIncident(Incident t[], int n) {
    char codeRecherche[15];
    printf("Entrez le code de l'incident à modifier : ");
    lireChaine(codeRecherche, sizeof(codeRecherche));

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(t[i].code, codeRecherche) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Incident introuvable.\n");
        return;
    }

    char sSaisie[10];
    printf("Nouveau statut (0:Ouvert, 1:En cours, 2:Résolu) : ");
    lireChaine(sSaisie, sizeof(sSaisie));
    int sTemp = atoi(sSaisie);
    if (sTemp >= 0 && sTemp <= 2) t[index].statut = (Statut)sTemp;

    char gSaisie[10];
    printf("Nouveau niveau de gravité (0:Faible, 1:Moyen, 2:Élevé, 3:Critique) : ");
    lireChaine(gSaisie, sizeof(gSaisie));
    int gTemp = atoi(gSaisie);
    if (gTemp >= 0 && gTemp <= 3) t[index].gravite = (Gravite)gTemp;

    printf("Nouveau technicien responsable : ");
    lireChaine(t[index].technicien, sizeof(t[index].technicien));

    printf("Incident modifié avec succès.\n");
}

int supprimerIncident(Incident t[], int n) {
    char codeRecherche[15];
    printf("Entrez le code de l'incident à supprimer : ");
    lireChaine(codeRecherche, sizeof(codeRecherche));

    int index = -1;
    for (int i = 0; i < n; i++) {
        if (strcmp(t[i].code, codeRecherche) == 0) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("Incident introuvable.\n");
        return n;
    }

    for (int i = index; i < n - 1; i++) {
        t[i] = t[i + 1];
    }
    printf("Incident supprimé avec succès.\n");
    return n - 1;
}

void trierIncidents(Incident t[], int n) {
    if (n <= 1) {
        printf("Pas assez d'éléments pour trier.\n");
        return;
    }
    char choixSaisie[10];
    printf("\nTrier par :\n1. Code\n2. Niveau de gravité\n3. Date de détection\nChoix : ");
    lireChaine(choixSaisie, sizeof(choixSaisie));
    int choixTri = atoi(choixSaisie);

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            int condition = 0;
            if (choixTri == 1 && strcmp(t[j].code, t[j + 1].code) > 0) condition = 1;
            else if (choixTri == 2 && t[j].gravite > t[j + 1].gravite) condition = 1;
            else if (choixTri == 3 && strcmp(t[j].date, t[j + 1].date) > 0) condition = 1;

            if (condition) {
                Incident temp = t[j];
                t[j] = t[j + 1];
                t[j + 1] = temp;
            }
        }
    }
    printf("Tri effectué. Affichage du résultat :\n");
    afficherTousIncidents(t, n);
}

void afficherStatistiques(const Incident t[], int n) {
    printf("\n================ STATISTIQUES ================\n");
    printf("Nombre total d'incidents : %d\n", n);

    int critiques = 0, resolus = 0, ouverts = 0;
    int gravites[4] = {0};

    for (int i = 0; i < n; i++) {
        if (t[i].gravite == CRITIQUE) critiques++;
        if (t[i].statut == RESOLU) resolus++;
        if (t[i].statut == OUVERT) ouverts++;
        if (t[i].gravite >= 0 && t[i].gravite <= 3) gravites[t[i].gravite]++;
    }

    printf("Nombre d'incidents critiques : %d\n", critiques);
    printf("Nombre d'incidents résolus : %d\n", resolus);
    printf("Nombre d'incidents ouverts : %d\n", ouverts);
    printf("----------------------------------------------\n");
    printf("Par niveau de gravité :\n");
    for (int i = 0; i < 4; i++) {
        printf("  - %s : %d\n", graviteVersChaine((Gravite)i), gravites[i]);
    }
    printf("----------------------------------------------\n");
    printf("Nombre d'incidents traités par technicien :\n");

    char techniciensTraites[MAX_INCIDENTS][MAX_STR];
    int nbTechs = 0;

    for (int i = 0; i < n; i++) {
        int dejaCompte = 0;
        for (int j = 0; j < nbTechs; j++) {
            if (strcmp(techniciensTraites[j], t[i].technicien) == 0) {
                dejaCompte = 1;
                break;
            }
        }
        if (!dejaCompte) {
            strcpy(techniciensTraites[nbTechs], t[i].technicien);
            int count = 0;
            for (int k = 0; k < n; k++) {
                if (strcmp(t[k].technicien, t[i].technicien) == 0) {
                    count++;
                }
            }
            printf("  - %s : %d incident(s)\n", t[i].technicien, count);
            nbTechs++;
        }
    }
    printf("==============================================\n");
}

const char* graviteVersChaine(Gravite g) {
    const char *chaines[] = {"Faible", "Moyen", "Élevé", "Critique"};
    return (g >= FAIBLE && g <= CRITIQUE) ? chaines[g] : "Inconnu";
}

const char* statutVersChaine(Statut s) {
    const char *chaines[] = {"Ouvert", "En cours", "Résolu"};
    return (s >= OUVERT && s <= RESOLU) ? chaines[s] : "Inconnu";
}
