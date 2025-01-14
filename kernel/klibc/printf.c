#include "khal.h"
#include <stdint.h>
#include <stdarg.h>

static char *itoa(uint64_t value, char *buf, uint8_t base) {
	char *ptr = buf;
	uint64_t temp = value;
	do {
		uint64_t digit = temp % base;
		if (digit < 10)
			*ptr = '0' + digit;
		else
			*ptr = 'A' + (digit - 10);
		ptr++;
		temp /= base;
	} while (temp);
	*ptr = '\0';
	// Reverse the string
	char *start = buf;
	char *end = ptr - 1;
	while (start < end) {
		char tmp = *start;
		*start = *end;
		*end = tmp;
		start++;
		end--;
	}
	return buf;
}

// TODO: normalize
void __attribute__((format(printf, 1, 2))) serial_printf(const char *fmt, ...) {
	char buf[32];
	va_list args;
	va_start(args, fmt);
	while (*fmt) {
		if (*fmt == '%') {
			fmt++;
			switch (*fmt) {
				case 's': {
					char *str = va_arg(args, char *);
					while (*str) serial_write_byte(*str++);
				} break;
				case 'd': {
					int64_t num = va_arg(args, int64_t);
					itoa(num, buf, 10);
					serial_printf("%s", buf);
				} break;
				case 'u': {
					uint64_t num = va_arg(args, uint64_t);
					itoa(num, buf, 10);
					serial_printf("%s", buf);
				} break;
				case 'x': {
					uint64_t num = va_arg(args, uint64_t);
					itoa(num, buf, 16);
					serial_printf("%s", buf);
				} break;
				case 'c': serial_write_byte(va_arg(args, int)); break;
				default: serial_write_byte(*fmt); break;
			}
			fmt++;
		} else {
			serial_write_byte(*fmt++);
		}
	}
	va_end(args);
}
