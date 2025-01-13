#ifndef __ARCH_CPU_TABLES
#define __ARCH_CPU_TABLES

#define DESC_TABLE_SIZE 6

#ifndef __ASSEMBLY__
#include <stdint.h>

struct desc_table {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed));
#endif

#endif