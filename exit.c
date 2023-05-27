#include "shell.h"

/**
 * *_strncpy - function that copies a string
 * @dest: pointer to string destination
 * @src: pointer to source string
 * @i: number of characters to be copied
 * Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int i)
{
	int a, b;
	char *c = dest;

	a = 0;
	while (src[a] != '\0' && a < i - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < i)
	{
		b = a;
		while (b < i)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (c);
}

/**
 * *_strncat - function that concatenates two strings
 * @dest: pointer to first string
 * @src: pointer to second string
 * @i: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *_strncat(char *dest, char *src, int i)
{
	int a, b;
	char *c = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < i)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (a < i)
		dest[a] = '\0';
	return (c);
}

/**
 * *_strchr - function that locates a character in a string
 * @s: pointer string to be parsed
 * @c: character to note
 * Return: pointer to the memory area
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
