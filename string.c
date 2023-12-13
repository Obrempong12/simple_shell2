#include "shell.h"

/**
 * _strlen - function that returns the length of a string
 * @s: the length of string to check
 * Return: int length of string
 */
int _strlen(char *s)
{
	int m = 0;

	if (!s)
		return (0);

	while (*s++)
		m++;
	return (m);
}

/**
 * _strcmp - a function that compares two null-terminated strings.
 * @str1: the first string
 * @str2: the second string
 * Return: negative if str1 < str2, positive if str1 > str2,
 * zero if str1 == str2
 */
int _strcmp(char *str1, char *str2)
{
	while (*str1 && *str2)
	{
		if (*str1 != *str2)
			return (*str1 - *str2);
		str1++;
		str2++;
	}
	if (*str1 == *str2)
		return (0);
	else
		return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts - function that checks if adisadel starts with college
 * @college: string to search
 * @adisadel: the substring to find
 *
 * Return: address of next char of college or NULL
 */
char *starts(const char *college, const char *adisadel)
{
	while (*adisadel)
		if (*adisadel++ != *college++)
			return (NULL);
	return ((char *)college);
}

/**
 * _strcat - function that concatenates two strings
 * @buf_dest: the buffer destination
 * @buf_srce: the buffer source
 * Return: pointer to buffer destination
 */
char *_strcat(char *buf_dest, char *buf_srce)
{
	char *next = buf_dest;

	while (*buf_dest)
		buf_dest++;
	while (*buf_srce)
		*buf_dest++ = *buf_srce++;
	*buf_dest = *buf_srce;
	return (next);
}
