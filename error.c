#include "shell.h"

/**
 *_eputs - function that prints an input string
 * @str: pointer to string
 * Return: void
 */
void _eputs(char *str)
{
	int a = 0;

	if (str == NULL)
		return;
	while (str[a] != '\0')
	{
		_eputchar(str[a]);
		a++;
	}
}

/**
 * _eputchar - function that writes the character c to stderr
 * @c: char to print
 * Return: 1 if success, -1 if error
 */
int _eputchar(char c)
{
	static int a;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || a >= WRITE_BUFF_SIZE)
	{
		write(2, buff, a);
		a = 0;
	}
	if (c != BUFF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 * _putfd - function that writes the character c to given fd
 * @c: character to be printed
 * @fd: filedescriptor to write
 * Return: 1 if success, -1 if fail
 */
int _putfd(char c, int fd)
{
	static int a;
	static char buff[WRITE_BUFF_SIZE];

	if (c == BUFF_FLUSH || a >= WRITE_BUFF_SIZE)
	{
		write(fd, buff, a);
		a = 0;
	}
	if (c != BUFF_FLUSH)
		buff[a++] = c;
	return (1);
}

/**
 *_putsfd - function that prints an input string
 * @str: pointer ro string to be printed
 * @fd: filedescriptor to write
 * Return: number of characters input
 */
int _putsfd(char *str, int fd)
{
	int a = 0;

	if (str == NULL)
		return (0);
	while (*str)
	{
		a += _putfd(*str++, fd);
	}
	return (a);
}
