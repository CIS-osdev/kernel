#define __ASSEMBLY__

#include "arch/cpu/tables.h"

.code64

.global __asm_update_regs

get_flags:
    pushfd
    movq (%rsp), %rax
    popfd

    ret

get_rip:
    movq (%rsp), %rax
    ret

// TODO because I'm not familiar with x86-64 conventions
__asm_update_regs:
    ret

#undef __ASSEMBLY__