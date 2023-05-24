#include "shell.h"

/**
 * *_memset - function that fills memory with a const byte
 * @s: pointer to memory area
 * @d: byte
 * @i: amount of bytes
 * Return: s
 */
char *_memset(char *s, char d, unsigned int i)
{
	unsigned int a;

	for (a = 0; a < i; a++)
		s[a] = d;
	return (s);
}

/**
 * ifree - function that frees string of strings
 * @pp: pointer to pointer of string of strings
 */
void ifree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - function that reallocates block of memory
 * @ptr: pointer to previous block
 * @old_size: old byte
 * @new_size: new byte
 * Return: ptr
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (p == NULL)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
