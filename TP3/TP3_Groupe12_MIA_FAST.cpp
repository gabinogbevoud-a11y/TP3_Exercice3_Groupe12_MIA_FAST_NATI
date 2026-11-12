#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ETUDIANTS 100
#define MAX_CHAMBRES 100
#define MAX_DEMANDES 200
#define MAX_ATTRIBUTIONS 200
#define TAILLE_NOM 100
#define TAILLE_EMAIL 100
#define TAILLE_DATE 20

/* =========================
   Structures de données
   ========================= */

typedef struct {
    int id;
    char nom[TAILLE_NOM];
    char email[TAILLE_EMAIL];
} Etudiant;

typedef struct {
    int id;
    char numero[20];
    char batiment[50];
    int capacite;
    int occupee;
} Chambre;

typedef enum {
    DEMANDE_EN_ATTENTE,
    DEMANDE_ACCEPTEE,
    DEMANDE_REFUSEE,
    DEMANDE_TERMINEE
} EtatDemande;

typedef struct {
    int id;
    int idEtudiant;
    char dateDemande[TAILLE_DATE];
    EtatDemande etat;
} DemandeHebergement;

typedef struct {
    int id;
    int idEtudiant;
    int idChambre;
    int idDemande;
    char dateDebut[TAILLE_DATE];
    char dateFin[TAILLE_DATE];
    int active;
} Attribution;

/* =========================
   Variables globales
   ========================= */

Etudiant etudiants[MAX_ETUDIANTS];
Chambre chambres[MAX_CHAMBRES];
DemandeHebergement demandes[MAX_DEMANDES];
Attribution attributions[MAX_ATTRIBUTIONS];

int nbEtudiants = 0;
int nbChambres = 0;
int nbDemandes = 0;
int nbAttributions = 0;

/* =========================
   Fonctions utilitaires
   ========================= */

void viderBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* Nettoyage du buffer */
    }
}

void lireTexte(const char *message, char *chaine, int taille) {
    printf("%s", message);
    fgets(chaine, taille, stdin);
    chaine[strcspn(chaine, "\n")] = '\0';
}

int trouverEtudiant(int id) {
    for (int i = 0; i < nbEtudiants; i++) {
        if (etudiants[i].id == id) {
            return i;
        }
    }
    return -1;
}

int trouverChambre(int id) {
    for (int i = 0; i < nbChambres; i++) {
        if (chambres[i].id == id) {
            return i;
        }
    }
    return -1;
}

int trouverDemande(int id) {
    for (int i = 0; i < nbDemandes; i++) {
        if (demandes[i].id == id) {
            return i;
        }
    }
    return -1;
}

int trouverAttributionActiveParEtudiant(int idEtudiant) {
    for (int i = 0; i < nbAttributions; i++) {
        if (attributions[i].idEtudiant == idEtudiant &&
            attributions[i].active == 1) {
            return i;
        }
    }
    return -1;
}

const char *texteEtatDemande(EtatDemande etat) {
    switch (etat) {
        case DEMANDE_EN_ATTENTE:
            return "En attente";
        case DEMANDE_ACCEPTEE:
            return "Acceptee";
        case DEMANDE_REFUSEE:
            return "Refusee";
        case DEMANDE_TERMINEE:
            return "Terminee";
        default:
            return "Inconnue";
    }
}

/* =========================
   Gestion des étudiants
   ========================= */

void enregistrerEtudiant(void) {
    if (nbEtudiants >= MAX_ETUDIANTS) {
        printf("Capacite maximale d'etudiants atteinte.\n");
        return;
    }

    etudiants[nbEtudiants].id = nbEtudiants + 1;

    printf("Nom complet : ");
    viderBuffer();
    fgets(etudiants[nbEtudiants].nom, TAILLE_NOM, stdin);
    etudiants[nbEtudiants].nom[strcspn(etudiants[nbEtudiants].nom, "\n")] = '\0';

    lireTexte("Email : ", etudiants[nbEtudiants].email, TAILLE_EMAIL);

    printf("Etudiant enregistre avec l'identifiant %d.\n",
           etudiants[nbEtudiants].id);
    nbEtudiants++;
}

