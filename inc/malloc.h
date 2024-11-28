#ifndef MALLOC_H
#define MALLOC_H

# include "../libft/libft.h"

# include <sys/mman.h>
# include <sys/resource.h>


# define TINY_ZONE_SIZE (16 * sysconf(_SC_PAGESIZE))
# define SMALL_ZONE_SIZE (64 * sysconf(_SC_PAGESIZE))
# define TINY_THRESHOLD 512
# define SMALL_THRESHOLD 2048

# define ALIGN(x) (((((x) - 1) >> 4) << 4) + 16) // 16 bytes align

typedef struct BlockMeta {
    size_t size;                      
    char free;                        
    struct BlockMeta* next;         
    struct BlockMeta* prev;   
} BlockMeta;

typedef struct MemoryZone {
    BlockMeta* free_list;          
    size_t zone_size;              
    struct MemoryZone* next;        
    struct MemoryZone* prev;          
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
void    show_alloc_mem_hex();

char malloc_shrink_block(BlockMeta* block, size_t size);

#endif