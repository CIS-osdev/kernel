#include <kstring.h>
#include <kstdint.h>

int strcmp(const char *s1, const char *s2) 
{
    for (int i = 0;; i++)
    {
        if (s1[i] > s2[i])
		{
	    	return 1;
		}
		else if (s1[i] < s2[i]) 
		{
	    	return -1; // INT сломан, тут он возращает maxValue.
		}
		if (s1[i] == '\0' || s2[i] == '\0')
		{
	    	return 0;
		}
    }
}

char *strcpy(char *dst, const char *src)
{
	char *buf = dst;
	while ((*dst++ = *src++) != '\0'); // Задаем по байту в dst из src, пока результатом этого не станет NUL
	return buf;
}

int strlen(const char *s)
{
	int i;
	for (i = 0; s[i] != '\0'; i++); // Добавляем к i, пока не встретим NUL
	return i;
}

char *strcat(char *dst, const char *src)
{
	char *buf = dst;
	strcpy(dst+strlen(dst), src); // Копируем строку в цель со смешением в длинну dst
	return buf;
}
