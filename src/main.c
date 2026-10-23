#include <stdio.h>
#include "colis.h"
#include "tri.h"
#include "camion.h"

int main(void)
{
    ListeColis liste;
    liste_init(&liste);

    Colis exemple[] = {
        {101,  8, 20, 2, "Paris"},
        {102,  3, 10, 5, "Lille"},
        {103, 12, 40, 1, "Lyon"},
        {104,  5, 25, 4, "Paris"},
        {105,  2, 15, 3, "Lille"},
    };
    for (int i = 0; i < 5; i++) {
        if (ajouter_colis(&liste, exemple[i]) != 0) {
            printf("Erreur lors de l'ajout du colis %d\n", exemple[i].id);
        }
    }

    liste_afficher(&liste);

    int pos = rechercher_id(&liste, 103);
    if (pos != -1) {
        printf("\nColis 103 trouve :\n");
        colis_afficher(liste.tab[pos]);
    }
    printf("Colis 999 : %s\n", rechercher_id(&liste, 999) == -1 ? "introuvable" : "trouve");

    Colis doublon = {101, 1, 1, 1, "Nice"};
    Colis invalide = {200, 0, 10, 1, "Nice"};
    printf("Ajout doublon 101 : code %d\n", ajouter_colis(&liste, doublon));
    printf("Ajout poids 0     : code %d\n", ajouter_colis(&liste, invalide));

    printf("\nTri par poids :\n");
    tri_fusion(&liste, comparer_poids);
    liste_afficher(&liste);

    printf("\nTri par valeur :\n");
    tri_fusion(&liste, comparer_valeur);
    liste_afficher(&liste);

    printf("\nTri par priorite :\n");
    tri_fusion(&liste, comparer_priorite);
    liste_afficher(&liste);

    ListeColis chargement;
    liste_init(&chargement);

    int capacite = 20;
    if (remplir_camion(&liste, capacite, 0, &chargement) == 0) {
        printf("\nChargement pour %d kg :\n", capacite);
        liste_afficher(&chargement);
        printf("Poids %d / %d kg, valeur %d\n", poids_total(&chargement), capacite, valeur_totale(&chargement));
    }

    ListeColis sujet;
    liste_init(&sujet);
    Colis abcd[] = {
        {1, 8, 20, 5, "A"},
        {2, 6, 25, 1, "B"},
        {3, 5, 18, 4, "C"},
        {4, 4, 14, 3, "D"},
    };
    for (int i = 0; i < 4; i++) {
        ajouter_colis(&sujet, abcd[i]);
    }
    capacite = 9;
    for (int avec_priorite = 0; avec_priorite <= 1; avec_priorite++) {
        if (remplir_camion(&sujet, capacite, avec_priorite, &chargement) == 0) {
            printf("\nExemple A/B/C/D, %d kg, %s :\n", capacite, avec_priorite ? "avec priorite" : "valeur seule");
            liste_afficher(&chargement);
            printf("Poids %d / %d kg, valeur %d\n", poids_total(&chargement), capacite, valeur_totale(&chargement));
        }
    }

    liste_liberer(&sujet);
    liste_liberer(&chargement);
    liste_liberer(&liste);
    return 0;
}
