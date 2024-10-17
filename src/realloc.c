#include "../inc/malloc.h"

// Helper function to copy memory safely
void* memcpy_safe(void* dest, const void* src, size_t n) {
    char* d = dest;
    const char* s = src;
    while (n--) {
        *d++ = *s++;
    }
    return dest;
}

// Helper function to get the size of the allocated block
size_t get_block_size(void* ptr) {
    if (!ptr) return 0;
    BlockMeta* block = (BlockMeta*)ptr - 1;
    return block->size;
}

// Realloc implementation
void* realloc(void* ptr, size_t new_size) {
    if (!ptr) {
        // If the pointer is NULL, realloc behaves like malloc
        return malloc(new_size);
    }
    
    if (new_size == 0) {
        // If the new size is 0, free the memory and return NULL
        free(ptr);
        return NULL;
    }

    // Get the size of the current block
    BlockMeta* block = (BlockMeta*)ptr - 1;
    size_t current_size = block->size;

    if (new_size <= current_size) {
        // If the new size is smaller or equal to the current block size, just return the same pointer
        return ptr;
    }

    // Allocate a new block with the required size
    void* new_ptr = malloc(new_size);
    if (!new_ptr) {
        return NULL; // Allocation failed
    }

    // Copy the old data to the new block (up to the current size)
    memcpy_safe(new_ptr, ptr, current_size);

    // Free the old block
    free(ptr);

    return new_ptr;
}
