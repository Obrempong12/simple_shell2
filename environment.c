#include "shell.h"

/**
 * _myenv - function that prints the current environment
 * @para: parameter structure with potential arguments
 * Return: Always 0
 */
int _myenv(info_t *para)
{
	print_list_str(para->env);
	return (0);
}

/**
 * _getenv - function gets the environment variable value
 * @para: parameter structure with potential arguments
 * @env_name: environment variable name
 * Return: the value of environment
 */
char *_getenv(info_t *para, const char *env_name)
{
	list_t *node = para->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, env_name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable.
 * @info: parameter structure with potential arguments.
 * Return: Always 0
 */
int _mysetenv(info_t *para)
{
	if (para->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(para, para->argv[1], para->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - function that removes an environment variable
 * @para: Structure containing potential arguments
 * Return: Always 0
 */
int _myunsetenv(info_t *para)
{
	int m;

	if (para->argc == 1)
	{
		_eputs("Too few arguments.\n");
		return (1);
	}
	for (m = 1; m <= para->argc; m++)
		_unsetenv(para, para->argv[m]);

	return (0);
}

/**
 * populate_env_list - populates linked list of environment
 * @para: paramenter structure with potential arguments
 * Return: Always 0
 */
int populate_env_list(info_t *para)
{
	list_t *node = NULL;
	size_t m;

	for (m = 0; environ[m]; m++)
		add_end_node(&node, environ[m], 0);
	para->env = node;
	return (0);
}
