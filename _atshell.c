#include "shell.h"

/**
 * interactive_mode - returns true if shell is interactive mode
 * @para: struct address
 *
 * Return: 1 if interactive mode, otherwise 0
 */
int interactive_mode(info_t *para)
{
	return (isatty(STDIN_FILENO) && para->readfd <= 2);
}

/**
 * is_delim - function that checks for delimiter character
 * @c: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, otherwise 0
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 *is_alpha_char - checks for alphabetic character
 *@c: The character to be inputted
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int is_alpha_char(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, otherwise converted number
 */

int _atoi(char *str)
{
	int m, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (m = 0; str[m] != '\0' && flag != 2; m++)
	{
		if (str[m] == '-')
			sign *= -1;

		if (str[m] >= '0' && str[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (str[m] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
