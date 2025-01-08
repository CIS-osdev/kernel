#include <kstdint.h>

void puts(char *str) {
    char *video_memory = (char *)0xB8000;
    uint16_t *v = (uint16_t *)video_memory;
    int i = 0;
    while(str[i]) {
        v[i] = (str[i] << 8) | 0x0F;
        i++;
    }
}

void kernel_main64() {
    puts("Hello, World from CIS! ");
    while(1);
}