#include "khal.h"
#include "kstring.h"
#include "sys/panic.h"
#include <stdint.h>

int multiboot2_init(uint64_t *addr, uint32_t magic);
int sectons_init();

void kernel_main64(uint64_t *multiboot2, uint32_t magic, void *esp,
                   uint64_t base) {
	sectons_init();
	serial_init();
	serial_printf(":D\n");

	int status = multiboot2_init(multiboot2, magic);

	if (status) {
		serial_printf("[OK]\n");
	} else {
		serial_printf("[ERR]\n");
	}

	PANIC("AAAAAAAAAAAAAAAaa");

	for (;;) {}
}
