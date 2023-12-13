#include "shell.h"

/**
 * _convstr_int - function that converts a string to an integer
 * @str: the string to be converted
 * Return: 0 if no nums in string, otherwise -1
 */
int _convstr_int(char *str)
{
	int m = 0;
	unsigned long int numb = 0;

	if (*str == '+')
		str++;
	for (m = 0;  str[m] != '\0'; m++)
	{
		if (str[m] >= '0' && str[m] <= '9')
		{
			numb *= 10;
			numb += (str[m] - '0');
			if (numb > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (numb);
}

/**
 * print_error - function that prints an error message
 * @para: the parameter
 * @strerr: string with specified error type
 * Return: 0 if no nums in string, otherwise -1
 */
void print_error(info_t *para, char *strerr)
{
	_pinputstr(para->fname);
	_pinputstr(": ");
	print_d(para->line_count, STDERR_FILENO);
	_pinputstr(": ");
	_pinputstr(para->argv[0]);
	_pinputstr(": ");
	_pinputstr(strerr);
}

/**
 * print_deci - function prints a decimal numbers
 * @input: the input
 * @fd: the file descriptor
 * Return: num of characters printed
 */
int print_deci(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int m, count = 0;
	unsigned int ada, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		ada = -input;
		__putchar('-');
		count++;
	}
	else
		ada = input;
	current = ada;
	for (m = 1000000000; m > 1; m /= 10)
	{
		if (ada / m)
		{
			__putchar('0' + current / m);
			count++;
		}
		current %= m;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_number - converter function, a clone of itoa
 * @numb: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int numb, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char symb = 0;
	char *ptr;
	unsigned long n = numb;

	if (!(flags & CONVERT_UNSIGNED) && numb < 0)
	{
		n = -numb;
		symb = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcde" : "0123456789ABCDE";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[n % base];
		n /= base;
	} while (n != 0);

	if (symb)
		*--ptr = symb;
	return (ptr);
}

/**
 * replace_comments - replaces first instance of '#' with '\0'
 * @buf: address of the string
 * Return: Always 0;
 */
void replace_comments(char *buf)
{
	int m;

	for (m = 0; buf[m] != '\0'; m++)
		if (buf[m] == '#' && (!m || buf[m - 1] == ' '))
		{
			buf[m] = '\0';
			break;
		}
}
