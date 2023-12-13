#include "shell.h"

/**
 **_strncpy - function that copies a string
 *@strdest: the destination string to be copied
 *@strsrce: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *strdest, char *strsrce, int n)
{
	int m, k;
	char *s = strdest;

	m = 0;
	while (strsrce[m] != '\0' && m < n - 1)
	{
		strdest[m] = strsrce[m];
		m++;
	}
	if (m < n)
	{
		k = m;
		while (k < n)
		{
			strdest[k] = '\0';
			k++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@strdest: the first string
 *@strsrce: the second string
 *@n: the amount of bytes
 *Return: the concatenated string
 */
char *_strncat(char *strdest, char *strsrce, int n)
{
	int m, k;
	char *s = strdest;

	m = 0;
	k = 0;
	while (strdest[m] != '\0')
		m++;
	while (strsrce[k] != '\0' && k < n)
	{
		strdest[m] = strsrce[k];
		m++;
		k++;
	}
	if (k < n)
		strdest[m] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@s: the string
 *@c: the character
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
