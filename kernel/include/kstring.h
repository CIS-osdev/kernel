#ifndef __K_STRING
#define __K_STRING

#include "kopsize.h"
#include <stdbool.h>
#include <stddef.h>

#define string_equal(s1, s2) !strcmp(s1, s2)
#define string_equal_n(s1, s2, n) !strncmp(s1, s2, n)
#define string_for_each(_s, _i) for (size_t _i = 0; _i < strlen(_s); _i++)

void memset(void *ptr, char c, size_t size);
void memcpy(void *dest, const void *src, size_t size);
void xmemcpy(void *dest, const void *src, size_t size, opsize_t opsize);
int memcmp(const void *ptr1, const void *ptr2, size_t count);

#define _tolower(c) ((c) | 0x20)

size_t __attribute__((pure)) strlen(const char *s);

char *strcpy(char *dest, const char *src);
char *strncpy(char *dest, const char *src, size_t n);

int __attribute__((pure)) strncmp(const char *s1, const char *s2, size_t n);
int __attribute__((pure)) strcmp(const char *s1, const char *s2);

char *strchr(char *s, char c);
char *strchr_r(char *s, char c);
char *strstr(char *str, const char *sub);

char *strltrim(char *str);
char *strrtrim(char *str);
char *strtrim(char *str);

bool isdigit(char c);
bool isalphac(char c);
bool islowerc(char c);
bool isupperc(char c);
bool isalnumc(char c);

bool isnumeric(const char *s);
bool isalpha(const char *s);
bool isalnum(const char *s);

char tolowerc(char c);
char *tolower(char *s);
char *toupper(char *s);

#endif
