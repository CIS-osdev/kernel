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

// https://wiki.osdev.org/Inline_Assembly/Examples
static inline void io_wait() {
    outb(0x80, 0);
}

static inline void lidt(void* base, uint16_t size) {
    // This function works in 32 and 64bit mode
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    asm ( "lidt %0" : : "m"(IDTR) );  // let the compiler choose an addressing mode
}

uint64_t rdtsc() {
    uint32_t low, high;
    asm volatile("rdtsc":"=a"(low),"=d"(high));
    return ((uint64_t)high << 32) | low;
}

static inline void wrmsr(uint64_t msr, uint64_t value) {
    uint32_t low = value & 0xFFFFFFFF;
    uint32_t high = value >> 32;
    asm volatile (
        "wrmsr"
        :
        : "c"(msr), "a"(low), "d"(high)
    );
}

static inline uint64_t rdmsr(uint64_t msr) {
    uint32_t low, high;
    asm volatile (
        "rdmsr"
        : "=a"(low), "=d"(high)
        : "c"(msr)
    );
	return ((uint64_t)high << 32) | low;
}


#else
#error "Only AMD64 is supported"
#endif

#endif