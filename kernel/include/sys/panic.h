#ifndef __SYS_PANIC
#define __SYS_PANIC

#include <stdint.h>

void __attribute__((noreturn)) panic_int(uint8_t int_no, const char *msg);
void __attribute__((noreturn))
panic(const char *msg, const char *func, const int line);

#define PANIC(msg) panic(msg, __func__, __LINE__)

#endif
