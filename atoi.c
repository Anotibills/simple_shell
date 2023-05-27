#include "shell.h"

/**
 * interactive - function that returns true for shell is interactive mode
 * @info: address struct
 *
 * Return: 1 if interactive mode, otherwise returns 0
 */
int interactive(info_t *info)
{
	return (info->readfd <= 2 && isatty(STDIN_FILENO));
}

/**
 * is_delim - function that checks if character is a delimeter
 * @c: character to check
 * @delim: delimeter string
 * Return: 1 if true, and 0 if false
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *_isalpha - function that checks for alphabetic char
 *@c: character to input
 *Return: 1 if c is alphabetic, else, return 0
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - function that converts a string to an integer
 *@s: string
 *Return: 0 if no numbers in string, otherwise convert number
 */

int _atoi(char *s)
{
	int a, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (a = 0;  s[a] != '\0' && flag != 2; a++)
	{
		if (s[a] == '-')
			sign *= -1;

		if (s[a] >= '0' && s[a] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[a] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
