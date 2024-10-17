#include "../inc/malloc.h"

void test_zone_alloc(size_t size_alloc, char *zone_name) {
    // header tiny zone test with emoji
    write(1, "🧪 ", 5);
    write(1, zone_name, ft_strlen(zone_name));
    write(1, " zone test 🧪\n", 16);
    const size_t size = 100;
    void* tab[size];
    size_t i = 0;

    while (i < size) {
        tab[i] = malloc(size_alloc);
        i++;
    }
    show_alloc_mem();
    i = 0;
    while (i < size) {
        free(tab[i]);
        i++;
    }
    show_alloc_mem();
}

/// function that test all functions: malloc, free, realloc, show_alloc_mem
void test() {
    test_zone_alloc(TINY_THRESHOLD, "TINY");
    test_zone_alloc(SMALL_THRESHOLD, "SMALL");
    test_zone_alloc(10000, "LARGE");
}

int main()
{
    // print page size with write
    write(1, "Page size: ", 11);
    ft_putnbr_fd(sysconf(_SC_PAGESIZE), 1);
    write(1, "\n", 1);
    test();
    return 0;
}