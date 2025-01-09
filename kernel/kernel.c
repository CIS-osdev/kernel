#include <khal.h>
#include <kstdint.h>

int multiboot_init(uint64_t *addr, uint32_t magic);

void kernel_main64(uint64_t *multiboot, uint32_t magic, void *esp, uint64_t base) {
	serial_init( );
	multiboot_init(multiboot, magic);
	serial_write_byte('[');
	serial_write_byte('O');
	serial_write_byte('K');
	serial_write_byte(']');
	for (;;) {}
}