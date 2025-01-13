#include "arch/cpu/strace.h"
#include <stdint.h>

struct stackframe *strace_get() {
	struct stackframe *res;
	asm("movq %%rbp, %0" : "=r"(res));
	return res;
}

uint64_t strace_get_framep(int sf_offset) {
	struct stackframe *stack = strace_get();

	// skip get_x86_stack_trace(), 0 points to this function
	for (int i = 0; stack && i < sf_offset + 1; i++) {
		stack = stack->sp;
	}

	return stack->pc;
}