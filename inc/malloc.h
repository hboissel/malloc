#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/libft.h"

# include <sys/mman.h>
# include <sys/resource.h>


# define TINY_ZONE_SIZE (16 * sysconf(_SC_PAGESIZE))  // Size of a TINY zone
# define SMALL_ZONE_SIZE (64 * sysconf(_SC_PAGESIZE)) // Size of a SMALL zone
# define TINY_THRESHOLD 512              // Max size for TINY allocations
# define SMALL_THRESHOLD 2048            // Max size for SMALL allocations

# define ALIGN(x) (((((x) - 1) >> 4) << 4) + 16) // Align the size to 16 bytes

typedef struct BlockMeta {
    size_t size;                       // Size of the block
    char free;                         // Whether the block is free
    struct BlockMeta* next;            // Next block in the list
    struct BlockMeta* prev;            // Previous block in the list
} BlockMeta;

typedef struct MemoryZone {
    BlockMeta* free_list;              // List of free/used blocks
    size_t zone_size;                  // Total size of the zone
    struct MemoryZone* next;           // Pointer to the next zone
    struct MemoryZone* prev;           // Pointer to the previous zone
} MemoryZone;

typedef struct MemoryZoneList {
    MemoryZone* tiny_zone;
    MemoryZone* small_zone;
    MemoryZone* large_allocations;
} MemoryZoneList;

extern struct MemoryZoneList memory_zones;

# define BLOCK_META_SIZE sizeof(BlockMeta)
# define MEMORY_ZONE_SIZE sizeof(MemoryZone)

void*   malloc(size_t size);
void    free(void* ptr);
void*   realloc(void* ptr, size_t size);
void	*calloc(size_t nmemb, size_t size);

void    show_alloc_mem();
void    show_alloc_mem_ex();

char malloc_shrink_block(BlockMeta* block, size_t size);

#endif