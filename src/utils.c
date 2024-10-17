#include "../inc/malloc.h"

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