void afficherEtudiants(void) {
    if (nbEtudiants == 0) {
        printf("Aucun etudiant enregistre.\n");
        return;
    }

    printf("\n===== LISTE DES ETUDIANTS =====\n");
    for (int i = 0; i < nbEtudiants; i++) {
        printf("ID : %d | Nom : %s | Email : %s\n",
               etudiants[i].id,
               etudiants[i].nom,
               etudiants[i].email);
    }
}

/* =========================
   Gestion des chambres
   ========================= */

void enregistrerChambre(void) {
    if (nbChambres >= MAX_CHAMBRES) {
        printf("Capacite maximale de chambres atteinte.\n");
        return;
    }

    chambres[nbChambres].id = nbChambres + 1;
    chambres[nbChambres].occupee = 0;

    lireTexte("Numero de chambre : ",
              chambres[nbChambres].numero,
              sizeof(chambres[nbChambres].numero));

    lireTexte("Batiment : ",
              chambres[nbChambres].batiment,
              sizeof(chambres[nbChambres].batiment));

    printf("Capacite de la chambre : ");
    scanf("%d", &chambres[nbChambres].capacite);

    if (chambres[nbChambres].capacite <= 0) {
        chambres[nbChambres].capacite = 1;
    }

    printf("Chambre enregistree avec l'identifiant %d.\n",
           chambres[nbChambres].id);
    nbChambres++;
}

void afficherChambres(void) {
    if (nbChambres == 0) {
        printf("Aucune chambre enregistree.\n");
        return;
    }

    printf("\n===== LISTE DES CHAMBRES =====\n");
    for (int i = 0; i < nbChambres; i++) {
        printf("ID : %d | Numero : %s | Batiment : %s | Capacite : %d | Etat : %s\n",
               chambres[i].id,
               chambres[i].numero,
               chambres[i].batiment,
               chambres[i].capacite,
               chambres[i].occupee ? "Occupee" : "Libre");
    }
}

void afficherChambresLibres(void) {
    int trouvee = 0;

    printf("\n===== CHAMBRES LIBRES =====\n");
    for (int i = 0; i < nbChambres; i++) {
        if (chambres[i].occupee == 0) {
            printf("ID : %d | Numero : %s | Batiment : %s | Capacite : %d\n",
                   chambres[i].id,
                   chambres[i].numero,
                   chambres[i].batiment,
                   chambres[i].capacite);
            trouvee = 1;
        }
    }

    if (!trouvee) {
        printf("Aucune chambre libre.\n");
    }
}

void afficherChambresOccupees(void) {
    int trouvee = 0;

    printf("\n===== CHAMBRES OCCUPEES =====\n");
    for (int i = 0; i < nbChambres; i++) {
        if (chambres[i].occupee == 1) {
            printf("ID : %d | Numero : %s | Batiment : %s\n",
                   chambres[i].id,
                   chambres[i].numero,
                   chambres[i].batiment);
            trouvee = 1;
        }
    }

    if (!trouvee) {
        printf("Aucune chambre occupee.\n");
    }
}

/* =========================
   Gestion des demandes
   ========================= */

void enregistrerDemande(void) {
    int idEtudiant;

    if (nbDemandes >= MAX_DEMANDES) {
        printf("Capacite maximale de demandes atteinte.\n");
        return;
    }

    if (nbEtudiants == 0) {
        printf("Enregistrez d'abord un etudiant.\n");
        return;
    }

    afficherEtudiants();
    printf("Identifiant de l'etudiant : ");
    scanf("%d", &idEtudiant);

    if (trouverEtudiant(idEtudiant) == -1) {
        printf("Etudiant introuvable.\n");
        return;
    }

    demandes[nbDemandes].id = nbDemandes + 1;
    demandes[nbDemandes].idEtudiant = idEtudiant;
    demandes[nbDemandes].etat = DEMANDE_EN_ATTENTE;

    lireTexte("Date de la demande : ",
              demandes[nbDemandes].dateDemande,
              TAILLE_DATE);

    printf("Demande enregistree avec l'identifiant %d.\n",
           demandes[nbDemandes].id);
    nbDemandes++;
}

void afficherDemandes(void) {
    if (nbDemandes == 0) {
        printf("Aucune demande enregistree.\n");
        return;
    }

    printf("\n===== DEMANDES D'HEBERGEMENT =====\n");
    for (int i = 0; i < nbDemandes; i++) {
        int indexEtudiant = trouverEtudiant(demandes[i].idEtudiant);

        printf("ID demande : %d | Etudiant : %s | Date : %s | Etat : %s\n",
               demandes[i].id,
               indexEtudiant != -1 ? etudiants[indexEtudiant].nom : "Inconnu",
               demandes[i].dateDemande,
               texteEtatDemande(demandes[i].etat));
    }
}

