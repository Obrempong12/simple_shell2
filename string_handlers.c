#include "shell.h"

/**
 * _strcpy - function that copies a string
 * @buf_dest: the destination of buffer
 * @buf_srce: the source of buffer
 * Return: pointer to destination of buffer
 */
char *_strcpy(char *buf_dest, char *buf_srce)
{
	int m = 0;

	if (buf_dest == buf_srce || buf_srce == 0)
		return (buf_dest);
	while (buf_srce[m])
	{
		buf_dest[m] = buf_srce[m];
		m++;
	}
	buf_dest[m] = 0;
	return (buf_dest);
}

/**
 * _strdup - function that duplicates a string
 * @str: the string to be duplicated
 * Return: the pointer to the duplicated string
 */
char *_strdup(const char *str)
{
	int length = 0;
	char *nest;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	nest = malloc(sizeof(char) * (length + 1));
	if (!nest)
		return (NULL);
	for (length++; length--;)
		nest[length] = *--str;
	return (nest);
}

/**
 *_put - function that prints an input string
 *@str: the string to be printed
 * Return: Nothing
 */
void _put(char *str)
{
	int m = 0;

	if (!str)
		return;
	while (str[m] != '\0')
	{
		_putchar(str[m]);
		m++;
	}
}

/**
 * _putchar - function that writes the char c to stdout.
 * @c: The character to be printed
 * Return: 1 when successful.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	static int m;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || m >= WRITE_BUF_SIZE)
	{
		write(1, buf, m);
		m = 0;
	}
	if (c != BUF_FLUSH)
		buf[m++] = c;
	return (1);
}
