#include "shell.h"

/**
 * _strcpy - funtion that copies a string
 * @dest: pointer to the destination
 * @src: pointer to the source
 * Return: destination
 */
char *_strcpy(char *dest, char *src)
{
	int a = 0;

	if (dest == src || !src)
		return (dest);
	while (src[a])
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = 0;
	return (dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: pointer to string
 * Return: pointer of string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (!str)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (ret == NULL)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 *_puts - function that prints an input string
 *@str: pointer to string
 * Return: void
 */
void _puts(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		_putchar(str[a]);
		a++;
	}
}

/**
 * _putchar - function that writes a character to stdout
 * @c: character
 * Return: 1 if success, -1 if error
 */
int _putchar(char c)
{
	static int a;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || a >= WRITE_BUFF_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (c != BUFF_FLUSH)
		buff[a++] = c;
	return (1);
}
