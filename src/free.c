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

static char is_free_block(BlockMeta *block)
{
    while (block)
    {
        if (!block->free)
        {
            return 0;
        }
        block = block->next;
    }
    return 1;
}

static void remove_one_zone(MemoryZone **zone_head, MemoryZone *zone)
{
    if (zone->prev)
    {
        zone->prev->next = zone->next;
        if (zone->next)
        {
            zone->next->prev = zone->prev;
        }
    }
    else
    {
        *zone_head = zone->next;
        if (zone->next)
        {
            zone->next->prev = NULL;
        }
    }
}

// Function that give back the zone to the system if all blocks are free
static void free_zone(MemoryZone **zone_head)
{
    if (!zone_head || !*zone_head)
        return;

    MemoryZone *zone = *zone_head;
    MemoryZone *temp = NULL;

    while (zone)
    {
        // Check if all blocks are free

        if (!is_free_block(zone->free_list))
        {
            zone = zone->next;
            continue;
        }
        // All blocks are free, release the zone
        remove_one_zone(zone_head, zone);
        temp = zone->next;
        munmap(zone, zone->zone_size);
        zone = temp;
    }
}

// Merge adjacent free blocks
static void coalesce_blocks(BlockMeta *block)
{
    // Coalesce with the previous block
    if (block->prev && block->prev->free)
    {
        block->prev->size += BLOCK_META_SIZE + block->size;
        block->prev->next = block->next;
        if (block->next)
        {
            block->next->prev = block->prev;
        }
        block = block->prev;
    }
    // Coalesce with the next blocks
    while (block->next && block->next->free)
    {
        block->size += BLOCK_META_SIZE + block->next->size;
        block->next = block->next->next;
    }
}

// Free a block within a zone
static void free_in_zone(MemoryZone **zone_head, void *ptr)
{
    if (!*zone_head || !ptr)
        return;

    // Locate the block metadata (which is right before the allocated memory)
    BlockMeta *block = (BlockMeta *)ptr - 1;

    block->free = 1;

    // Coalesce adjacent free blocks here
    coalesce_blocks(block);

    // Check if the zone can be released
    free_zone(zone_head);
}

// Main free function
void free(void *ptr)
{
    if (!ptr)
    {
        return;
    }
    if (is_pointer_in_zone(memory_zones.tiny_zone, ptr))
    {
        free_in_zone(&memory_zones.tiny_zone, ptr);
        return;
    }
    if (is_pointer_in_zone(memory_zones.small_zone, ptr))
    {
        free_in_zone(&memory_zones.small_zone, ptr);
        return;
    }
    if (is_pointer_in_zone(memory_zones.large_allocations, ptr))
    {
        free_in_zone(&memory_zones.large_allocations, ptr);
        return;
    }
}
