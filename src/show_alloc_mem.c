#include "malloc.h"

/// Print a address to the standard output in hexadecimal format
/// Using write function
void print_address_hex(size_t value) {
    char hex[16] = "0123456789abcdef";
    char buffer[16];
    int i = 0;
    while (value > 0) {
        buffer[i++] = hex[value % 16];
        value /= 16;
    }
    write(1, "0x", 2);
    while (i > 0) {
        write(1, &buffer[--i], 1);
    }
}

// Helper function to print blocks in a given zone
void print_zone(const char *zone_name, MemoryZone *zone, size_t *total)
{
    while (zone)
    {
        write(1, zone_name, ft_strlen(zone_name));
        write(1, " : ", 3);
        print_address_hex((size_t)zone);
        write(1, "\n", 1);
        BlockMeta *block = zone->free_list;
        int i = 0;
        while (block)
        {
            void *block_start = (void *)(block + 1);
            void *block_end = (void *)((char *)block_start + block->size);
            ft_putnbr_fd(++i, 1);
            write(1, " - ", 3);
            if (block->free)
            {
                write(1, "\033[0;32m", 7);
            }
            else
            {
                write(1, "\033[0;31m", 7);
            }
            print_address_hex((size_t)block_start);
            write(1, " - ", 3);
            print_address_hex((size_t)block_end);
            write(1, " : ", 3);
            ft_putnbr_fd(block->size, 1);
            write(1, " bytes\n", 7);
            write(1, "\033[0m", 5);
            *total += block->size;
            block = block->next;
        }
        zone = zone->next;
    }
}

// Function to display memory allocations
void show_alloc_mem()
{
    write(1, "--------------------------------\n", 33);
    write(1, "🌟 Memory allocations 🌟\n", 29);

    size_t total_memory = 0;

    // Print TINY zone allocations
    print_zone("TINY", tiny_zone, &total_memory);

    // Print SMALL zone allocations
    print_zone("SMALL", small_zone, &total_memory);

    // Print LARGE allocations
    print_zone("LARGE", large_allocations, &total_memory);

    // Print total memory allocated
    write(1, "Total : ", 8);
    ft_putnbr_fd(total_memory, 1);
    write(1, " bytes\n", 7);

    write(1, "--------------------------------\n", 33);
}
