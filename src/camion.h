#ifndef CAMION_H
#define CAMION_H

#include "colis.h"

int remplir_camion(const ListeColis *colis, int capacite, ListeColis *chargement);
int poids_total(const ListeColis *l);
int valeur_totale(const ListeColis *l);


#endif
