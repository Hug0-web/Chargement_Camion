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
