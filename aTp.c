#include <stdio.h>
#include <stdint.h>

void print_ptr(void* ptr) {
    uintptr_t ptr_val = (uintptr_t)ptr;
    int bits = sizeof(uintptr_t) * 8;

    printf("Printing pointer with %d bits: \n", bits);

    for (int i = 0; i < bits; i++ ) {
        int bit_i = (ptr_val & (1ULL << i)) >> i;
        printf("%d", bit_i);
    }
    printf("\n");
}

int main() {
    int x = 5; 
    int* ptr = &x; 

    printf("%p\n", ptr);
    print_ptr(ptr);

    return 0;
}

