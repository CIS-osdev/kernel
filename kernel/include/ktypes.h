#ifndef __K_TYPES
#define __K_TYPES

#include <stdbool.h>
#include <stdint.h>

// unsigned types
typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

// signed types
typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t i8;

// floating point types
typedef double f64;
typedef float f32;

// other
typedef i64 ssize;
typedef u64 usize;

// memory manager
typedef u32 phys_addr_t;
typedef u32 virt_addr_t;

#endif /* __K_TYPES */