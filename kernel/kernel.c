#include <khal.h>
#include <kstdint.h>

int multiboot2_init(uint64_t *addr, uint32_t magic);

void kernel_main64(uint64_t *multiboot2, uint32_t magic, void *esp, uint64_t base) {
	serial_init( );
	serial_write_byte(':');
	serial_write_byte('D');
	serial_write_byte('\n');
	int status = multiboot2_init(multiboot2, magic);
	serial_write_byte('\n');

	if (status) {
		serial_write_byte('[');
		serial_write_byte('O');
		serial_write_byte('K');
		serial_write_byte(']');
	} else {
		serial_write_byte('[');
		serial_write_byte('E');
		serial_write_byte('R');
		serial_write_byte('R');
		serial_write_byte(']');
	}
	for (;;) {}
}