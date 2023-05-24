#include "shell.h"

/**
 * input_buff - function that buffers chained commands
 * @info: struct
 * @buff: buffer address
 * @len: length
 * Return: bytes
 */
ssize_t input_buff(info_t *info, char **buff, size_t *len)
{
	ssize_t rd = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buff);
		*buff = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buff, &len_p, stdin);
#else
		rd = _getline(info, buff, &len_p);
#endif
		if (rd > 0)
		{
			if ((*buff)[rd - 1] == '\n')
			{
				(*buff)[rd - 1] = '\0';
				rd--;
			}
			info->linecount_flag = 1;
			remove_comments(*buff);
			build_history_list(info, *buff, info->histcount++);
			{
				*len = rd;
				info->cmd_buff = buff;
			}
		}
	}
	return (rd);
}

/**
 * get_input - function that gets a line minus the newline
 * @info: struct
 * Return: value of rd
 */
ssize_t get_input(info_t *info)
{
	static char *buff;
	static size_t a, b;
	static size_t len;
	ssize_t rd = 0;
	char **buff_p = &(info->arg), *p;

	_putchar(BUFF_FLUSH);
	rd = input_buff(info, &buff, &len);
	if (rd == -1)
		return (-1);
	if (len)
	{
		b = a;
		p = buff + a;
		check_chain(info, buff, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buff, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buff_type = CMD_NORM;
		}
		*buff_p = p;
		return (_strlen(p));
	}
	*buff_p = buff;
	return (rd);
}

/**
 * read_buff - function that reads a buffer
 * @info: struct
 * @buff: buffer
 * @a: size
 * Return: value of rd
 */
ssize_t read_buff(info_t *info, char *buff, size_t *a)
{
	ssize_t rd = 0;

	if (*a)
		return (0);
	rd = read(info->readfd, buff, READ_BUFF_SIZE);
	if (rd >= 0)
		*a = rd;
	return (rd);
}

/**
 * _getline - function to gets the next line of input from STDIN
 * @info: struct
 * @ptr: pointer to buffer address
 * @length: length size
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buff[READ_BUFF_SIZE];
	static size_t a, len;
	size_t k;
	ssize_t rd = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	rd = read_buff(info, buff, &len);
	if (rd == -1 || (rd == 0 && len == 0))
		return (-1);
	c = _strchr(buff + a, '\n');
	k = c ? 1 + (unsigned int)(c - buff) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buff + a, k - a);
	else
		_strncpy(new_p, buff + a, k - a + 1);

	s += k - a;
	a = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - function that blocks ctrl+C
 * @sig_num: signal number
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
