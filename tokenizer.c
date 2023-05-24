#include "shell.h"

/**
 * **strtow - function that splits a string into words
 * @str: pointer of string
 * @d: pointer of string
 * Return: pointer to the array of strings, or NULL if fail
 */

char **strtow(char *str, char *d)
{
	int a, b, k, m, numwords = 0;
	char **c;

	if (!str || str[0] == 0)
		return (NULL);
	if (d == NULL)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (c == NULL)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		k = 0;
		while (!is_delim(str[a + k], d) && str[a + k])
			k++;
		c[b] = malloc((k + 1) * sizeof(char));
		if (c[b] == NULL)
		{
			for (k = 0; k < b; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[b][m] = str[a++];
		c[b][m] = 0;
	}
	c[b] = NULL;
	return (c);
}

/**
 * **strtow2 - function that splits a string into words
 * @str: pointer to string
 * @d: delimeter
 * Return: pointer to array of strings, or NULL if fail
 */
char **strtow2(char *str, char d)
{
	int a, b, k, m, numwords = 0;
	char **c;

	if (!str || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
		    (str[a] != d && !str[a + 1]) || str[a + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	c = malloc((1 + numwords) * sizeof(char *));
	if (c == NULL)
		return (NULL);
	for (a = 0, b = 0; b < numwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		k = 0;
		while (str[a + k] != d && str[a + k] && str[a + k] != d)
			k++;
		c[b] = malloc((k + 1) * sizeof(char));
		if (c[b] == NULL)
		{
			for (k = 0; k < b; k++)
				free(c[k]);
			free(c);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			c[b][m] = str[a++];
		c[b][m] = 0;
	}
	c[b] = NULL;
	return (c);
}
