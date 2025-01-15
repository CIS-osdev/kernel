#include "arch/cpu/control.h"
#include "arch/cpu/state.h"
#include "khal.h"
#include <stdint.h>

// TODO: make printf-like

void __attribute__((noreturn)) panic_int(uint8_t int_no, const char *msg) {
	cpu_interrupt_lock_acquire();

	serial_printf("\n\rKernel panic (in interrupt) [INT=0x%02X] - %s\n", int_no,
	              msg);
	cpu_state_print();

	for (;;) cpu_halt();
}

void __attribute__((noreturn)) panic(const char *msg, const char *func,
                                     const int line) {
	cpu_interrupt_lock_acquire();

	serial_printf("\n\rKernel panic - %s in %s:%d\n", msg, func, line);
	cpu_state_print();
	for (;;) cpu_halt();
}