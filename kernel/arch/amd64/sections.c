#include "khal.h"
#include "kstring.h"
#include <stdint.h>

extern uint64_t kernel_section_text_start;
extern uint64_t kernel_section_text_end;
extern uint64_t kernel_section_rodata_start;
extern uint64_t kernel_section_rodata_end;
extern uint64_t kernel_section_data_start;
extern uint64_t kernel_section_data_end;
extern uint64_t kernel_section_bss_start;
extern uint64_t kernel_section_bss_end;

typedef struct {
	uint64_t start;
	uint64_t end;
} sections_t;

sections_t kernel_sections[4];

sections_t *sectons_init() {
	// Why this halts cpu?
	//memset(&kernel_section_bss_start, 0,
	//       (uint64_t)&kernel_section_bss_end -
	//           (uint64_t)&kernel_section_bss_start);
	serial_printf("\t.text 0x%x-0x%x(%u)\n", &kernel_section_text_start,
	              &kernel_section_text_end,
	              &kernel_section_text_end - &kernel_section_text_start);
	kernel_sections[0] =
	    (sections_t){ kernel_section_text_start, kernel_section_text_end };

	serial_printf("\t.rodata 0x%x-0x%x(%u)\n", &kernel_section_rodata_start,
	              &kernel_section_rodata_end,
	              &kernel_section_rodata_end - &kernel_section_rodata_start);
	kernel_sections[1] =
	    (sections_t){ kernel_section_rodata_start, kernel_section_rodata_end };

	serial_printf("\t.data 0x%x-0x%x(%u)\n", &kernel_section_data_start,
	              &kernel_section_data_end,
	              &kernel_section_data_end - &kernel_section_data_start);
	kernel_sections[2] =
	    (sections_t){ kernel_section_data_start, kernel_section_data_end };

	serial_printf("\t.bss 0x%x-0x%x(%u)\n", &kernel_section_bss_start,
	              &kernel_section_bss_end,
	              &kernel_section_bss_end - &kernel_section_bss_start);
	kernel_sections[3] =
	    (sections_t){ kernel_section_bss_start, kernel_section_bss_end };

	return (sections_t *)&kernel_sections;
}