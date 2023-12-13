#include "shell.h"

/**
 *_pinputstr - function that prints an input string
 * @str: the string to be printed
 * Return: Nothing
 */
void _pinputstr(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_writchar(str[m]);
		m++;
	}
}

/**
 * _writchar - writes the character c to stderr
 * @c: The character to be printed
 * Return: On success 1, otherwise 0
 */
int _writchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(2, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 * _writchar_fd - writes the character c to fd
 * @c: The character
 * @fd: The file descriptor
 * Return: On success 1, otherwise -1
 */
int _writchar_fd(char c, int fd)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(fd, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}

/**
 *_pinputstr_fd - prints an input string to fd
 * @str: the string to be printed
 * @fd: the file descriptor
 * Return: the number of characters
 */
int _pinputstr_fd(char *str, int fd)
{
	int m = 0;

	if (!str)
		return (0);
	while (*str)
	{
		m += _pinputstr_fd(*str++, fd);
	}
	return (m);
}
