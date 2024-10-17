#include "../inc/malloc.h"


// Helper function to find which zone the pointer belongs to
int is_pointer_in_zone(MemoryZone* zone, void* ptr) {
    while (zone) {
        void* zone_start = (void*)(zone);
        void* zone_end = (void*)((char*)zone + zone->zone_size);
        if (ptr >= zone_start && ptr < zone_end) {
            return 1;
        }
        zone = zone->next;
    }
    return 0;
}

// Function that give back the zone to the system if all blocks are free
void free_zone(MemoryZone** zone) {
    if (!*zone) return;

    // Check if all blocks are free
    BlockMeta* block = (*zone)->free_list;
    while (block) {
        if (!block->free) {
            return; // At least one block is in use
        }
        block = block->next;
    }

    // All blocks are free, release the zone
    munmap(zone, (*zone)->zone_size);
    *zone = NULL;
}

// Merge adjacent free blocks
void coalesce_blocks(BlockMeta* block) {
    while (block->next && block->next->free) {
        block->size += BLOCK_META_SIZE + block->next->size;
        block->next = block->next->next;
    }
}

// Free a block within a zone
void free_in_zone(MemoryZone** zone, void* ptr) {
    if (!*zone || !ptr) return;

    // Locate the block metadata (which is right before the allocated memory)
    BlockMeta* block = (BlockMeta*)ptr - 1;
    
    
    // Mark the block as free
    block->free = 1;

    // Coalesce adjacent free blocks here
    coalesce_blocks(block);

    // Check if the zone can be released
    free_zone(zone);
}

// Main free function
void free(void* ptr) {
    if (!ptr) {
        return;
    }

    // Check if the pointer belongs to TINY zone
    if (is_pointer_in_zone(tiny_zone, ptr)) {
        free_in_zone(&tiny_zone, ptr);
        return;
    }

    // Check if the pointer belongs to SMALL zone
    if (is_pointer_in_zone(small_zone, ptr)) {
        free_in_zone(&small_zone, ptr);
        return;
    }

    // Check if the pointer belongs to LARGE zone
    if (is_pointer_in_zone(large_allocations, ptr)) {
        free_in_zone(&large_allocations, ptr);
        return;
    }
}
