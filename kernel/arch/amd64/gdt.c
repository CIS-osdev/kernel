#include <kstdint.h>

typedef struct {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed)) gdt_entry64_t;

gdt_entry64_t gdt64[3];

void gdt64_set_gate(int num, uint64_t base, uint32_t limit, uint8_t access, uint8_t granularity) {
    gdt64[num].limit_low = (limit & 0xFFFF);
    gdt64[num].base_low = (base & 0xFFFF);
    gdt64[num].base_middle = (base >> 16) & 0xFF;
    gdt64[num].access = access;
    gdt64[num].granularity = (granularity & 0xF) | ((limit >> 16) & 0xF0);
    gdt64[num].base_high = (base >> 24) & 0xFF;
}

void gdt64_install() {
    gdt64_set_gate(0, 0, 0, 0, 0);
    gdt64_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xAF);
    gdt64_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    uint64_t gdt64_ptr = (sizeof(gdt_entry64_t) * 3) - 1;
    gdt64_ptr |= (uint64_t)gdt64 << 16;
    asm volatile("lgdt %0" : : "m" (*(void **) &gdt64_ptr));
}