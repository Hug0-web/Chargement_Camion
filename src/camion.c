#include <stdlib.h>
#include "camion.h"

int remplir_camion(const ListeColis *colis, int capacite, ListeColis *chargement)
{
    int n = colis->taille;
    int largeur = capacite + 1;

    chargement->taille = 0;
    if (capacite < 0) {
        return 0;
    }

    int *meilleur = malloc((size_t)(n + 1) * largeur * sizeof(int));
    if (meilleur == NULL) {
        return -1;
    }

    for (int w = 0; w <= capacite; w++) {
        meilleur[w] = 0;
    }

    for (int i = 1; i <= n; i++) {
        Colis c = colis->tab[i - 1];
        int *ligne = &meilleur[(size_t)i * largeur];
        int *precedente = &meilleur[(size_t)(i - 1) * largeur];

        for (int w = 0; w <= capacite; w++) {
            ligne[w] = precedente[w];
            if (c.poids <= w && precedente[w - c.poids] + c.valeur > ligne[w]) {
                ligne[w] = precedente[w - c.poids] + c.valeur;
            }
        }
    }

    int w = capacite;
    for (int i = n; i >= 1; i--) {
        if (meilleur[(size_t)i * largeur + w] != meilleur[(size_t)(i - 1) * largeur + w]) {
            if (liste_ajouter(chargement, colis->tab[i - 1]) != 0) {
                free(meilleur);
                return -1;
            }
            w -= colis->tab[i - 1].poids;
        }
    }

    free(meilleur);
    return 0;
}

int poids_total(const ListeColis *l)
{
    int total = 0;
    for (int i = 0; i < l->taille; i++) {
        total += l->tab[i].poids;
    }
    return total;
}

int valeur_totale(const ListeColis *l)
{
    int total = 0;
    for (int i = 0; i < l->taille; i++) {
        total += l->tab[i].valeur;
    }
    return total;
}
