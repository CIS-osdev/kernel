#include <khal.h>
#include <kstdint.h>

int multiboot2_init(uint64_t *addr, uint32_t magic);

void kernel_main64(uint64_t *multiboot2, uint32_t magic, void *esp, uint64_t base) {
	serial_init( );
	serial_printf(":D\n");
	
	int status = multiboot2_init(multiboot2, magic);

	if (status) {
		serial_printf("[OK]\n");
	} else {
		serial_printf("[ERR]\n");
	}

	for (;;) {}
}