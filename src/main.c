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
        if (liste_ajouter(&liste, exemple[i]) != 0) {
            printf("Erreur : plus de memoire\n");
            liste_liberer(&liste);
            return 1;
        }
    }

    
    printf("%d colis (capacite reservee : %d)\n", liste.taille, liste.capacite);
    for (int i = 0; i < liste.taille; i++) {
        Colis c = liste.tab[i];
        printf("%d  %d kg  valeur %d  prio %d  %s\n",
               c.id, c.poids, c.valeur, c.priorite, c.destination);
    }

    liste_liberer(&liste);
    return 0;
}
