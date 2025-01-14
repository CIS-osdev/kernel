#include "khal.h"
#include <stdint.h>
#include "kstdlib.h"
#include <3rd/multiboot2.h>

#define CHECK_FLAG(flags, bit) ((flags) & (1 << (bit)))

void handle_cmdline_tag(struct multiboot_tag *tag);
void handle_module_tag(struct multiboot_tag *tag);
void handle_basic_load_base_addr(struct multiboot_tag *tag);
void handle_basic_meminfo_tag(struct multiboot_tag *tag);
void handle_mmap_tag(struct multiboot_tag *tag);

int multiboot2_init(uint64_t *addr, uint32_t magic) {
	struct multiboot_tag *tag;
	uint64_t mbi_addr = (uint64_t)addr;

	if (magic != MULTIBOOT2_BOOTLOADER_MAGIC) {
		serial_printf("Invalid magic number: 0x%x\n", (unsigned)magic);
		return -1;
	}

	if (mbi_addr & 7) {
		serial_printf("Unaligned mbi: 0x%x\n", mbi_addr);
		return -2;
	}

	uint64_t size = *addr;
	serial_printf("Announced mbi size 0x%x\n", size);

	tag = (struct multiboot_tag *)(mbi_addr + sizeof(uint64_t));

	while (tag->type != MULTIBOOT_TAG_TYPE_END) {
		if ((uintptr_t)tag % MULTIBOOT_TAG_ALIGN != 0) {
			serial_printf("Tag at 0x%x is not aligned correctly\n",
			              (uintptr_t)tag);
			break;
		}

		switch (tag->type) {
			case MULTIBOOT_TAG_TYPE_CMDLINE: handle_cmdline_tag(tag); break;
			case MULTIBOOT_TAG_TYPE_MODULE: handle_module_tag(tag); break;
			case MULTIBOOT_TAG_TYPE_BASIC_MEMINFO:
				handle_basic_meminfo_tag(tag);
				break;
			case MULTIBOOT_TAG_TYPE_MMAP: handle_mmap_tag(tag); break;
			case MULTIBOOT_TAG_TYPE_LOAD_BASE_ADDR:
				handle_basic_load_base_addr(tag);
				break;
			default:
				serial_printf("Tag at 0x%x | %d\n", (uintptr_t)tag, tag->type);
				break;
		}

		// Move to the next tag
		tag = (struct multiboot_tag *)((uintptr_t)tag) + ((tag->size + 7) & ~7);
	}

	return 1;
}

void handle_cmdline_tag(struct multiboot_tag *tag) {
	struct multiboot_tag_string *cmdline = (struct multiboot_tag_string *)tag;
	serial_printf("Command line: %s\n", cmdline->string);
}

void handle_module_tag(struct multiboot_tag *tag) {
	struct multiboot_tag_module *module = (struct multiboot_tag_module *)tag;
	serial_printf("Module at 0x%x - 0x%x\n", module->mod_start,
	              module->mod_end);
	serial_printf("Module cmdline: %s\n", module->cmdline);
}

void handle_basic_meminfo_tag(struct multiboot_tag *tag) {
	struct multiboot_tag_basic_meminfo *meminfo =
	    (struct multiboot_tag_basic_meminfo *)tag;
	serial_printf("Memory lower: %u KB\n", meminfo->mem_lower);
	serial_printf("Memory upper: %u KB\n", meminfo->mem_upper);
}

void handle_basic_load_base_addr(struct multiboot_tag *tag) {
	struct multiboot_tag_load_base_addr *base_addr =
	    (struct multiboot_tag_load_base_addr *)tag;
	serial_printf("load_base_size: %u\n", base_addr->size);
	serial_printf("load_base_addr: 0x%x\n", base_addr->load_base_addr);
}

void handle_mmap_tag(struct multiboot_tag *tag) {
	struct multiboot_tag_mmap *mmap = (struct multiboot_tag_mmap *)tag;
	struct multiboot_mmap_entry *entry;
	uint64_t entry_size = mmap->entry_size;
	uint64_t entry_count =
	    (mmap->size - sizeof(struct multiboot_tag_mmap)) / entry_size;

	serial_printf("Memory map:\n");
	for (uint64_t i = 0; i < entry_count; i++) {
		entry =
		    (struct multiboot_mmap_entry *)((uintptr_t)mmap +
		                                    sizeof(struct multiboot_tag_mmap) +
		                                    i * entry_size);
		serial_printf("  0x%x - 0x%x: type %u\n", entry->addr,
		              entry->addr + entry->len, entry->type);
	}
}