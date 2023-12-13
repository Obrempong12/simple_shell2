#include "shell.h"

/**
 * **string_words - function that splits a string into words.
 * @str: string to be inputted
 * @dstr: delimiter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **string_words(char *str, char *dstr)
{
	int m, j, k, a, numbwords = 0;
	char **ars;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!dstr)
		dstr = " ";
	for (m = 0; str[m] != '\0'; m++)
		if (!is_delim(str[m], dstr) && (is_delim(str[m + 1], dstr) || !str[m + 1]))
			numbwords++;

	if (numbwords == 0)
		return (NULL);
	ars = malloc((1 + numbwords) * sizeof(char *));
	if (!ars)
		return (NULL);
	for (m = 0, k = 0; k < numbwords; k++)
	{
		while (is_delim(str[m], dstr))
			m++;
		k = 0;
		while (!is_delim(str[m + j], dstr) && str[m + j])
			j++;
		ars[k] = malloc((j + 1) * sizeof(char));
		if (!ars[k])
		{
			for (j = 0; j < k; j++)
				free(ars[j]);
			free(ars);
			return (NULL);
		}
		for (a = 0; a < j; a++)
			ars[k][a] = str[m++];
		ars[k][a] = 0;
	}
	ars[k] = NULL;
	return (ars);
}

/**
 * **string_words1 - splits a string into words
 * @str: the input string
 * @dstr: the delimiter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **string_words1(char *str, char dstr)
{
	int m, j, k, a, numbwords = 0;
	char **ars;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (m = 0; str[m] != '\0'; m++)
		if ((str[m] != dstr && str[m + 1] == dstr) ||
		    (str[m] != dstr && !str[m + 1]) || str[m + 1] == dstr)
			numbwords++;
	if (numbwords == 0)
		return (NULL);
	ars = malloc((1 + numbwords) * sizeof(char *));
	if (!ars)
		return (NULL);
	for (m = 0, k = 0; k < numbwords; k++)
	{
		while (str[m] == dstr && str[m] != dstr)
			m++;
		j = 0;
		while (str[m + j] != dstr && str[m + j] && str[m + j] != dstr)
			j++;
		ars[k] = malloc((j + 1) * sizeof(char));
		if (!ars[k])
		{
			for (j = 0; j < k; j++)
				free(ars[j]);
			free(ars);
			return (NULL);
		}
		for (a = 0; a < j; a++)
			ars[k][a] = str[m++];
		ars[k][a] = 0;
	}
	ars[k] = NULL;
	return (ars);
}
