#include "shell.h"

/**
 * get_environ - returns the string array copy of environ
 * @para: Structure containing potential arguments
 * Return: Always 0
 */
char **get_environ(info_t *para)
{
	if (!para->environ || para->env_changed)
	{
		para->environ = list_to_strings(para->env);
		para->env_changed = 0;
	}

	return (para->environ);
}

/**
 * _unsetenv - function that removes an environment variable
 * @para: Structure containing potential arguments
 * @var: the string environment variable
 * Return: 1 on delete, otherwise 0
 */
int _unsetenv(info_t *para, char *var)
{
	list_t *node = para->env;
	size_t m = 0;
	char *p;

	if (!node || !var)
		return (0);

	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			para->env_changed = delete_node_index(&(para->env), m);
			m = 0;
			node = para->env;
			continue;
		}
		node = node->next;
		m++;
	}
	return (para->env_changed);
}

/**
 * _setenv - Initializes a new environment variable,
 *             or modify an existing one
 * @para: Structure containing potential arguments
 * @var: the string envionment variable
 * @value: the string environment variable value
 * Return: Always 0
 */
int _setenv(info_t *para, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *p;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = para->env;
	while (node)
	{
		p = starts_with(node->str, var);
		if (p && *p == '=')
		{
			free(node->str);
			node->str = buf;
			para->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_end_node(&(para->env), buf, 0);
	free(buf);
	para->env_changed = 1;
	return (0);
}
