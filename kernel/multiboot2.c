#include <3rd/multiboot2.h>
#include <khal.h>
#include <kstdint.h>
#include <kstdlib.h>

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))
#define printf(...)

int multiboot2_init(uint64_t *addr, uint32_t magic) {
	serial_write_byte('1' + __COUNTER__);
	struct multiboot_tag *tag;
	
	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		printf("Invalid magic number: 0x%x\n", (unsigned)magic);
		return -1;
	}

	if ((uint64_t)addr & 7) {
      printf ("Unaligned mbi: 0x%x\n", addr);
      return -2;
    }

	uint64_t size = *addr;
	IGNORE_UNUSED(size);
	IGNORE_UNUSED(tag);

	printf ("Announced mbi size 0x%x\n", size);

	serial_write_byte('1' + __COUNTER__);
	return 1;
}