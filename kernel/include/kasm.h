#ifndef __K_ASM
#define __K_ASM

#include <kstdint.h>

#if defined(__x86_64__)
static inline void outb(uint16_t port, uint8_t val) {
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
	uint8_t ret;
	asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

static inline void outw(uint16_t port, uint16_t val) {
	asm volatile("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint16_t inw(uint16_t port) {
	uint16_t ret;
	asm volatile("inw %1, %0" : "=a"(ret) : "Nd"(port));
	return ret;
}

static inline void outl(uint16_t port, uint32_t val) {
	asm volatile("outl %%eax, %%dx" : : "dN"(port), "a"(val));
}

static inline unsigned int inl(uint16_t port) {
	uint32_t ret;
	asm volatile("inl %%dx, %%eax" : "=a"(ret) : "dN"(port));
	return ret;
}

#else
#error "Only AMD64 is supported"
#endif

#endif