#include "malloc.h"

/// Function that check if the pointer belongs to the zone and a block
static int is_pointer_in_zone(MemoryZone *zone, void *ptr)
{
    while (zone)
    {
        BlockMeta *block = zone->free_list;
        while (block)
        {
            void *block_content = (void *)(block + 1);
            if (ptr == block_content)
            {
                return 1;
            }
            block = block->next;
        }
        zone = zone->next;
    }
    return 0;
}

// Realloc implementation
void* realloc(void* ptr, size_t size) {
    if (!ptr) {
        return malloc(size);
    }
    if (size == 0) {
        free(ptr);
        return NULL;
    }
    size = ALIGN(size);
    // Check if ptr belongs to a zone
    if (!is_pointer_in_zone(memory_zones.tiny_zone, ptr) && !is_pointer_in_zone(memory_zones.small_zone, ptr)
        && !is_pointer_in_zone(memory_zones.large_allocations, ptr)) {
        return NULL;
    }
    BlockMeta* block = (BlockMeta*)ptr - 1;
    size_t current_size = block->size;
    if (size == current_size) {
        return ptr;
    }
    if (size < current_size) {
        malloc_shrink_block(block, size);
        return ptr;
    }
    // Allocate a new block with the required size
    void* new_ptr = malloc(size);
    if (!new_ptr) {
        return NULL;
    }
    ft_memcpy(new_ptr, ptr, current_size);
    free(ptr);
    return new_ptr;
}
