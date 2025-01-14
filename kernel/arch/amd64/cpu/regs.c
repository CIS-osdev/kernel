#include "amd64/cpu/regs.h"
#include "arch/cpu/strace.h"
#include "kstring.h"

extern void __asm_update_regs(asm_regs_t *regs);

// work in progress
void update_asm_regs(asm_regs_t *state) {
	memset(state, 0x00, sizeof(asm_regs_t));
	return;
}