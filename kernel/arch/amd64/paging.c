#include <stdint.h>

uint64_t paging_main[3][512] __attribute__((aligned(4096))) = { 0 };

int paging_init() {
	return -1;
}