/* =========================
   Attribution et départs
   ========================= */

void attribuerChambre(void) {
    int idEtudiant, idChambre, idDemande;

    if (nbAttributions >= MAX_ATTRIBUTIONS) {
        printf("Capacite maximale d'attributions atteinte.\n");
        return;
    }

    if (nbEtudiants == 0 || nbChambres == 0 || nbDemandes == 0) {
        printf("Il faut au moins un etudiant, une chambre et une demande.\n");
        return;
    }

    afficherEtudiants();
    printf("Identifiant de l'etudiant : ");
    scanf("%d", &idEtudiant);

    if (trouverEtudiant(idEtudiant) == -1) {
        printf("Etudiant introuvable.\n");
        return;
    }

    if (trouverAttributionActiveParEtudiant(idEtudiant) != -1) {
        printf("Cet etudiant possede deja une chambre.\n");
        return;
    }

    afficherDemandes();
    printf("Identifiant de la demande : ");
    scanf("%d", &idDemande);

    int indexDemande = trouverDemande(idDemande);
    if (indexDemande == -1 || demandes[indexDemande].idEtudiant != idEtudiant) {
        printf("Demande invalide pour cet etudiant.\n");
        return;
    }

    if (demandes[indexDemande].etat != DEMANDE_EN_ATTENTE) {
        printf("Cette demande n'est plus en attente.\n");
        return;
    }

    afficherChambresLibres();
    printf("Identifiant de la chambre : ");
    scanf("%d", &idChambre);

    int indexChambre = trouverChambre(idChambre);
    if (indexChambre == -1) {
        printf("Chambre introuvable.\n");
        return;
    }

    if (chambres[indexChambre].occupee == 1) {
        printf("Cette chambre est deja occupee.\n");
        return;
    }

    attributions[nbAttributions].id = nbAttributions + 1;
    attributions[nbAttributions].idEtudiant = idEtudiant;
    attributions[nbAttributions].idChambre = idChambre;
    attributions[nbAttributions].idDemande = idDemande;
    attributions[nbAttributions].active = 1;

    lireTexte("Date de debut d'occupation : ",
              attributions[nbAttributions].dateDebut,
              TAILLE_DATE);

    strcpy(attributions[nbAttributions].dateFin, "-");

    chambres[indexChambre].occupee = 1;
    demandes[indexDemande].etat = DEMANDE_ACCEPTEE;

    printf("Chambre attribuee avec succes.\n");
    nbAttributions++;
}

void enregistrerDepart(void) {
    int idEtudiant;

    printf("Identifiant de l'etudiant qui quitte la residence : ");
    scanf("%d", &idEtudiant);

    int indexAttribution = trouverAttributionActiveParEtudiant(idEtudiant);
    if (indexAttribution == -1) {
        printf("Aucune attribution active pour cet etudiant.\n");
        return;
    }

    int indexChambre = trouverChambre(attributions[indexAttribution].idChambre);
    int indexDemande = trouverDemande(attributions[indexAttribution].idDemande);

    lireTexte("Date de fin d'occupation : ",
              attributions[indexAttribution].dateFin,
              TAILLE_DATE);

    attributions[indexAttribution].active = 0;

    if (indexChambre != -1) {
        chambres[indexChambre].occupee = 0;
    }

    if (indexDemande != -1) {
        demandes[indexDemande].etat = DEMANDE_TERMINEE;
    }

    printf("Depart enregistre. La chambre est maintenant libre.\n");
}

void afficherAttributionsActives(void) {
    int trouvee = 0;

    printf("\n===== OCCUPATIONS ACTUELLES =====\n");
    for (int i = 0; i < nbAttributions; i++) {
        if (attributions[i].active == 1) {
            int indexEtudiant = trouverEtudiant(attributions[i].idEtudiant);
            int indexChambre = trouverChambre(attributions[i].idChambre);

            printf("Attribution %d | Etudiant : %s | Chambre : %s | Debut : %s\n",
                   attributions[i].id,
                   indexEtudiant != -1 ? etudiants[indexEtudiant].nom : "Inconnu",
                   indexChambre != -1 ? chambres[indexChambre].numero : "Inconnue",
                   attributions[i].dateDebut);
            trouvee = 1;
        }
    }

    if (!trouvee) {
        printf("Aucune occupation actuelle.\n");
    }
}

