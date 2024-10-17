#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/libft.h"

# include <sys/mman.h>


# define TINY_ZONE_SIZE (4 * sysconf(_SC_PAGESIZE))  // Size of a TINY zone
# define SMALL_ZONE_SIZE (16 * sysconf(_SC_PAGESIZE)) // Size of a SMALL zone
# define TINY_THRESHOLD 128              // Max size for TINY allocations
# define SMALL_THRESHOLD 512            // Max size for SMALL allocations

typedef struct BlockMeta {
    size_t size;                       // Size of the block
    int free;                          // Whether the block is free
    struct BlockMeta* next;            // Next block in the list
} BlockMeta;

typedef struct MemoryZone {
    BlockMeta* free_list;              // List of free/used blocks
    size_t zone_size;                  // Total size of the zone
    struct MemoryZone* next;           // Pointer to the next zone
} MemoryZone;

extern MemoryZone* tiny_zone;
extern MemoryZone* small_zone;
extern MemoryZone* large_allocations;

# define BLOCK_META_SIZE sizeof(BlockMeta)
# define MEMORY_ZONE_SIZE sizeof(MemoryZone)

void*   malloc(size_t size);
void    free(void* ptr);
void*   realloc(void* ptr, size_t new_size);
void	*calloc(size_t nmemb, size_t size);
void    show_alloc_mem();

#endif