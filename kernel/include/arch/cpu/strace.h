#ifndef __ARCH_CPU_STRACE
#define __ARCH_CPU_STRACE

#include <stdint.h>

struct stackframe {
	struct stackframe *sp;
	uint64_t pc;
};

extern struct stackframe *strace_get();
extern uint64_t strace_get_framep(int sf_offset);

#endif