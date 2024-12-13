#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stddef.h> // Pour size_t

// Déclaration de la structure de bloc mémoire
typedef struct Block {
    size_t size;            // Taille du bloc (inclut les métadonnées)
    struct Block* next;     // Pointeur vers le prochain bloc libre
} Block;

// Déclaration des fonctions
void* my_malloc(size_t size);
void my_free(void* ptr);

#endif // ALLOCATOR_H
