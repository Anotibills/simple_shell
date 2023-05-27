#include "shell.h"

/**
 * _erratoi - function that converts a string to an integer
 * @s: pointer to string to be converted
 * Return: 0 if numbers not in string, else convert, and -1 if error
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int result = 0;

	if (*s == '+')
		s++;
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			result *= 10;
			result += (s[a] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * print_error - function that prints an error message
 * @info: pointer to struct
 * @estr: pointer to string error type
 * Return: 0 if numbers not in string, else convert, and -1 if error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
	print_d(info->line_count, STDERR_FILENO);
}

/**
 * print_d - function that prints a decimal (integer)
 * @input: input
 * @fd: filedescriptor to write
 * Return: the number of printed characters
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (_abs_ / a)
		{
			__putchar('0' + current / a);
			count++;
		}
		current %= a;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - function that converter function
 * @num: the number
 * @base: the base
 * @flags: the argument flags
 * Return: the string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long n = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		n = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - function that replaces first instance of '#' with '\0'
 * @buff: pointer to string address
 * Return: 0
 */
void remove_comments(char *buff)
{
	int a;

	for (a = 0; buff[a] != '\0'; a++)
		if (buff[a] == '#' && (a == 0 || buff[a - 1] == ' '))
		{
			buff[a] = '\0';
			break;
		}
}
