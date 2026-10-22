#ifndef COLIS_H
#define COLIS_H

typedef struct {
    int  id;
    int  poids;         
    int  valeur;
    int  priorite;
    char destination[32];
} Colis;


typedef struct {
    Colis *tab;      
    int    taille;   
    int    capacite;    
} ListeColis;


void liste_init(ListeColis *l);
int  liste_ajouter(ListeColis *l, Colis c);
void liste_liberer(ListeColis *l);

void colis_afficher(Colis c);
void liste_afficher(const ListeColis *l);
int  rechercher_id(const ListeColis *l, int id);
int  ajouter_colis(ListeColis *l, Colis c);


#endif
