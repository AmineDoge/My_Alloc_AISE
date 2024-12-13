#include <stdio.h>
#include <stdint.h>
#include "allocator.h"

// Fonction utilitaire pour vérifier l'alignement
int is_aligned(void* ptr, size_t alignment) {
    return ((uintptr_t)ptr % alignment) == 0;
}

int main() {

    // Test 1: Allocation Best Fit
    printf("\n=== Test 1: Allocation Best Fit ===\n");
    void* f = my_malloc(50);  
    void* g = my_malloc(100); 
    void* h = my_malloc(200);
    printf("Bloc f: %p (50 octets)\n", f);
    printf("Bloc g: %p (100 octets)\n", g);
    printf("Bloc h: %p (200 octets)\n", h);

    my_free(f);
    my_free(g);
    my_free(h);

    void* i = my_malloc(60); 
    void* j = my_malloc(110); 
    void* k = my_malloc(210); 
    printf("Bloc i (réutilisé): %p (60 octets)\n", i);
    printf("Bloc j (réutilisé): %p (110 octets)\n", j);
    printf("Bloc k (réutilisé): %p (210 octets)\n", k);

    my_free(i);
    my_free(j);
    my_free(k);

    // Test 2: Recyclage des blocs libérés
    printf("\n=== Test 2: Recyclage des blocs libérés ===\n");
    void* d = my_malloc(15); 
    void* e = my_malloc(25); 
    printf("Bloc d (réutilisé): %p (15 octets)\n", d);
    printf("Bloc e (réutilisé): %p (25 octets)\n", e);
    my_free(d);
    my_free(e);

    // Test 3: Allocation avec segmentation par tailles
    printf("\n=== Test 3: Allocation avec segmentation par tailles ===\n");
    void* a = my_malloc(10); 
    void* b = my_malloc(20); 
    void* c = my_malloc(70); 
    printf("Bloc a: %p (10 octets)\n", a);
    printf("Bloc b: %p (20 octets)\n", b);
    printf("Bloc c: %p (70 octets)\n", c);
    my_free(a);
    my_free(b);
    my_free(c);

    // Test 4: Allocation simple et alignement
    printf("\n=== Test 3: Allocation simple et alignement ===\n");
    void* ptr1 = my_malloc(10);
    printf("Adresse de ptr1: %p (10 octets)\n", ptr1);
    if (is_aligned(ptr1, 16)) {
        printf("\tAlignement respect\u00e9\n");
    } else {
        printf("\tErreur: Alignement non respect\u00e9\n");
    }
    my_free(ptr1);

    
    // Test 5: Stress test
    printf("\n=== Test 5: Stress test ===\n");
    void* stress_blocks[1000];
    for (int n = 0; n < 1000; n++) {
        stress_blocks[n] = my_malloc(16 + (n % 256));
    }
    for (int n = 0; n < 1000; n++) {
        my_free(stress_blocks[n]);
    }
    printf("Stress test pass\u00e9\n");

    return 0;
}
