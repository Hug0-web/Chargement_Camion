#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "colis.h"
#include "tri.h"
#include "camion.h"

#define NB_RECHERCHES 1000

static double ms_depuis(clock_t debut)
{
    return 1000.0 * (clock() - debut) / CLOCKS_PER_SEC;
}

static Colis colis_aleatoire(int id)
{
    Colis c = {id, 1 + rand() % 50, rand() % 100, 1 + rand() % 5, "Ville"};
    return c;
}

int main(void)
{
    int tailles[] = {100, 1000, 10000, 100000};
    int capacites[] = {50, 500, 5000};
    srand(42);

    printf("%8s | %12s | %16s | %10s", "n", "Ajout n (ms)", "1000 rech. (ms)", "Tri (ms)");
    for (int k = 0; k < 3; k++) {
        printf(" | Sac C=%-4d (ms)", capacites[k]);
    }
    printf("\n");

    for (int t = 0; t < 4; t++) {
        int n = tailles[t];
        ListeColis liste;
        ListeColis chargement;
        liste_init(&liste);
        liste_init(&chargement);

        clock_t debut = clock();
        for (int i = 1; i <= n; i++) {
            ajouter_colis(&liste, colis_aleatoire(i));
        }
        double t_ajout = ms_depuis(debut);

        debut = clock();
        for (int r = 0; r < NB_RECHERCHES; r++) {
            rechercher_id(&liste, -1);
        }
        double t_recherche = ms_depuis(debut);

        debut = clock();
        tri_fusion(&liste, comparer_poids);
        double t_tri = ms_depuis(debut);

        printf("%8d | %12.0f | %16.0f | %10.0f", n, t_ajout, t_recherche, t_tri);

        for (int k = 0; k < 3; k++) {
            debut = clock();
            int res = remplir_camion(&liste, capacites[k], 0, &chargement);
            double t_sac = ms_depuis(debut);
            if (res == 0) {
                printf(" | %15.0f", t_sac);
            } else {
                printf(" | %15s", "memoire insuff.");
            }
        }
        printf("\n");

        liste_liberer(&chargement);
        liste_liberer(&liste);
    }

    printf("\nMemoire du sac a dos = (n+1) x (C+1) x %d octets :\n", (int)sizeof(int));
    for (int t = 0; t < 4; t++) {
        printf("%8d :", tailles[t]);
        for (int k = 0; k < 3; k++) {
            double mo = (double)(tailles[t] + 1) * (capacites[k] + 1) * sizeof(int) / (1024.0 * 1024.0);
            printf("   C=%-4d %9.1f Mo", capacites[k], mo);
        }
        printf("\n");
    }
    return 0;
}
