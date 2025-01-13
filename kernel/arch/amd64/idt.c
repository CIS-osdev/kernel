#include "kstdint.h"

// From https://wiki.osdev.org/Interrupt_Descriptor_Table#Structure_on_x86-64
struct idt_64 {
	uint16_t offset_1; // offset bits 0..15
	uint16_t selector; // a code segment selector in GDT or LDT
	uint8_t
	    ist; // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
	uint8_t type_attributes; // gate type, dpl, and p fields
	uint16_t offset_2;       // offset bits 16..31
	uint32_t offset_3;       // offset bits 32..63
	uint32_t zero;           // reserved
};