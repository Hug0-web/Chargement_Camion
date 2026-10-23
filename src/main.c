#include <stdio.h>
#include <string.h>
#include "colis.h"
#include "tri.h"
#include "camion.h"

static void vider_ligne(const char *ligne)
{
    if (strchr(ligne, '\n') == NULL) {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
        }
    }
}

static int lire_entier(const char *message)
{
    char ligne[64];
    int valeur;
    char reste;

    while (1) {
        printf("%s", message);
        if (fgets(ligne, sizeof(ligne), stdin) == NULL) {
            return 0;
        }
        vider_ligne(ligne);
        if (sscanf(ligne, "%d %c", &valeur, &reste) == 1) {
            return valeur;
        }
        printf("Veuillez saisir un nombre entier.\n");
    }
}

static void lire_texte(const char *message, char *dest, int taille)
{
    printf("%s", message);
    if (fgets(dest, taille, stdin) == NULL) {
        dest[0] = '\0';
        return;
    }
    vider_ligne(dest);
    dest[strcspn(dest, "\n")] = '\0';
}

static void afficher_menu(void)
{
    printf("\n===== GESTION DES LIVRAISONS =====\n");
    printf("1. Afficher les colis\n");
    printf("2. Ajouter un colis\n");
    printf("3. Rechercher un colis\n");
    printf("4. Organiser les colis\n");
    printf("5. Preparer un camion\n");
    printf("6. Afficher le chargement\n");
    printf("7. Afficher les statistiques\n");
    printf("0. Quitter\n");
}

static void menu_ajouter(ListeColis *liste)
{
    Colis c;
    c.id = lire_entier("Identifiant : ");
    c.poids = lire_entier("Poids (kg) : ");
    c.valeur = lire_entier("Valeur : ");
    c.priorite = lire_entier("Priorite (1 = plus urgente, 5 = moins urgente) : ");
    lire_texte("Destination : ", c.destination, sizeof(c.destination));

    switch (ajouter_colis(liste, c)) {
        case 0:  printf("Colis ajoute.\n"); break;
        case -1: printf("Erreur : plus de memoire.\n"); break;
        case -2: printf("Erreur : l'identifiant %d existe deja.\n", c.id); break;
        default: printf("Erreur : donnees invalides (poids > 0, valeur >= 0, priorite 1 a 5, destination non vide).\n");
    }
}

static void menu_rechercher(const ListeColis *liste)
{
    int id = lire_entier("Identifiant recherche : ");
    int pos = rechercher_id(liste, id);
    if (pos == -1) {
        printf("Colis %d introuvable.\n", id);
    } else {
        printf("%6s %6s %7s %5s   %s\n", "ID", "Poids", "Valeur", "Prio", "Destination");
        colis_afficher(liste->tab[pos]);
    }
}

static void menu_organiser(ListeColis *liste)
{
    printf("1. Par poids (croissant)\n");
    printf("2. Par valeur (decroissante)\n");
    printf("3. Par priorite (1 en premier)\n");
    int choix = lire_entier("Choix : ");

    Comparateur comparer;
    if (choix == 1) {
        comparer = comparer_poids;
    } else if (choix == 2) {
        comparer = comparer_valeur;
    } else if (choix == 3) {
        comparer = comparer_priorite;
    } else {
        printf("Choix invalide.\n");
        return;
    }

    if (tri_fusion(liste, comparer) != 0) {
        printf("Erreur : plus de memoire.\n");
        return;
    }
    liste_afficher(liste);
}

static void afficher_bilan_camion(const ListeColis *chargement, int capacite)
{
    printf("%d colis, poids %d / %d kg, valeur %d\n",
           chargement->taille, poids_total(chargement), capacite, valeur_totale(chargement));
}

static void afficher_statistiques(const ListeColis *liste, const ListeColis *chargement,
                                  int camion_prepare, int capacite)
{
    int par_priorite[6] = {0};
    for (int i = 0; i < liste->taille; i++) {
        par_priorite[liste->tab[i].priorite]++;
    }

    printf("Nombre de colis : %d\n", liste->taille);
    printf("Poids total     : %d kg\n", poids_total(liste));
    printf("Valeur totale   : %d\n", valeur_totale(liste));
    for (int p = 1; p <= 5; p++) {
        printf("Priorite %d      : %d colis\n", p, par_priorite[p]);
    }

    printf("Camion          : ");
    if (camion_prepare) {
        afficher_bilan_camion(chargement, capacite);
    } else {
        printf("non prepare\n");
    }
}

int main(void)
{
    ListeColis liste;
    ListeColis chargement;
    liste_init(&liste);
    liste_init(&chargement);

    Colis exemple[] = {
        {101,  8, 20, 2, "Paris"},
        {102,  3, 10, 5, "Lille"},
        {103, 12, 40, 1, "Lyon"},
        {104,  5, 25, 4, "Paris"},
        {105,  2, 15, 3, "Lille"},
    };
    for (int i = 0; i < 5; i++) {
        ajouter_colis(&liste, exemple[i]);
    }

    int camion_prepare = 0;
    int capacite = 0;
    int choix;

    do {
        afficher_menu();
        choix = lire_entier("Choix : ");
        printf("\n");

        switch (choix) {
            case 1:
                liste_afficher(&liste);
                break;
            case 2:
                menu_ajouter(&liste);
                break;
            case 3:
                menu_rechercher(&liste);
                break;
            case 4:
                menu_organiser(&liste);
                break;
            case 5: {
                int cap = lire_entier("Capacite du camion (kg) : ");
                if (cap <= 0) {
                    printf("La capacite doit etre positive.\n");
                    break;
                }
                int avec_priorite = lire_entier("Tenir compte de la priorite ? (0 = non, 1 = oui) : ");
                if (remplir_camion(&liste, cap, avec_priorite != 0, &chargement) != 0) {
                    printf("Erreur : plus de memoire (capacite trop grande ?).\n");
                    camion_prepare = 0;
                    break;
                }
                capacite = cap;
                camion_prepare = 1;
                printf("Camion prepare : ");
                afficher_bilan_camion(&chargement, capacite);
                break;
            }
            case 6:
                if (!camion_prepare) {
                    printf("Aucun camion prepare (utilisez l'option 5).\n");
                } else {
                    liste_afficher(&chargement);
                    afficher_bilan_camion(&chargement, capacite);
                }
                break;
            case 7:
                afficher_statistiques(&liste, &chargement, camion_prepare, capacite);
                break;
            case 0:
                printf("Au revoir.\n");
                break;
            default:
                printf("Choix invalide.\n");
        }
    } while (choix != 0);

    liste_liberer(&chargement);
    liste_liberer(&liste);
    return 0;
}
