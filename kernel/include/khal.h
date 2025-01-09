#ifndef __K_HAL
#define __K_HAL

#include <kstdint.h>
#include <kasm.h>

#if defined(__x86_64__)

extern uint64_t paging_main[3][512] __attribute__((aligned(4096)));

void serial_write_byte(uint8_t byte);
int serial_init();

#else
#error "Only AMD64 is supported"
#endif

#endif