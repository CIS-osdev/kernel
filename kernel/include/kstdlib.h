#ifndef __K_STDLIB
#define __K_STDLIB

#include <ktypes.h>

#define unlikely(x) __builtin_expect(x, 0)
#define likely(x) __builtin_expect(x, 1)

/** @brief Ignore unused variable/static function.*/
#define IGNORE_UNUSED(x) ((void)x)

#define BITS_PER_BYTE 8

/**
 * @brief Convert bits to bytes.
 *
 * @param [in] n - given number of bits.
 * @return number of bytes needed for containing n bits.
 */
static inline usize bits_to_bytes(usize n) {
	// assuming that a byte contains 8 bits
	return (n + 7) >> 3;
}

/**
 * @brief Convert bytes to bits.
 *
 * @param [in] n - given number of bytes.
 * @return number of bits in n bytes.
 */
static inline usize bytes_to_bits(usize n) {
	// assuming that a byte contains 8 bits
	return n << 3;
}

/**
 * @brief Get number of bits in value.
 *
 * @param [in] x - given value to count.
 * @return number of bits in value.
 */
#define BITS_PER_TYPE(x) (bytes_to_bits(sizeof(x)))

/**
 * @brief Set the specific bit of given value.
 *
 * @param [out] value - given value to change.
 * @param [in] pos - given bit position to set.
 */
static inline void set_bit(u32 *value, i32 pos) {
	*value |= (1U << pos);
}

/**
 * @brief Clear the specific bit of given value.
 *
 * @param [out] value - given value to change.
 * @param [in] pos - given bit position to clear.
 */
static inline void clear_bit(u32 *value, i32 pos) {
	*value &= ~(1U << pos);
}

/**
 * @brief Get the specific bit of given value.
 *
 * @param [in] value - given value to test.
 * @param [in] pos - given bit position to test.
 * @return true if the bit is set, false otherwise.
 */
static inline bool test_bit(u32 value, i32 pos) {
	return (value & (1U << pos)) != 0;
}

#endif /* __K_STDLIB */