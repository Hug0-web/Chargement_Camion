#include <stdlib.h>
#include "tri.h"

int comparer_poids(const Colis *a, const Colis *b)
{
    return a->poids - b->poids;
}

int comparer_valeur(const Colis *a, const Colis *b)
{
    return b->valeur - a->valeur;
}

int comparer_priorite(const Colis *a, const Colis *b)
{
    return a->priorite - b->priorite;
}


static void fusionner(Colis *tab, Colis *tmp, int debut, int milieu, int fin, Comparateur comparer)
{
    int i = debut;
    int j = milieu;
    int k = debut;

    while (i < milieu && j < fin) {
        if (comparer(&tab[i], &tab[j]) <= 0) {
            tmp[k++] = tab[i++];
        } else {
            tmp[k++] = tab[j++];
        }
    }
    while (i < milieu) {
        tmp[k++] = tab[i++];
    }
    while (j < fin) {
        tmp[k++] = tab[j++];
    }
    for (k = debut; k < fin; k++) {
        tab[k] = tmp[k];
    }
}

static void tri_fusion_rec(Colis *tab, Colis *tmp, int debut, int fin, Comparateur comparer)
{
    if (fin - debut <= 1) {
        return;
    }
    int milieu = debut + (fin - debut) / 2;
    tri_fusion_rec(tab, tmp, debut, milieu, comparer);
    tri_fusion_rec(tab, tmp, milieu, fin, comparer);
    fusionner(tab, tmp, debut, milieu, fin, comparer);
}

int tri_fusion(ListeColis *l, Comparateur comparer)
{
    if (l->taille <= 1) {
        return 0;
    }
    Colis *tmp = malloc(l->taille * sizeof(Colis));
    if (tmp == NULL) {
        return -1;
    }
    tri_fusion_rec(l->tab, tmp, 0, l->taille, comparer);
    free(tmp);
    return 0;
}
