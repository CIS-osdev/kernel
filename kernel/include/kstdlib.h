#ifndef __K_STDLIB
#define __K_STDLIB

#define unlikely(x) __builtin_expect(x, 0)
#define likely(x) __builtin_expect(x, 1)

#define IGNORE_UNUSED(x) ((void)x)

#endif