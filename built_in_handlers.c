#include "shell.h"

/**
 * _myhistory - function that displays the history list.
 * @para: parameter structure with potential arguments
 *  Return: Always 0
 */
int _myhistory(info_t *para)
{
	print_list(para->history);
	return (0);
}

/**
 * unset_alias - function that sets alias to string
 * @para: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, otherwise 1
 */
int unset_alias(info_t *para, char *str)
{
	char *p, c;
	int nest;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	nest = delete_node_index(&(para->alias),
		get_index_node(para->alias, node_starts_with(para->alias, str, -1)));
	*p = c;
	return (nest);
}

/**
 * set_alias - function that sets alias to string
 * @para: parameter struct
 * @str: the string alias
 * Return: Always 0 on success, otherwise 1
 */
int set_alias(info_t *para, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(para, str));

	unset_alias(para, str);
	return (add_end_node(&(para->alias), str, 0) == NULL);
}

/**
 * print_alias - function that prints an alias string
 * @node: the alias node
 * Return: Always 0 on success, otherwise 1
 */
int print_alias(list_t *node)
{
	char *p = NULL, *h = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (h = node->str; h <= p; h++)
			_putchar(*h);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - function mimics the alias built_in
 * @para: Structure containing potential arguments
 *  Return: Always 0
 */
int _myalias(info_t *para)
{
	int m = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (para->argc == 1)
	{
		node = para->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (m = 1; para->argv[m]; m++)
	{
		p = _strchr(para->argv[m], '=');
		if (p)
			set_alias(para, para->argv[m]);
		else
			print_alias(node_starts_with(para->alias, para->argv[m], '='));
	}

	return (0);
}
