#ifndef INCIDENTS_H
#define INCIDENTS_H

#define MAX_INCIDENTS 100
#define MAX_STR 50
#define MAX_DESC 200
#define FILENAME "incidents.csv"

typedef enum { FAIBLE, MOYEN, ELEVE, CRITIQUE } Gravite;
typedef enum { OUVERT, EN_COURS, RESOLU } Statut;

typedef struct {
    char code[15];
    char titre[MAX_STR];
    char description[MAX_DESC];
    char type[MAX_STR];
    Gravite gravite;
    char ip[16];
    char machine[MAX_STR];
    char date[11];
    char heure[6];
    Statut statut;
    char technicien[MAX_STR];
} Incident;

void afficherMenu(void);
int chargerIncidents(Incident t[], const char *filename);
void sauvegarderIncidents(const Incident t[], int n, const char *filename);
int ajouterIncident(Incident t[], int n);
void afficherTousIncidents(const Incident t[], int n);
void rechercherIncident(const Incident t[], int n);
void modifierIncident(Incident t[], int n);
int supprimerIncident(Incident t[], int n);
void trierIncidents(Incident t[], int n);
void afficherStatistiques(const Incident t[], int n);
const char* graviteVersChaine(Gravite g);
const char* statutVersChaine(Statut s);
void lireChaine(char *chaine, int longueur);

#endif
