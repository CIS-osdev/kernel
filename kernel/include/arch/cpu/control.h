#ifndef __ARCH_CPU_CONTROL
#define __ARCH_CPU_CONTROL

#include <stdbool.h>

extern bool cpu_interrupt_lock_acquired();
extern void cpu_interrupt_lock_acquire();
extern void cpu_interrupt_lock_release();
extern void cpu_interrupt_lock_force_release();

void cpu_halt();

#endif