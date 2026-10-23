#ifndef TRI_H
#define TRI_H

#include "colis.h"

typedef int (*Comparateur)(const Colis *a, const Colis *b);

int comparer_poids(const Colis *a, const Colis *b);
int comparer_valeur(const Colis *a, const Colis *b);
int comparer_priorite(const Colis *a, const Colis *b);

int tri_fusion(ListeColis *l, Comparateur comparer);


#endif
