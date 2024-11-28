#include "malloc.h"
#include <bits/mman-linux.h>

MemoryZoneList memory_zones = {
    .tiny_zone = NULL,
    .small_zone = NULL,
    .large_allocations = NULL
};

static BlockMeta* find_free_block(MemoryZone* zone, size_t size) {
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
char malloc_shrink_block(BlockMeta* block, size_t size) {
    if (block->size <= size + BLOCK_META_SIZE) {
        return 0;
    }
    BlockMeta* new_block = (BlockMeta*)((char*)(block + 1) + size);
    new_block->size = block->size - size - BLOCK_META_SIZE;
    new_block->free = 1;
    new_block->next = block->next;
    if (new_block->next) {
        new_block->next->prev = new_block;
    }
    new_block->prev = block;
    block->size = size;
    block->next = new_block;
    block->free = 0;
    free(new_block + 1); // Free the new block to merge it with the next one
    return 1;
}

/// Function that check if the size of memory which is requested is valid
/// regarding the system limits
static int is_valid_size(size_t size)
{
    struct rlimit limit;
    getrlimit(RLIMIT_AS, &limit);
    if (size > (size_t)limit.rlim_cur)
    {
        return 0;
    }
    return 1;
}

// Initialize a new zone for TINY or SMALL allocations
static MemoryZone* init_memory_zone(size_t zone_size, size_t block_size) {
    if (!is_valid_size(zone_size)) {
        return NULL;
    }
    void* memory = mmap(NULL, zone_size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (memory == MAP_FAILED) {
        return NULL;
    }
    
    MemoryZone* zone = (MemoryZone*)memory;
    zone->zone_size = zone_size;
    zone->free_list = (BlockMeta*)((char*)memory + MEMORY_ZONE_SIZE);
    zone->free_list->size = zone_size - MEMORY_ZONE_SIZE - BLOCK_META_SIZE;
    zone->free_list->free = 1;
    zone->free_list->next = NULL;
    zone->free_list->prev = NULL;
    zone->next = NULL;
    zone->prev = NULL;

    // Split the block if it's too large
    malloc_shrink_block(zone->free_list, block_size);
    
    return zone;
}

static void* allocate_in_zone(MemoryZone** zone_head, size_t size, size_t zone_size) {
    MemoryZone* zone = *zone_head;

    // Find a free block
    while (zone != NULL) {
        BlockMeta* block = find_free_block(zone, size);
        if (block) {
            malloc_shrink_block(block, size);
            block->free = 0;
            return (void*)(block + 1); // Return pointer after metadata
        }
        zone = zone->next;
    }

    // No free block found, create a new zone
    zone = init_memory_zone(zone_size, size);
    if (!zone) {
        return NULL;
    }
    if (*zone_head == NULL) {
        *zone_head = zone;
    } else {
        MemoryZone* temp = *zone_head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = zone;
        zone->prev = temp;
    }

    zone->free_list->free = 0;
    return (void*)(zone->free_list + 1); // Return pointer after metadata
}

void* malloc(size_t size) {
    if (!size) {
        return NULL;
    }
    size = ALIGN(size);
    if (size <= TINY_THRESHOLD) {
        return allocate_in_zone(&memory_zones.tiny_zone, size, TINY_ZONE_SIZE);
    } else if (size <= SMALL_THRESHOLD) {
        return allocate_in_zone(&memory_zones.small_zone, size, SMALL_ZONE_SIZE);
    } else {
        size_t total_size = ALIGN(size + MEMORY_ZONE_SIZE + BLOCK_META_SIZE);
        return allocate_in_zone(&memory_zones.large_allocations, size, total_size);
    }
}
