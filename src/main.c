#include <stdio.h>
#include "colis.h"

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

    liste_liberer(&liste);
    return 0;
}
