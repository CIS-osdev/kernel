#include <kstdint.h>

uint64_t paging_main[3][512] __attribute__((aligned(4096))) = {0};

static inline void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

void hal_write_byte_manual(uint8_t byte) {
	outb(0x3f8, byte);
}

void kernel_main64(uint64_t *multiboot, uint32_t magic, void *esp, uint64_t base) {
    hal_write_byte_manual('[');
    hal_write_byte_manual('O');
    hal_write_byte_manual('K');
    hal_write_byte_manual(']');
    for(;;) {}
}