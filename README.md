# README - Implémentation d'un Allocateur Mémoire

DOGHMANE Amine, M1 CHPS

## Description

Ce projet implémente un allocateur mémoire personnalisé en C, offrant les fonctionnalités de base d'allocation (équivalent à `malloc`) et de libération (équivalent à `free`).

### Fonctionnalités principales

- **`my_malloc(size_t size)`** : Alloue un bloc mémoire de la taille demandée.
- **`my_free(void* ptr)`** : Libère un bloc mémoire précédemment alloué.

### Optimisations implémentées

1. **Segmentation en classes de tailles**

   - Les blocs libres sont organisés en différentes classes basées sur des puissances de deux.
   - Cette segmentation permet une allocation et une libération plus rapides.

2. **Best Fit**

   - Lorsqu'un bloc libre est recherché, l'allocateur sélectionne le bloc dont la taille est la plus proche de celle demandée.

3. **Recyclage des blocs libérés**

   - Les blocs libérés sont réinsérés dans leurs listes correspondantes pour être réutilisés ultérieurement.
   - Cela réduit les appels à `mmap`.

4. **Alignement des blocs**

   - Tous les blocs sont alignés sur 16 octets pour des performances optimales sur les architectures modernes.

### Structure des fichiers

- **allocator.c** : Contient l'implémentation des fonctions `my_malloc` et `my_free`.
- **allocator.h** : Définit les structures et les prototypes des fonctions.
- **test\_allocator.c** : Fichier de test validant le bon fonctionnement de l'allocateur.
- **Makefile** : Fichier de construction permettant de compiler et d'exécuter le projet facilement.

## Instructions de Compilation et d'Exécution

   ```bash
   make
   ```
   Cela générera un exécutable nommé `test_allocator`.

   Pour exécuter les tests, utilisez la commande :
   ```bash
   make run
   ```

   Pour supprimer les fichiers compilés, utilisez la commande :
  ```bash
  make clean
  ```

## Résultats des Tests

Tous les tests sont inclus dans `test_allocator.c`.

1. Stratégie Best Fit (Test 1).
2. Recyclage des blocs libérés (Test 2).
3. Segmentation en classes de tailles (Test 3).
4. Alignement des blocs (Test 4).
5. Test de stress à grande échelle (Test 5).



