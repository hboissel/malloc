#include "malloc.h"
#include <unistd.h>

void test_zone_alloc(size_t size_alloc, char *zone_name) {
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

/// Function that test fragmentation
void test_fragmentation() {
    write(1, "🧪 Fragmentation test 🧪\n", 29);
    const size_t size = 10;
    void* tab[size];
    size_t i = 0;

    while (i < size) {
        tab[i] = malloc(128);
        i++;
    }
    show_alloc_mem();
    i = 0;
    while (i < size - 1) {
        free(tab[i]);
        i++;
    }
    show_alloc_mem();
    free(tab[size - 1]);
}

/// function that test realloc
void test_realloc() {
    write(1, "🧪 Realloc test 🧪\n", 23);
    void* ptr = malloc(128);
    ft_memcpy(ptr, "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA", 32);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 256);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 64);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 65);
    show_alloc_mem_ex();
    ptr = realloc(ptr, 4);
    show_alloc_mem_ex();
    free(ptr);
    show_alloc_mem();
}

/// function that test realloc and free with random values
void test_random() {
    write(1, "🧪 Random test 🧪\n", 22);
    void* ptr = malloc(128) + 1;
    free(ptr);
    show_alloc_mem();
    void* ptr2 = malloc(128) + 1;
    show_alloc_mem();
    void* res = realloc(ptr2, 128);
    show_alloc_mem();
    if (res == NULL) {
        write(1, "Realloc failed\n", 15);
    }
    free(ptr - 1);
    free(ptr2 - 1);
    show_alloc_mem();
}

/// Function that test show_alloc_mem_ex
void test_show_alloc_mem_ex() {
    write(1, "🧪 show_alloc_mem_ex test 🧪\n", 34);
    char* ptr = malloc(128);
    ft_memcpy(ptr, "AAAAAAAAAAAAAAAA", 16);
    char* ptr2 = malloc(128);
    ft_memcpy(ptr2, "BBBBBBBBBBBBBBBB", 16);
    show_alloc_mem_ex();
    free(ptr);
    free(ptr2);
    show_alloc_mem_ex();
}

/// Stress test with 1000 malloc and free
void test_stress() {
    write(1, "🧪 Stress test 🧪\n", 22);
    const size_t size = 10000;
    void* tab[size];
    size_t i = 0;

    while (i < size) {
        tab[i] = calloc(1, 48);
        i++;
    }
    i = 0;
    while (i < size) {
        free(tab[i]);
        i++;
    }
    show_alloc_mem();
}

/// Personalized test
void test_personalized() {
    write(1, "🧪 Personalized test 🧪\n", 28);

}

/// function that test all functions: malloc, free, realloc, show_alloc_mem
void test() {
    // test_zone_alloc(TINY_THRESHOLD, "TINY");
    // test_zone_alloc(SMALL_THRESHOLD, "SMALL");
    // test_zone_alloc(10000, "LARGE");
    // test_fragmentation();
    // test_realloc();
    // test_random();
    // test_show_alloc_mem_ex();
    // test_personalized();
    test_stress();
}

int main()
{
    write(1, "Page size: ", 11);
    ft_putnbr_fd(sysconf(_SC_PAGESIZE), 1);
    write(1, "\n", 1);

    write(1, "BLOCK_META_SIZE: ", 17);
    ft_putnbr_fd(BLOCK_META_SIZE, 1);
    write(1, "\n", 1);

    write(1, "MEMORY_ZONE_SIZE: ", 18);
    ft_putnbr_fd(MEMORY_ZONE_SIZE, 1);
    write(1, "\n", 1);

    test();
    return 0;
}