void afficherHistorique(void) {
    if (nbAttributions == 0) {
        printf("Aucun historique d'occupation.\n");
        return;
    }

    printf("\n===== HISTORIQUE DES OCCUPATIONS =====\n");
    for (int i = 0; i < nbAttributions; i++) {
        int indexEtudiant = trouverEtudiant(attributions[i].idEtudiant);
        int indexChambre = trouverChambre(attributions[i].idChambre);

        printf("Attribution %d | Etudiant : %s | Chambre : %s | Debut : %s | Fin : %s | Etat : %s\n",
               attributions[i].id,
               indexEtudiant != -1 ? etudiants[indexEtudiant].nom : "Inconnu",
               indexChambre != -1 ? chambres[indexChambre].numero : "Inconnue",
               attributions[i].dateDebut,
               attributions[i].dateFin,
               attributions[i].active ? "Active" : "Terminee");
    }
}

/* =========================
   Statistiques
   ========================= */

void afficherStatistiques(void) {
    int chambresOccupees = 0;
    int capaciteTotale = 0;
    int placesOccupees = 0;

    for (int i = 0; i < nbChambres; i++) {
        capaciteTotale += chambres[i].capacite;

        if (chambres[i].occupee == 1) {
            chambresOccupees++;
            placesOccupees += chambres[i].capacite;
        }
    }

    double tauxOccupationChambres = 0.0;
    double tauxOccupationPlaces = 0.0;

    if (nbChambres > 0) {
        tauxOccupationChambres = ((double) chambresOccupees / nbChambres) * 100;
    }

    if (capaciteTotale > 0) {
        tauxOccupationPlaces = ((double) placesOccupees / capaciteTotale) * 100;
    }

    printf("\n===== STATISTIQUES DE LA RESIDENCE =====\n");
    printf("Nombre total de chambres : %d\n", nbChambres);
    printf("Chambres occupees : %d\n", chambresOccupees);
    printf("Chambres libres : %d\n", nbChambres - chambresOccupees);
    printf("Capacite totale : %d place(s)\n", capaciteTotale);
    printf("Places considerees occupees : %d\n", placesOccupees);
    printf("Taux d'occupation des chambres : %.2f %%\n", tauxOccupationChambres);
    printf("Taux d'occupation des places : %.2f %%\n", tauxOccupationPlaces);
}

/* =========================
   Menu principal
   ========================= */

void afficherMenu(void) {
    printf("\n===========================================\n");
    printf(" SYSTEME DE GESTION D'UNE RESIDENCE\n");
    printf("===========================================\n");
    printf("1. Enregistrer un etudiant\n");
    printf("2. Afficher les etudiants\n");
    printf("3. Enregistrer une chambre\n");
    printf("4. Afficher toutes les chambres\n");
    printf("5. Afficher les chambres libres\n");
    printf("6. Afficher les chambres occupees\n");
    printf("7. Enregistrer une demande d'hebergement\n");
    printf("8. Afficher les demandes\n");
    printf("9. Attribuer une chambre\n");
    printf("10. Enregistrer un depart\n");
    printf("11. Afficher les occupations actuelles\n");
    printf("12. Afficher l'historique des occupations\n");
    printf("13. Afficher les statistiques\n");
    printf("0. Quitter\n");
    printf("Votre choix : ");
}

int main(void) {
    int choix;

    do {
        afficherMenu();
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                enregistrerEtudiant();
                break;
            case 2:
                afficherEtudiants();
                break;
            case 3:
                enregistrerChambre();
                break;
            case 4:
                afficherChambres();
                break;
            case 5:
                afficherChambresLibres();
                break;
            case 6:
                afficherChambresOccupees();
                break;
            case 7:
                enregistrerDemande();
                break;
            case 8:
                afficherDemandes();
                break;
            case 9:
                attribuerChambre();
                break;
            case 10:
                enregistrerDepart();
                break;
            case 11:
                afficherAttributionsActives();
                break;
            case 12:
                afficherHistorique();
                break;
            case 13:
                afficherStatistiques();
                break;
            case 0:
                printf("Fin du programme.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    return 0;
}
