#include "shell.h"

/**
 * list_length - function that determines length of linked list
 * @b: pointer to first node
 * Return: size of list
 */
size_t list_length(const list_t *b)
{
	size_t m = 0;

	while (b)
	{
		b = b->next;
		m++;
	}
	return (m);
}

/**
 * list_return_strings - returns an array of strings
 * @ph: pointer to first node
 * Return: array of strings
 */
char **list_return_strings(list_t *ph)
{
	list_t *node = ph;
	size_t m = sa_handler(ph), k;
	char **strs;
	char *str;

	if (!ph || !m)
		return (NULL);
	strs = malloc(sizeof(char *) * (m + 1));
	if (!strs)
		return (NULL);
	for (m = 0; node; node = node->next, m++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (k = 0; k < m; k++)
				free(strs[k]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[m] = str;
	}
	strs[m] = NULL;
	return (strs);
}


/**
 * print_list - prints all elements of linked list
 * @b: pointer to first node
 * Return: size of list
 */
size_t print_list(const list_t *b)
{
	size_t m = 0;

	while (b)
	{
		_put(convert_number(b->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_put(b->str ? b->str : "(nil)");
		_put("\n");
		b = b->next;
		m++;
	}
	return (m);
}

/**
 * node_starts_with - function that returns node with prefix
 * @ph: pointer to list head
 * @prefix: string to match
 * @c: the next character
 * Return: match node or null
 */
list_t *node_starts_with(list_t *ph, char *prefix, char c)
{
	char *q = NULL;

	while (ph)
	{
		q = node_starts_with(ph->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (ph);
		ph = ph->next;
	}
	return (NULL);
}

/**
 * get_index_node - function that gets the index of a node
 * @ph: pointer to list head
 * @pn: pointer to the node
 * Return: index of node or -1
 */
ssize_t get_index_node(list_t *ph, list_t *pn)
{
	size_t m = 0;

	while (ph)
	{
		if (ph == pn)
			return (m);
		ph = ph->next;
		m++;
	}
	return (-1);
}
