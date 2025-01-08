#include <kstdint.h>

typedef struct {
    uint16_t limit;
    uint64_t base;
} __attribute__((packed)) idt_reg_t;

typedef struct {
    uint16_t offset_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t type_attr;
    uint16_t offset_high;
} __attribute__((packed)) idt_entry_t;

idt_entry_t idt[256];
idt_reg_t idt_reg;

void dummy_handler64() {
    asm volatile("iretq");
}

void idt_set_gate(int num, uint64_t handler, uint16_t selector, uint8_t type_attr) {
    idt[num].offset_low = handler & 0xFFFF;
    idt[num].selector = selector;
    idt[num].zero = 0;
    idt[num].type_attr = type_attr;
    idt[num].offset_high = (handler >> 16) & 0xFFFF;
}

void idt_install() {
    for(int i = 0; i < 256; i++) {
        idt_set_gate(i, (uint64_t)dummy_handler64, 0x08, 0x8E);
    }

    idt_reg.limit = (sizeof(idt_entry_t) * 256) - 1;
    idt_reg.base = (uint64_t)&idt;
    asm volatile("lidt %0" : : "m" (idt_reg));
}