// NOTE: This file contains code derived from or inspired by AstriX ("The AstriX
// Operating System") at https://codeberg.org/AstriX/AstriX. Copyright (c)
// 2023-2025 NotYourFox, sigsegv SPDX-License-Identifier: GPL-3.0-or-later

// If this project is made accessible to the general public, it is required to
// obey the terms of GNU General Public License version 3 (or later) for as long
// as this notice applies.
// If you suspect any form of license violation or copyright infringement,
// please reach out to AstriX team at <contact@notyourfox.coffee>.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "kstring.h"
#include <stdbool.h>
#include <stddef.h>

void memset(void *ptr, char c, size_t size) {
	for (size_t i = 0; i < size; i++) {
		*(char *)(ptr + i) = c;
	}
}

void xmemcpy(void *dest, const void *src, size_t size, opsize_t opsize) {
	size_t d0, d1, d2;

	switch (opsize) {
		case OPSIZE_BYTE:
			asm volatile("rep movsb"
			             : "=&c"(d0), "=&D"(d1), "=&S"(d2)
			             : "0"(size), "1"(dest), "2"(src)
			             : "memory");
			break;
		case OPSIZE_WORD:
			asm volatile("rep movsw"
			             : "=&c"(d0), "=&D"(d1), "=&S"(d2)
			             : "0"(size), "1"(dest), "2"(src)
			             : "memory");
			break;
		case OPSIZE_DWORD:
			asm volatile("rep movsl"
			             : "=&c"(d0), "=&D"(d1), "=&S"(d2)
			             : "0"(size), "1"(dest), "2"(src)
			             : "memory");
			break;
		case OPSIZE_QWORD:
			asm volatile("rep movsl"
			             : "=&c"(d0), "=&D"(d1), "=&S"(d2)
			             : "0"(size), "1"(dest), "2"(src)
			             : "memory");
			break;
		default:
			asm volatile("rep movsb"
			             : "=&c"(d0), "=&D"(d1), "=&S"(d2)
			             : "0"(size * opsize), "1"(dest), "2"(src)
			             : "memory");
			break;
	}
}

void memcpy(void *dest, const void *src, size_t size) {
	xmemcpy(dest, src, size, OPSIZE_BYTE);
}

int memcmp(const void *ptr1, const void *ptr2, size_t count) {
	register const unsigned char *p1 = ptr1;
	register const unsigned char *p2 = ptr2;

	while (count-- > 0) {
		if (*p1++ != *p2++) {
			return p1[-1] < p2[-1] ? -1 : 1;
		}
	}

	return 0;
}

size_t __attribute__((pure)) strlen(const char *s) {
	int i;
	for (i = 0; s[i] != '\0'; i++);
	return i;
}

char *strcat(char *dst, const char *src) {
	char *buf = dst;
	strcpy(dst + strlen(dst), src);
	return buf;
}

char *strcpy(char *dest, const char *src) {
	memcpy(dest, src, strlen(src) + 1);
	return dest;
}

char *strncpy(char *dest, const char *src, size_t n) {
	size_t total = n > strlen(src) ? strlen(src) : n;
	memcpy(dest, src, total);
	dest[total] = 0x00;

	return dest;
}

int strncmp(const char *s1, const char *s2, size_t n) {
	if (n > strlen(s1) || n > strlen(s2)) {
		return strlen(s1) > strlen(s2) ? 1 : -1;
	}

	return memcmp(s1, s2, n);
}

int strcmp(const char *s1, const char *s2) {
	if (strlen(s1) != strlen(s2)) {
		return strlen(s1) > strlen(s2) ? 1 : -1;
	}

	return strncmp(s1, s2, strlen(s1));
}

char *strltrim(char *str) {
	while (*str == ' ' || *str == '\t') {
		str++;
	}

	return str;
}

char *strrtrim(char *str) {
	char *ptr = str + strlen(str) - 1;
	while (*ptr == ' ' || *ptr == '\t') {
		*ptr++ = 0x00;
	}

	return str;
}

char *strtrim(char *str) {
	str = strltrim(str);
	return strrtrim(str);
}

bool isupperc(char c) {
	return (c >= 'A' && c <= 'Z');
}

bool isupper(const char *s) {
	string_for_each(s, i) {
		if (!isupperc(s[i])) {
			return false;
		}
	}

	return true;
}

bool islowerc(char c) {
	return (c >= 'a' && c <= 'z');
}

// note: returns false for non-alpha string
bool islower(const char *s) {
	string_for_each(s, i) {
		if (!islowerc(s[i])) {
			return false;
		}
	}

	return true;
}

bool isdigit(char c) {
	return c >= '0' && c <= '9';
}

bool isnumeric(const char *s) {
	string_for_each(s, i) {
		if (!isdigit(s[i])) {
			return false;
		}
	}

	return true;
}

bool isalphac(char c) {
	return isupperc(c) || islowerc(c);
}

bool isalpha(const char *s) {
	string_for_each(s, i) {
		if (!isalphac(s[i])) {
			return false;
		}
	}

	return true;
}

bool isalnumc(char c) {
	return isalphac(c) || isdigit(c);
}

bool isalnum(const char *s) {
	string_for_each(s, i) {
		if (!isalphac(s[i]) && !isdigit(s[i])) {
			return false;
		}
	}

	return true;
}

char toupperc(char c) {
	if (!isalnumc(c)) {
		return c;
	}

	return c & ~0x20;
}

char tolowerc(char c) {
	if (!isalnumc(c)) {
		return c;
	}

	return _tolower(c);
}

// NOTE: MODIFIES STRING IN-PLACE

char *toupper(char *s) {
	// note: 'a' > 'A'
	string_for_each(s, i) {
		if (isupperc(s[i]) || !isalphac(s[i])) {
			continue;
		}

		s[i] = toupperc(s[i]);
	}

	return s;
}

char *tolower(char *s) {
	// note: 'a' > 'A'
	string_for_each(s, i) {
		if (islowerc(s[i]) || !isalphac(s[i])) {
			continue;
		}

		s[i] = tolowerc(s[i]);
	}

	return s;
}

char *strchr(char *s, char c) {
	for (size_t i = 0; i < strlen(s); i++) {
		if (s[i] == c) {
			return s + i;
		}
	}

	return NULL;
}

char *strchr_r(char *s, char c) {
	for (int i = strlen(s) - 1; i >= 0; i--) {
		if (s[i] == c) {
			return s + i;
		}
	}

	return NULL;
}

char *strstr(char *str, const char *sub) {
	for (size_t i = 0; i < strlen(str); i++) {
		if (!strncmp(str + i, sub, strlen(sub))) {
			return str + i;
		}
	}

	return NULL;
}