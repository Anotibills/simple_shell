#include "shell.h"

/**
 * is_chain - function to test char if buffer is a chain delimeter
 * @info: pointer to struct
 * @buff: buffer
 * @p: current position of buffer address
 * Return: 1 if chain delimeter, else 0
 */
int is_chain(info_t *info, char *buff, size_t *p)
{
	size_t b = *p;

	if (buff[b] == '|' && buff[b + 1] == '|')
	{
		buff[b] = 0;
		b++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[b] == '&' && buff[b + 1] == '&')
	{
		buff[b] = 0;
		b++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[b] == ';')
	{
		buff[b] = 0;
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = b;
	return (1);
}

/**
 * check_chain - function that checks chaining continuation
 * @info: pointer struct
 * @buff: buffer
 * @p: current position of buffer address
 * @a: starting position in buffer
 * @len: length of buffer
 * Return: void
 */
void check_chain(info_t *info, char *buff, size_t *p, size_t a, size_t len)
{
	size_t b = *p;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[a] = 0;
			b = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buff[a] = 0;
			b = len;
		}
	}

	*p = b;
}

/**
 * replace_alias - function that replaces an aliases
 * @info: pointer to struct
 * Return: 1 if replaced, else 0
 */
int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (p == NULL)
			return (0);
		p = _strdup(p + 1);
		if (p == NULL)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * replace_vars - function that replaces vars
 * @info: pointer struct
 * Return: 1 if replaced, else 0
 */
int replace_vars(info_t *info)
{
	int a = 0;
	list_t *node;

	for (a = 0; info->argv[a]; a++)
	{
		if (info->argv[a][0] != '$' || !info->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[a][1], '=');
		if (node)
		{
			replace_string(&(info->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[a], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - function that replaces string
 * @old: pointer to old string address
 * @new: pointer to new string
 * Return: 1 if replaced, else 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
