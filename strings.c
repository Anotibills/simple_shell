#include "shell.h"

/**
 * _strlen - function that returns the length of string
 * @c: pointer to string
 * Return: the length of string
 */
int _strlen(char *c)
{
	int a = 0;

	if (c == NULL)
		return (0);

	while (*c++)
		a++;
	return (a);
}

/**
 * _strcmp - function that compares two strings.
 * @c1: string 1
 * @c2: string 2
 * Return: negative if c1 < c2, and positive if c1 > c2, 0 if c1 == c2
 */
int _strcmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * starts_with - function that checks if needle starts with haystack
 * @haystack: pointer to string
 * @needle: pointer to substring
 * Return: the address of next character of haystack, or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - function that concatenates two strings
 * @dest: pointer to buffer destination
 * @src: pointer to source buffer
 *
 * Return: buffer
 */
char *_strcat(char *dest, char *src)
{
	char *t = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (t);
}
