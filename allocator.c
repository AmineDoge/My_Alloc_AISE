#include "allocator.h"
#include <sys/mman.h>
#include <stdio.h>
#include <string.h>

// Taille minimum et maximum des classes
#define MIN_BLOCK_SIZE 8
#define MAX_BLOCK_SIZE 1024

// Taille d'alignement (16 octets pour cette implémentation)
#define ALIGNMENT 16

// Nombre de classes (par puissances de 2 : 8, 16, 32, ...)
#define NUM_CLASSES 7

// Table des listes libres (segmentation par taille)
static Block* free_list[NUM_CLASSES] = {NULL};

// Fonction utilitaire : Aligner une taille vers le multiple suivant de ALIGNMENT
static size_t align_up(size_t size) {
    return (size + ALIGNMENT - 1) & ~(ALIGNMENT - 1);
}

// Fonction utilitaire : Trouve la classe correspondant à une taille
static int get_class_index(size_t size) {
    size_t block_size = MIN_BLOCK_SIZE;
    int index = 0;

    while (block_size < size && index < NUM_CLASSES - 1) {
        block_size *= 2;
        index++;
    }
    return index;
}

// Fonction my_malloc avec segmentation par tailles et alignement
void* my_malloc(size_t size) {
    // Aligner la taille demandée
    size_t aligned_size = align_up(size + sizeof(Block));

    // Trouve la classe correspondant à la taille demandée
    int class_index = get_class_index(aligned_size);
    Block** current_list = &free_list[class_index];

    // Recherche d'un bloc libre dans la classe
    Block* best_fit = NULL;
    Block** best_fit_prev = NULL;
    Block** current = current_list;
    Block** prev = NULL;

    while (*current != NULL) {
        if ((*current)->size >= aligned_size &&
            (best_fit == NULL || (*current)->size < best_fit->size)) {
            best_fit = *current;
            best_fit_prev = prev;
        }
        prev = current;
        current = &(*current)->next;
    }

    if (best_fit != NULL) {
        // Retirer le bloc de la liste libre
        if (best_fit_prev != NULL) {
            *best_fit_prev = best_fit->next;
        } else {
            *current_list = best_fit->next;
        }

        // Découpage du bloc si nécessaire
        if (best_fit->size >= aligned_size + sizeof(Block)) {
            Block* remaining = (Block*)((char*)best_fit + aligned_size);
            remaining->size = best_fit->size - aligned_size;
            remaining->next = *current_list;
            *current_list = remaining;

            best_fit->size = aligned_size;
        }

        return (void*)(best_fit + 1);
    }

    // Aucun bloc disponible, allocation via mmap
    Block* new_block = mmap(NULL, aligned_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_block == MAP_FAILED) {
        return NULL;
    }
    new_block->size = aligned_size;

    return (void*)(new_block + 1);
}

// Fonction my_free : Libère un bloc et l'ajoute à la classe correspondante
void my_free(void* ptr) {
    if (ptr == NULL) {
        return;
    }

    Block* block = (Block*)ptr - 1;

    // Trouve la classe correspondant à la taille du bloc
    int class_index = get_class_index(block->size);
    Block** current_list = &free_list[class_index];

    // Ajouter le bloc libéré à la liste correspondante
    block->next = *current_list;
    *current_list = block;
}
