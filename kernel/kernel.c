#include <kstdint.h>

extern void serial_write_byte(uint8_t byte);


void kernel_main64(uint64_t *multiboot, uint32_t magic, void *esp, uint64_t base) {
    serial_write_byte('[');
    serial_write_byte('O');
    serial_write_byte('K');
    serial_write_byte(']');
    for(;;) {}
}