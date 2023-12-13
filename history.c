#include "shell.h"

/**
 * get_file_history - gets the history file
 * @para: parameter of structure
 * Return: allocated string
 */
char *get_file_history(info_t *para)
{
	char *buf, *dir;

	dir = _getenv(para, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - creates a file or adds to an existing file
 * @para: the parameter struct
 *
 * Return: 1 on success, otherwise -1
 */
int write_history(info_t *para)
{
	ssize_t fd;
	char *filename = get_history_file(para);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = para->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_file_history - function that reads history from file
 * @para: the parameter struct
 *
 * Return: history count on success, otherwise 0
 */
int read_file_history(info_t *para)
{
	int m, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(para);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (m = 0; m < fsize; m++)
		if (buf[m] == '\n')
		{
			buf[m] = 0;
			add_history_list(para, buf + last, linecount++);
			last = m + 1;
		}
	if (last != m)
		add_history_list(para, buf + last, linecount++);
	free(buf);
	para->histcount = linecount;
	while (para->histcount-- >= HIST_MAX)
		delete_node_index(&(para->history), 0);
	renumber_history(para);
	return (para->histcount);
}

/**
 * add_history_list - adds entry to a history linked list
 * @para: Structure containing potential arguments. Used to maintain
 * @buf: buffer
 * @linecount: the history linecount, history count
 *
 * Return: Always 0
 */
int add_history_list(info_t *para, char *buf, int linecount)
{
	list_t *node = NULL;

	if (para->history)
		node = para->history;
	add_end_node(&node, buf, linecount);

	if (!para->history)
		para->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list.
 * @para: Structure containing potential arguments.
 * Return: the new count.
 */
int renumber_history(info_t *para)
{
	list_t *node = para->history;
	int m = 0;

	while (node)
	{
		node->num = m++;
		node = node->next;
	}
	return (para->histcount = m);
}
