# Gestion des livraisons

Programme en C pour aider une entreprise de livraison à gérer ses colis
et à remplir un camion du mieux possible.

On peut ajouter des colis, les afficher, en retrouver un avec son identifiant,
les trier et préparer le chargement d'un camion
en choisissant les colis qui rapportent le plus sans dépasser sa capacité.

## Pourquoi le C ?

On a choisi le C parce qu'il nous oblige à tout écrire nous-mêmes : le tableau
qui stocke les colis, le tri, le remplissage du camion. Du coup on sait
exactement ce que fait chaque partie et combien elle coûte, ce qui est
justement ce qu'on nous demande d'expliquer dans ce TP.

## Compiler et lancer

Il faut juste `gcc`. Depuis le dossier `src` :

```
gcc -Wall -Wextra -o livraison main.c colis.c tri.c camion.c
./livraison
```

Au lancement, les 5 colis de l'exemple du sujet sont déjà chargés pour pouvoir
tester directement.

Pour relancer les mesures de temps (100 à 100 000 colis) :

```
gcc -Wall -Wextra -o mesures mesures.c colis.c tri.c camion.c
./mesures
```

## Le menu

```
===== GESTION DES LIVRAISONS =====
1. Afficher les colis
2. Ajouter un colis
3. Rechercher un colis
4. Organiser les colis
5. Preparer un camion
6. Afficher le chargement
7. Afficher les statistiques
0. Quitter
```

## Ce qu'il faut savoir

- **Priorité : 1 = le plus urgent, 5 = le moins urgent.**
- Les poids sont en kg et en nombres entiers.
- Deux colis ne peuvent pas avoir le même identifiant.
- Quand on prépare un camion, on peut choisir de tenir compte de la priorité
  ou non. Avec la priorité, chaque colis compte pour
  `valeur × (6 − priorité)` : un colis de priorité 1 compte 5 fois sa valeur,
  un colis de priorité 5 compte juste sa valeur.

## Les fichiers

| Fichier | Ce qu'il contient |
|---|---|
| `src/colis.h` / `colis.c` | Le colis, la liste de colis, l'ajout, l'affichage et la recherche |
| `src/tri.h` / `tri.c` | Le tri fusion et les 3 façons de comparer deux colis |
| `src/camion.h` / `camion.c` | Le remplissage du camion (sac à dos) et la règle de priorité |
| `src/main.c` | Le menu |
| `src/mesures.c` | Le programme qui chronomètre les opérations |
| `rapport.pdf` | Nos choix expliqués, les mesures et les réponses aux questions |
