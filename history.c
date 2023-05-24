#include "shell.h"

/**
 * get_history_file - function that gets the history file
 * @info: pointer to struct
 * Return: string with history file
 */

char *get_history_file(info_t *info)
{
	char *buff, *b;

	b = _getenv(info, "HOME=");
	if (b == NULL)
		return (NULL);
	buff = malloc(sizeof(char) * (_strlen(b) + _strlen(HIST_FILE) + 2));
	if (!buff)
		return (NULL);
	buff[0] = 0;
	_strcpy(buff, b);
	_strcat(buff, "/");
	_strcat(buff, HIST_FILE);
	return (buff);
}

/**
 * write_history - function that creates file
 * @info: pointer to struct
 *
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *fname = get_history_file(info);
	list_t *node = NULL;

	if (!fname)
		return (-1);

	fd = open(fname, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(fname);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUFF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - function that reads history from file
 * @info: pointer to struct
 * Return: histcount if success, else 0
 */
int read_history(info_t *info)
{
	int a, z = 0, lcount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buff = NULL, *fname = get_history_file(info);

	if (fname == NULL)
		return (0);

	fd = open(fname, O_RDONLY);
	free(fname);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buff = malloc(sizeof(char) * (fsize + 1));
	if (buff == NULL)
		return (0);
	rdlen = read(fd, buff, fsize);
	buff[fsize] = 0;
	if (rdlen <= 0)
		return (free(buff), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buff[a] == '\n')
		{
			buff[a] = 0;
			build_history_list(info, buff + z, lcount++);
			z = a + 1;
		}
	if (z != a)
		build_history_list(info, buff + z, lcount++);
	free(buff);
	info->histcount = lcount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - function that adds entry to a history linked list
 * @info: pointer to struct
 * @buff: buffer
 * @lcount: history of linecount and histcount
 * Return: 0
 */
int build_history_list(info_t *info, char *buff, int lcount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buff, lcount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - function that renumbers history of ll after changes
 * @info: pointer to struct
 * Return: new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
