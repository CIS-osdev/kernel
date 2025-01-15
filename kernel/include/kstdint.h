#ifndef __K_STDINT
#define __K_STDINT

// unsigned types
typedef unsigned long long uint64_t;
typedef unsigned int       uint32_t;
typedef unsigned short     uint16_t;
typedef unsigned char      uint8_t;

typedef uint64_t u64;
typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t  u8;

// signed types
typedef long long int64_t;
typedef int       int32_t;
typedef short     int16_t;
typedef char      int8_t;

typedef int64_t i64;
typedef int32_t i32;
typedef int16_t i16;
typedef int8_t  i8;

// floating point types
typedef double f64;
typedef float  f32;

// other
typedef int64_t  ssize_t;
typedef uint64_t size_t;

typedef i64 ssize;
typedef u64 usize;

// memory manager
typedef u32 phys_addr_t;
typedef u32 virt_addr_t;

#endif