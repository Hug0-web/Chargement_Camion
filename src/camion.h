#ifndef CAMION_H
#define CAMION_H

#include "colis.h"

int gain(Colis c, int avec_priorite);
int remplir_camion(const ListeColis *colis, int capacite, int avec_priorite, ListeColis *chargement);
int poids_total(const ListeColis *l);
int valeur_totale(const ListeColis *l);


#endif
