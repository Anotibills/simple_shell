#include "shell.h"

/**
 * _myhistory - function that displays the history list
 * @info: pointer to struct
 * Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - function that sets alias to string
 * @info: pointer to struct
 * @str: pointer to string
 * Return: 0 if success, 1 if error
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int ret;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(info->alias), get_node_index(info->alias,
				node_starts_with(info->alias, str, -1)));
	*p = c;
	return (ret);
}

/**
 * set_alias - function that sets alias to string
 * @info: pointer to struct
 * @str: string
 * Return: 0 if success, 1 if error
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));
	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node: pointer to node
 *
 * Return: 0 if success, 1 if error
 */
int print_alias(list_t *node)
{
	char *p = NULL, *i = NULL;

	if (node != 0)
	{
		p = _strchr(node->str, '=');
		for (i = node->str; i <= p; i++)
			_putchar(*i);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function that mimics the alias builtin
 * @info: pointer to struct
 *  Return: 0
 */
int _myalias(info_t *info)
{
	int a = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (a = 1; info->argv[a]; a++)
	{
		p = _strchr(info->argv[a], '=');
		if (p)
			set_alias(info, info->argv[a]);
		else
			print_alias(node_starts_with(info->alias, info->argv[a], '='));
	}

	return (0);
}
