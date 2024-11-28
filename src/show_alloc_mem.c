#include "malloc.h"

/// Print a address to the standard output in hexadecimal format
static void print_address_hex(size_t value) {
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

/// Print a memory block in hexadecimal format
static void print_block_hex(void *block_start, size_t size) {
    char *ptr = (char *)block_start;
    size_t i = 0;
    while (i < size) {
        if (i % 16 == 0) {
            if (i > 0) {
                write(1, "\n", 1);
            }
            print_address_hex((size_t)ptr);
            write(1, ": ", 2);
        }
        write(1, " ", 1);
        write(1, &"0123456789abcdef"[(*ptr >> 4) & 0xF], 1);
        write(1, &"0123456789abcdef"[*ptr & 0xF], 1);
        ptr++;
        i++;
    }
    write(1, "\n", 1);
}

// Helper function to print blocks in a given zone
static void print_zone(const char *zone_name, MemoryZone *zone, size_t *total, char dump)
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
                *total += block->size;
                write(1, "\033[0;31m", 7);
            }
            print_address_hex((size_t)block_start);
            write(1, " - ", 3);
            print_address_hex((size_t)block_end);
            write(1, " : ", 3);
            ft_putnbr_fd(block->size, 1);
            write(1, " bytes\n", 7);
            write(1, "\033[0m", 5);
            if (dump && !block->free)
            {
                print_block_hex(block_start, block->size);
            }
            block = block->next;
        }
        zone = zone->next;
    }
}

static void intro_print_zone(char dump)
{
    write(1, "--------------------------------\n", 33);
    if (dump)
    {
        write(1, "🌟 Memory hexdump 🌟\n", 26);
    }
    else
    {
        write(1, "🌟 Memory allocations 🌟\n", 29);
    }

    size_t total_memory = 0;

    print_zone("TINY", memory_zones.tiny_zone, &total_memory, dump);

    print_zone("SMALL", memory_zones.small_zone, &total_memory, dump);

    print_zone("LARGE", memory_zones.large_allocations, &total_memory, dump);

    write(1, "Total : ", 8);
    ft_putnbr_fd(total_memory, 1);
    write(1, " bytes\n", 7);

    write(1, "--------------------------------\n", 33);
}

// Function to display memory allocations
void show_alloc_mem()
{
    intro_print_zone(0);
}

/// Function to display a hexdump of a memory block
void show_alloc_mem_hex()
{
    intro_print_zone(1);
}
