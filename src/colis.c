#include <stdio.h>
#include <stdlib.h>
#include "colis.h"

#define CAPACITE_INITIALE 16


void liste_init(ListeColis *l)
{
    l->tab = malloc(CAPACITE_INITIALE * sizeof(Colis));
    l->taille = 0;
    l->capacite = (l->tab != NULL) ? CAPACITE_INITIALE : 0;
}


int liste_ajouter(ListeColis *l, Colis c)
{
    if (l->taille == l->capacite) {
        int nouvelle_capacite = (l->capacite == 0) ? CAPACITE_INITIALE : l->capacite * 2;
        Colis *nouveau = realloc(l->tab, nouvelle_capacite * sizeof(Colis));
        if (nouveau == NULL) {
            return -1;              
        }
        l->tab = nouveau;
        l->capacite = nouvelle_capacite;
    }
    l->tab[l->taille] = c;
    l->taille++;
    return 0;
}

void liste_liberer(ListeColis *l)
{
    free(l->tab);
    l->tab = NULL;
    l->taille = 0;
    l->capacite = 0;
}

void colis_afficher(Colis c)
{
    printf("%6d %6d %7d %5d   %s\n", c.id, c.poids, c.valeur, c.priorite, c.destination);
}

void liste_afficher(const ListeColis *l)
{
    if (l->taille == 0) {
        printf("Aucun colis.\n");
        return;
    }
    printf("%6s %6s %7s %5s   %s\n", "ID", "Poids", "Valeur", "Prio", "Destination");
    for (int i = 0; i < l->taille; i++) {
        colis_afficher(l->tab[i]);
    }
}

int rechercher_id(const ListeColis *l, int id)
{
    for (int i = 0; i < l->taille; i++) {
        if (l->tab[i].id == id) {
            return i;
        }
    }
    return -1;
}

int ajouter_colis(ListeColis *l, Colis c)
{
    if (c.poids <= 0 || c.valeur < 0 || c.priorite < 1 || c.priorite > 5) {
        return -3;
    }
    if (rechercher_id(l, c.id) != -1) {
        return -2;
    }
    return liste_ajouter(l, c);
}
