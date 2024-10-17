#include "../inc/malloc.h"

MemoryZone* tiny_zone = NULL;
MemoryZone* small_zone = NULL;
MemoryZone* large_allocations = NULL;

BlockMeta* find_free_block(MemoryZone* zone, size_t size) {
    BlockMeta* current = zone->free_list;
    while (current != NULL) {
        if (current->free && current->size >= size) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

// shrink a block for the required size
char shrink_block(BlockMeta* block, size_t size) {
    if (block->size <= size + BLOCK_META_SIZE) {
        return 0;
    }
    BlockMeta* new_block = (BlockMeta*)((char*)(block + 1) + size);
    new_block->size = block->size - size - BLOCK_META_SIZE;
    new_block->free = 1;
    new_block->next = block->next;
    block->size = size;
    block->next = new_block;
    return 1;
}

// Initialize a new zone for TINY or SMALL allocations
MemoryZone* init_memory_zone(size_t zone_size, size_t block_size) {
    void* memory = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANON | MAP_PRIVATE, -1, 0);
    if (memory == MAP_FAILED) {
        return NULL;
    }
    
    MemoryZone* zone = (MemoryZone*)memory;
    zone->zone_size = zone_size;
    zone->free_list = (BlockMeta*)((char*)memory + MEMORY_ZONE_SIZE);
    zone->free_list->size = zone_size - MEMORY_ZONE_SIZE - BLOCK_META_SIZE;
    zone->free_list->free = 1;
    zone->free_list->next = NULL;
    zone->next = NULL;

    // Split the block if it's too large
    shrink_block(zone->free_list, block_size);
    
    return zone;
}

void* allocate_in_zone(MemoryZone** zone_head, size_t size, size_t zone_size) {
    MemoryZone* zone = *zone_head;

    // Find a free block
    while (zone != NULL) {
        BlockMeta* block = find_free_block(zone, size);
        if (block) {
            shrink_block(block, size);
            block->free = 0;
            return (void*)(block + 1); // Return pointer after metadata
        }
        zone = zone->next;
    }

    // No free block found, create a new zone
    zone = init_memory_zone(zone_size, size);
    if (!zone) {
        return NULL; // Failed to create a new zone
    }
    if (*zone_head == NULL) {
        *zone_head = zone;
    } else {
        MemoryZone* temp = *zone_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = zone;
    }

    zone->free_list->free = 0;
    return (void*)(zone->free_list + 1); // Return pointer after metadata
}

void* malloc(size_t size) {
    if (!size) {
        return NULL;
    }
    
    if (size <= TINY_THRESHOLD) {
        // Handle TINY allocation
        return allocate_in_zone(&tiny_zone, size, TINY_ZONE_SIZE);
    } else if (size <= SMALL_THRESHOLD) {
        // Handle SMALL allocation
        return allocate_in_zone(&small_zone, size, SMALL_ZONE_SIZE);
    } else {
        // Handle LARGE allocation (mmap directly)
        size_t total_size = size + MEMORY_ZONE_SIZE + BLOCK_META_SIZE;
        return allocate_in_zone(&large_allocations, size, total_size);
    }
}
