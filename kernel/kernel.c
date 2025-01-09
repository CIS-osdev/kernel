#include <kstdint.h>

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void hal_write_byte_manual(uint8_t byte) {
	outb(0x3f8, byte);
}

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
    hal_write_byte_manual('[');
    hal_write_byte_manual('O');
    hal_write_byte_manual('K');
    hal_write_byte_manual(']');
    puts("Hello, World from CIS! ");
    for(;;) {}
}