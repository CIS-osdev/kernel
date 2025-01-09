#include <kstdint.h>
#include <khal.h>


void kernel_main64(uint64_t *multiboot, uint32_t magic, void *esp, uint64_t base) {
    serial_init();
    serial_write_byte('[');
    serial_write_byte('O');
    serial_write_byte('K');
    serial_write_byte(']');
    for(;;) {}
}