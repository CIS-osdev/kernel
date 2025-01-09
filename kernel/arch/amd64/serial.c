#include <kstdint.h>

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void serial_write_byte(uint8_t byte) {
	outb(0x3f8, byte);
}

int serial_init() {
    return -1;
}