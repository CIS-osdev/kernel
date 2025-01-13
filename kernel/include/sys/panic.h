#include <stdint.h>

void __attribute__((noreturn)) panic_int(uint8_t int_no, const char *msg);
void __attribute__((noreturn)) panic(const char *msg);