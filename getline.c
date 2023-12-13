#include "shell.h"
/**
 *input_buf - function that inputs buffer chain commands
 *@para: parameter of structure
 *@buf: address of buffer
 *@length: address of variable length
 *Return: bytes that were read
 */
ssize_t input_buf(info_t *para, char **buf, size_t *length)
{
	ssize_t w = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		w = getline(buf, &len_p, stdin);
#else
		w = _getline(para, buf, &len_p);
#endif
		if (w > 0)
		{
			if ((*buf)[w - 1] == '\n')
			{
				(*buf)[w - 1] = '\0';
				w--;
			}
			para->linecount_flag = 1;
			remove_comments(*buf);
			add_history_list(para, *buf, para->histcount++);
			{
				*length = w;
				para->cmd_buf = buf;
			}
		}
	}
	return (w);
}

/**
 *get_input - function that gets a line minus the newline
 *@para: parameter of structure
 *Return: bytes that was read
 */
ssize_t get_input(info_t *para)
{
	static char *buf;
	static size_t m, k, length;
	ssize_t w = 0;
	char **buf_p = &(para->arg), *p;

	_putchar(BUF_FLUSH);
	w = input_buf(para, &buf, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		k = m;
		p = buf + m;

		check_chain(para, buf, &k, m, length);
		while (k < length)
		{
			if (is_chain(para, buf, &k))
				break;
			k++;
		}

		m = k + 1;
		if (m >= length)
		{
			m = length = 0;
			para->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p;
		return (_strlen(p));
	}

	*buf_p = buf;
	return (w);
}

/**
 *read_buf - function that reads a buffer
 *@para: parameter of structure
 *@buf: buffer
 *@sb: size of buffer
 *Return: w
 */
ssize_t read_buf(info_t *para, char *buf, size_t *sb)
{
	ssize_t w = 0;

	if (*sb)
		return (0);
	w = read(para->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*sb = w;
	return (w);
}

/**
 *_getline - function that gets the next line of input
 *@para: parameter of structure
 *@b: address of pointer to buffer
 *@length: size of preallocated buffer pointer
 *Return: f
 */
int _getline(info_t *para, char **b, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t m, len;
	size_t j;
	ssize_t w = 0, f = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *b;
	if (p && length)
		f = *length;
	if (m == len)
		m = len = 0;

	w = read_buf(para, buf, &len);
	if (w == -1 || (w == 0 && len == 0))
		return (-1);

	c = _strchr(buf + m, '\n');
	j = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, f, f ? s + j : j + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (f)
		_strncat(new_p, buf + m, j - i);
	else
		_strncpy(new_p, buf + m, j - m + 1);

	f += j - m;
	m = j;
	p = new_p;

	if (length)
		*length = f;
	*b = p;
	return (f);
}

/**
 *sigintHandler - function that blocks ctrl-C
 *@sig_num: signal number
 *Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
