#include "amd64/cpu/regs.h"
#include "khal.h"

void cpu_state_print() {
	asm_regs_t current_state;

	serial_printf(
	    "The following register dump is a stub and a work-in-progress.\n");

	update_asm_regs(&current_state);
	serial_printf("Registers:\n");
	serial_printf("\tRAX: 0x%x  RBX: 0x%x  RCX: 0x%x  RDX: 0x%x\n",
	              current_state.eax, current_state.ebx, current_state.ecx,
	              current_state.edx);
	serial_printf("\tRBP: 0x%x  RSP: 0x%x  RSI: 0x%x  RDI: 0x%x\n",
	              current_state.ebp, current_state.esp, current_state.esi,
	              current_state.edi);
	serial_printf("\tCS:  0x%x  DS:  0x%x  ES:  0x%x  FS:  0x%x\n",
	              current_state.cs, current_state.ds, current_state.es,
	              current_state.fs);
	serial_printf("\tGS:  0x%x  SS:  0x%x\n", current_state.gs,
	              current_state.ss);
	serial_printf("\tCR0: 0x%x  CR2: 0x%x  CR3: 0x%x  CR4: 0x%x\n",
	              current_state.cr0, current_state.cr2, current_state.cr3,
	              current_state.cr4);

	serial_printf("\tDR0: 0x%x  DR1: 0x%x  DR2: 0x%x  DR3: 0x%x\n",
	              current_state.dr0, current_state.dr1, current_state.dr2,
	              current_state.dr3);
	serial_printf("\tDR6: 0x%x  DR7: 0x%x\n", current_state.dr6,
	              current_state.dr7);
	serial_printf("\tGDTR: base=0x%x, limit=0x%x\n\tLDTR: base=0x%x, "
	              "limit=0x%x\n\tIDTR: base=0x%x, limit=0x%x\n",
	              current_state.gdtr.base, current_state.gdtr.limit,
	              current_state.ldtr.base, current_state.ldtr.limit,
	              current_state.idtr.base, current_state.idtr.limit);

	// TODO: symbol names
	serial_printf("\tRIP: 0x%x", current_state.rip);

	// serial_printf("\tCode: ");
	// for (int i = 0; i < 16; i++) {
	// 	serial_printf("%x ", *(uint8_t *)(current_state.rip + i));
	// }
	// serial_printf("\n");

	serial_printf("\n");
}
