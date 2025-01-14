#ifndef __ARCH_CPU_REGS
#define __ARCH_CPU_REGS

#include "amd64/cpu/tables.h"

#include <stdint.h>

typedef struct {
	uint32_t eflags;

	union {
		struct {
			uint8_t ah;
			uint8_t al;
		};
		uint16_t ax;
		uint32_t eax;
		uint64_t rax;
	};
	union {
		struct {
			uint8_t bh;
			uint8_t bl;
		};
		uint16_t bx;
		uint32_t ebx;
		uint64_t rbx;
	};
	union {
		struct {
			uint8_t ch;
			uint8_t cl;
		};
		uint16_t cx;
		uint32_t ecx;
		uint64_t rcx;
	};
	union {
		struct {
			uint8_t dh;
			uint8_t dl;
		};
		uint16_t dx;
		uint32_t edx;
		uint64_t rdx;
	};

	union {
		uint16_t bp;
		uint32_t ebp;
		uint64_t rbp;
	};
	union {
		uint16_t sp;
		uint32_t esp;
		uint64_t rsp;
	};
	union {
		uint16_t si;
		uint32_t esi;
		uint64_t rsi;
	};
	union {
		uint16_t di;
		uint32_t edi;
		uint64_t rdi;
	};

	uint64_t rip;

	uint16_t cs;
	uint16_t ds;
	uint16_t es;
	uint16_t fs;
	uint16_t gs;
	uint16_t ss;

	uint32_t cr0;
	uint32_t cr2;
	uint32_t cr3;
	uint32_t cr4;

	uint32_t dr0;
	uint32_t dr1;
	uint32_t dr2;
	uint32_t dr3;
	uint32_t dr6;
	uint32_t dr7;

	struct desc_table gdtr;
	struct desc_table ldtr;
	struct desc_table idtr;
} __attribute__((packed)) asm_regs_t;

extern void update_asm_regs(asm_regs_t *state);

#endif
