#define __ASSEMBLY__

.intel_syntax noprefix

#include "arch/cpu/tables.h"

.code64

.global __asm_update_regs

get_flags:
    pushfd
    mov rax, [rsp]
    popfd

    ret

get_rip:
    mov rax, [rsp]
    ret

// TODO because I'm not familiar with x86-64 conventions
__asm_update_regs:
    ret

#undef __ASSEMBLY__