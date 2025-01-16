#ifndef __K_MULTIBOOT2
#define __K_MULTIBOOT2

#include "3rd/multiboot2.h"
#include <stdint.h>

// STUB!
typedef int list_head;

// make it tag-like to fit better with get_multiboot_tag
struct multiboot_module_list_tag {
	multiboot_uint16_t type;  // will be MULTIBOOT_TAG_MODULE
	multiboot_uint16_t flags; // will be 0
	multiboot_uint32_t size; // will be sizeof(struct multiboot_module_list_tag)

	struct multiboot_tag_module *module;
	list_head list;
};

struct multiboot_tag *get_multiboot_tag(uint8_t tag_id);
int multiboot2_init(uint64_t *addr, uint32_t magic);

#endif