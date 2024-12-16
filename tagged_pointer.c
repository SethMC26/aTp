#include <stdio.h>
#include <stdint.h>


/**
 * Prints out bits of pointer for debugging 
 */
void print_ptr(void* ptr) {
    //gets the ptr value 
    uintptr_t ptr_val = (uintptr_t)ptr;
    int bits = sizeof(uintptr_t) * 8;

    //printf("Printing pointer with %d bits: \n", bits);
    
    //if i could catch bits in a bottle...
    for (int i = bits-1; i > 0; i-- ) {
        if (i % 8 == 0) {
            printf(" ");
        }

        int bit_i = (ptr_val & (1ULL << i)) >> i;
        printf("%d", bit_i);
    }
    printf("\n");
}

/**
 * Sets tag to a pointer
 * @param ptr void * pointer to set tag
 * @param tag short of bits to set(16 max)
 * 
 * @returns void * new pointer with tag
 */
void* set_tag(void* ptr, short tag) {
    //get pointer as a value we can manipulate
    uintptr_t ptr_val = (uintptr_t)ptr;

    int ptr_len = (sizeof(uintptr_t) * 8);
    int tag_len = (sizeof(tag) * 8);
    
    //set tag by OR-ing bits 48-63 with our tag
    ptr_val |= (uintptr_t)tag << (ptr_len - tag_len);

    return (void *)ptr_val;
}

/**
 * Remove tag from pointer, this operation MUST be preformed before derefrencing pointer 
 * @param ptr void* pointer to remove tag from 
 * 
 * @return void* new pointer with tag removed 
 */
void* remove_tag(void* ptr) {
    //get pointer as a value we can manipulate
    uintptr_t ptr_val = (uintptr_t)ptr;
    
    int ptr_len = (sizeof(uintptr_t) * 8);
    int tag_len = (sizeof(short) * 8);

    //create mask to reset bits in the pointer field (bits 48 to 63)
    uintptr_t mask = ~((uintptr_t)0xFFFF << (ptr_len - tag_len));
    //zero out all tag bits (bits 48 and up)
    ptr_val &= mask; 

    return (void*)ptr_val;
}

/**
 * Reads tag data from a tagged pointer 
 * 
 * @param ptr void * pointer to read tag of 
 */
short read_tag(void* ptr) {
    uintptr_t ptr_val = (uintptr_t)ptr;
    
    int ptr_len = (sizeof(uintptr_t) * 8);
    int tag_len = (sizeof(short) * 8);

    //create mask to get bits of tag (bits 48-63)
    uintptr_t mask = (uintptr_t)0xFFFF << (ptr_len - tag_len);
    
    //keep only the bits of tha tag itself everything is zeroed out 
    ptr_val &= mask;
    //shift bits back right so we can get correct bits 
    ptr_val = ptr_val >> (ptr_len - tag_len);
    //we can saftey cast to a short since all truncated bits got zeroed out by mask
    return (short) ptr_val;
}   

int main() {
    if ((sizeof(uintptr_t) * 8 < 64)) {
        fprintf(stderr, "Critical error poitners must be 64 bits your pointer was %ld", (sizeof(uintptr_t) * 8));
        return 1;
    }

    int x = 5; 
    int* ptr = &x; 
    short test_tag = 42;

    printf("Orginal pointer\n");
    print_ptr(ptr);

    printf("\nPointer with tag\n");
    //set tag
    void * tag_ptr = set_tag(ptr, test_tag);
    print_ptr(tag_ptr);

    printf("\nTag from pointer\n");
    //read tag from pointer
    short tag = read_tag(tag_ptr);
    printf("Tag is %hd\n", tag);

    printf("\nPointer with tag removed\n");
    //remove tag so we can derefrence pointer
    void * org_ptr = remove_tag(tag_ptr);
    print_ptr(org_ptr);

    //get orginal data from pointer to prove we have not modified pointer
    printf("orginal data:%d\n", *(int *)org_ptr);
    return 0;
}

