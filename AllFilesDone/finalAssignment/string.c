/*
 *
 * Limited string.h functionality
 * string.c
 *
 * Copyright (C) 2018 Bastiaan Teeuwen <bastiaan@mkcl.nl>
 *
 */

#include <stddef.h>

void *memcpy(void *dest, const void *src, size_t n)
{
	unsigned char *d = dest;
	const unsigned char *s = src;

	while (n--)
		*d++ = *s++;

	return dest;
}

void *memmove(void *dest, const void *src, size_t n)
{
	char *d = dest;
	const char *s = src;

	if (d == s)
		return dest;

	if (s > d) {
		while (n--)
			*d++ = *s++;
	} else {
		d += n - 1;
		s += n - 1;

		while (n--)
			*d-- = *s--;
	}

	return dest;
}

void *memset(void *dest, int c, size_t n)
{
	unsigned char *d = dest;

	while (n--)
		*d++ = c;

	return dest;
}

char *strcpy(char *dest, const char *src)
{
	char *d = dest;
	const char *s = src;

	while ((*d++ = *s++));

	return dest;
}

char *strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

	for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];

	while (i < n)
		dest[i++] = '\0';

	return dest;
}
