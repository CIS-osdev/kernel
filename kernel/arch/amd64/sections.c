#include "khal.h"
#include <stdint.h>
#include "kstring.h"

extern uint64_t kernel_section_text_start;
extern uint64_t kernel_section_text_end;
extern uint64_t kernel_section_rodata_start;
extern uint64_t kernel_section_rodata_end;
extern uint64_t kernel_section_data_start;
extern uint64_t kernel_section_data_end;
extern uint64_t kernel_section_bss_start;
extern uint64_t kernel_section_bss_end;

int sectons_init() {
	serial_printf("\t.text 0x%x-0x%x(%u)\n", &kernel_section_text_start,
	              &kernel_section_text_end,
	              &kernel_section_text_end - &kernel_section_text_start);
	serial_printf("\t.rodata 0x%x-0x%x(%u)\n", &kernel_section_rodata_start,
	              &kernel_section_rodata_end,
	              &kernel_section_rodata_end - &kernel_section_rodata_start);
	serial_printf("\t.data 0x%x-0x%x(%u)\n", &kernel_section_data_start,
	              &kernel_section_data_end,
	              &kernel_section_data_end - &kernel_section_data_start);
	serial_printf("\t.bss 0x%x-0x%x(%u)\n", &kernel_section_bss_start,
	              &kernel_section_bss_end,
	              &kernel_section_bss_end - &kernel_section_bss_start);
	
	memset(&kernel_section_bss_start, 0, &kernel_section_bss_end - &kernel_section_bss_start);

	return 1;
}